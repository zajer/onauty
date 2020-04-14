#define CAML_NAME_SPACE
#define DEBUG FALSE
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/custom.h>
#include "nauty/nauty.h" 
//#include "nauty/nautinv.h" 
#include <stdlib.h>
int are_canon_graphs_equal(graph *cg1, graph *cg2,int m,int n)
{
	size_t k;
	if ( DEBUG )
		printf("Are canon graphs equal - loop begin\n");
	for (k = 0; k < m*(size_t)n; ++k) 
		if (cg1[k] != cg2[k]) break; 
	if ( DEBUG )
		printf("Are canon graphs equal - loop finished\n");
    if (k != m*(size_t)n)  
	{
		if ( DEBUG )
			printf("Are canon graphs equal - not equal\n");
		return 0;
	}
	if ( DEBUG )
		printf("Are canon graphs equal - equal\n");
	return 1;
}

char is_end_of_list(value *eol)
{
    if( *eol == Val_int(0))
        return 1;
    else
        return 0;
}

int extract_from_parameter(value *list_element_content)
{
	int result;
    result = Int_val(Field( *list_element_content, 0 ));
	if ( DEBUG )
		printf("from= %d\n", result);
	return result;
}

int extract_to_parameter(value *list_element_content)
{
	int result;
    result = Int_val(Field( *list_element_content, 1 ));
	if ( DEBUG )
		printf("to= %d\n", result);
	return result;
}

void setup_graph_ndir(graph *g,int g_sz,int no_nodes,int no_setwords,value *edges_list)
{
    value *current_eol,*current_content;
    int i,from,to;
    current_eol = edges_list;
    
    EMPTYGRAPH(g,no_setwords,no_nodes); 

    while ( !is_end_of_list(current_eol) )
    {
		current_content = &Field( *current_eol,0 );

        from = extract_from_parameter( current_content );
        to = extract_to_parameter( current_content );
		
        ADDONEEDGE(g,from,to,no_setwords);
        current_eol = &Field(*current_eol,1);
    }
}

int main_routine_ndir(int nov,value *edges1,value *edges2,char are_colored,value *colors1,value *colors2)
{
    if ( DEBUG )
		printf("In main routine for ndir\n");
    DEFAULTOPTIONS_GRAPH(options); 
	statsblk stats; 
	int n,m,i; 
	size_t k; 
	
	DYNALLSTAT(int,lab1,lab1_sz); 
	DYNALLSTAT(int,lab2,lab2_sz); 
	DYNALLSTAT(int,ptn1,ptn1_sz); 
	DYNALLSTAT(int,ptn2,ptn2_sz); 
	DYNALLSTAT(int,orbits1,orbits1_sz); 
	DYNALLSTAT(int,orbits2,orbits2_sz); 
	DYNALLSTAT(int,map,map_sz); 
	DYNALLSTAT(graph,g1,g1_sz); 
	DYNALLSTAT(graph,g2,g2_sz); 
	DYNALLSTAT(graph,cg1,cg1_sz); 
	DYNALLSTAT(graph,cg2,cg2_sz); 

	options.getcanon = TRUE; 
    
	n = nov;	
	m = SETWORDSNEEDED(n); 
	
	nauty_check(WORDSIZE,m,n,NAUTYVERSIONID); 
	if ( DEBUG )
		printf("Main routine ndir - malloc start\n");
	DYNALLOC1(int,lab1,lab1_sz,n,"malloc"); 
	DYNALLOC1(int,lab2,lab2_sz,n,"malloc"); 
	DYNALLOC1(int,ptn1,ptn1_sz,n,"malloc"); 
	DYNALLOC1(int,ptn2,ptn2_sz,n,"malloc"); 
	DYNALLOC1(int,orbits1,orbits1_sz,n,"malloc"); 
	DYNALLOC1(int,orbits2,orbits2_sz,n,"malloc"); 
	DYNALLOC1(int,map,map_sz,n,"malloc"); 
	DYNALLOC2(graph,g1,g1_sz,n,m,"malloc"); 
	DYNALLOC2(graph,g2,g2_sz,n,m,"malloc");
	DYNALLOC2(graph,cg1,cg1_sz,n,m,"malloc"); 
	DYNALLOC2(graph,cg2,cg2_sz,n,m,"malloc"); 

	if ( DEBUG )
		printf("Main routine ndir - malloc finished\n");
	
	setup_graph_ndir(g1,g1_sz,n,m,edges1);
	if ( DEBUG )
		printf("Main routine ndir - setup of graph1 finished\n");
	setup_graph_ndir(g2,g2_sz,n,m,edges2); 
	if ( DEBUG )
		printf("Main routine ndir - setup of graph2 finished\n");

	if (are_colored)
	{
		//color_graph1(lab1,ptn1,n);
		//color_graph2(lab2,ptn2,n);
	    options.defaultptn = FALSE; 
		if ( DEBUG )
			printf("Main routine ndir - colors set\n");
	}
	
	if ( DEBUG )
		printf("Main routine ndir - densenauty start\n");

	densenauty(g1,lab1,ptn1,orbits1,&options,&stats,m,n,cg1);
	if ( DEBUG )
		printf("Main routine ndir - densenauty for graph1 finished\n");
	densenauty(g2,lab2,ptn2,orbits2,&options,&stats,m,n,cg2); 
	if ( DEBUG )
		printf("Main routine ndir - densenauty for graph2 finished\n");

	int result = are_canon_graphs_equal(cg1,cg2,m,n);
    if ( DEBUG )
		printf("Main routine ndir - finished - result=%d\n",result);

    return result;
}

value nauty_graph_iso_no_colors(value graph1, value graph2)
{
    CAMLparam2 (graph1,graph2);
    CAMLlocal3 (result,edges1,edges2);
	int nov1_i,nov2_i,result_i;
	if ( DEBUG )
		printf("c_stub - ndir - start\n");
	nov1_i = Int_val(Field(graph1,0));
	nov2_i = Int_val(Field(graph2,0));
	
	if (nov1_i == nov2_i && nov1_i != 0)
	{
		
		if ( DEBUG )
			printf("c_stub - ndir - numbers of vertices are equal:%d\n",nov1_i);
		edges1 = Field(graph1,1);
		edges2 = Field(graph2,1);
		
		result_i = main_routine_ndir(nov1_i,&edges1,&edges2,FALSE,NULL,NULL);
		
		if ( DEBUG )
			printf("c_stub - ndir - result=%d\n",result_i);
		
		result = Val_int( result_i );
		if ( DEBUG )
			printf("c_stub - ndir - result converted\n");
	}
	else if (nov1_i==0 && nov2_i == 0)
	{
		if ( DEBUG )
			printf("Numbers of vertices are equal to 0 in both graphs");
		result = Val_int(1);
	}
	else
	{
		if ( DEBUG )
			printf("Numbers of vertices are not equal: nov1=%d nov2=%d\n",nov1_i,nov2_i);
		result = Val_int(0);
	}
    
	if ( DEBUG )
		printf("c_stub - ndir - finished\n");
	CAMLreturn (result);
}