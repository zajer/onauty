#define CAML_NAME_SPACE
#define DEBUG FALSE
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/custom.h>
#include "nauty/nauty.h" 
#include "nauty/nautinv.h" 
#include <stdlib.h>
int are_canon_graphs_equal(graph *cg1, graph *cg2,int m,int n)
{
	size_t k;
	if ( DEBUG )
		printf("are_canon_graphs_equal - loop begin\n");
	for (k = 0; k < m*(size_t)n; ++k) 
		if (cg1[k] != cg2[k]) break; 
	if ( DEBUG )
		printf("are_canon_graphs_equal - loop finished\n");
    if (k != m*(size_t)n)  
	{
		if ( DEBUG )
			printf("are_canon_graphs_equal - graphs are not equal\n");
		return FALSE;
	}
	if ( DEBUG )
		printf("are_canon_graphs_equal - graphs are equal\n");
	return TRUE;
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

value *next_eol(value *current_eol)
{
	return &Field(*current_eol,1);
}

value *content_of_eol(value *eol)
{
	return &Field(*eol,0);
}

void setup_graph_ndir(graph *g,int g_sz,int no_nodes,int no_setwords,value *edges_list)
{
    value *current_eol,*current_content;
    int i,from,to;
    current_eol = edges_list;
    
    EMPTYGRAPH(g,no_setwords,no_nodes); 

    while ( !is_end_of_list(current_eol) )
    {
		current_content = content_of_eol (current_eol);

        from = extract_from_parameter( current_content );
        to = extract_to_parameter( current_content );
		
        ADDONEEDGE(g,from,to,no_setwords);
		current_eol = next_eol(current_eol);
    }
}

void setup_graph_dir(graph *g,int g_sz,int no_nodes,int no_setwords,value *edges_list)
{
    value *current_eol,*current_content;
    int i,from,to;
    current_eol = edges_list;
    
    EMPTYGRAPH(g,no_setwords,no_nodes); 

    while ( !is_end_of_list(current_eol) )
    {
		current_content = content_of_eol (current_eol);

        from = extract_from_parameter( current_content );
        to = extract_to_parameter( current_content );
		
        ADDONEARC(g,from,to,no_setwords);
		current_eol = next_eol(current_eol);
    }
}

void color_graph(int *lab,int *ptn,value *colors_list)
{
	value *current_color,*list_of_vertices_4_current_color_list,*current_vertex_4_current_color,*vertex_id;
	
	current_color = colors_list;
	int i = 0;
	while( !is_end_of_list(current_color) )
	{
		list_of_vertices_4_current_color_list = content_of_eol(current_color);
		current_vertex_4_current_color = list_of_vertices_4_current_color_list;
		while ( !is_end_of_list(current_vertex_4_current_color) )
		{
			vertex_id = content_of_eol(current_vertex_4_current_color);
			lab[i] = Int_val(*vertex_id);
			ptn[i] = 1;
			i++;
			current_vertex_4_current_color = next_eol(current_vertex_4_current_color);
		}
		ptn[i-1] = 0;
		current_color = next_eol(current_color);
	}
}

void common_nauty_routine(
	int n,int m,
	value *edges1,value *edges2,
	value *colors1,value *colors2,
	boolean are_graphs_colored,
	boolean are_graphs_directed,
	optionblk* options,
	graph *cg1,graph *cg2,
	int *lab1,int *lab2
	)
{
	//n = no_vertices;	
	//m = SETWORDSNEEDED(no_vertices); 
	statsblk stats; 
	size_t k; 
	
	//DYNALLSTAT(int,lab1,lab1_sz); 
	//DYNALLSTAT(int,lab2,lab2_sz); 
	DYNALLSTAT(int,ptn1,ptn1_sz); 
	DYNALLSTAT(int,ptn2,ptn2_sz); 
	DYNALLSTAT(int,orbits1,orbits1_sz); 
	DYNALLSTAT(int,orbits2,orbits2_sz);  
	DYNALLSTAT(graph,g1,g1_sz); 
	DYNALLSTAT(graph,g2,g2_sz); 

	options->getcanon = TRUE; 
    
	nauty_check(WORDSIZE,m,n,NAUTYVERSIONID); 
	if ( DEBUG )
		printf("common_nauty_routine - malloc start\n");
	//DYNALLOC1(int,lab1,lab1_sz,n,"malloc"); 
	//DYNALLOC1(int,lab2,lab2_sz,n,"malloc"); 
	DYNALLOC1(int,ptn1,ptn1_sz,n,"malloc"); 
	DYNALLOC1(int,ptn2,ptn2_sz,n,"malloc"); 
	DYNALLOC1(int,orbits1,orbits1_sz,n,"malloc"); 
	DYNALLOC1(int,orbits2,orbits2_sz,n,"malloc"); 
	DYNALLOC2(graph,g1,g1_sz,n,m,"malloc"); 
	DYNALLOC2(graph,g2,g2_sz,n,m,"malloc");

	if(are_graphs_directed)
	{
		setup_graph_dir(g1,g1_sz,n,m,edges1);
		if ( DEBUG )
			printf("common_nauty_routine - setup of digraph1 finished\n");
		setup_graph_dir(g2,g2_sz,n,m,edges2); 
		if ( DEBUG )
			printf("common_nauty_routine - setup of digraph2 finished\n");
	}
	else
	{
		setup_graph_ndir(g1,g1_sz,n,m,edges1);
		if ( DEBUG )
			printf("common_nauty_routine - setup of graph1 finished\n");
		setup_graph_ndir(g2,g2_sz,n,m,edges2); 
		if ( DEBUG )
			printf("common_nauty_routine - setup of graph2 finished\n");
	}

	if (are_graphs_colored)
	{
		color_graph(lab1,ptn1,colors1);
		color_graph(lab2,ptn2,colors2);
		options->defaultptn = FALSE; 
		if ( DEBUG )
			printf("common_nauty_routine - colors set\n");
	}

	densenauty(g1,lab1,ptn1,orbits1,options,&stats,m,n,cg1);
	densenauty(g2,lab2,ptn2,orbits2,options,&stats,m,n,cg2); 
	
	DYNFREE(ptn1,ptn1_sz);
	DYNFREE(ptn2,ptn2_sz);
	DYNFREE(orbits1,orbits1_sz);
	DYNFREE(orbits2,orbits2_sz);
	DYNFREE(g1,g1_sz);
	DYNFREE(g2,g2_sz);
}

optionblk get_default_options(boolean are_graphs_directed)
{
	DEFAULTOPTIONS_DIGRAPH(options_di);
	DEFAULTOPTIONS_GRAPH(options_g);
	if(are_graphs_directed)
		return options_di;
	else
		return options_g;
}

void make_mapping_of_iso_graphs(int *g1lab, int *g2lab, int *map, int nov)
{
	int i;
	for (i = 0; i < nov; ++i) 
	{
		if ( DEBUG ) printf("vertex %d of sg1 maps onto vertex %d of sg2\n", g1lab[i],g2lab[i]);
		map[g1lab[i]] = g2lab[i];
	}
}

int common_nauty_iso_check(
	int no_vertices,
	value *edges1,
	value *edges2,
	char are_colored,
	value *colors1,
	value *colors2,
	boolean are_graphs_directed
	)
{
	
	int result,m;
	optionblk options = get_default_options(are_graphs_directed);
	m=SETWORDSNEEDED(no_vertices);
	
	DYNALLSTAT(int,lab1,lab1_sz); 
	DYNALLSTAT(int,lab2,lab2_sz);
	DYNALLSTAT(graph,canon_graph1_result,canon_graph1_result_size); 
	DYNALLSTAT(graph,canon_graph2_result,canon_graph2_result_size); 
	
	DYNALLOC1(int,lab1,lab1_sz,no_vertices,"malloc"); 
	DYNALLOC1(int,lab2,lab2_sz,no_vertices,"malloc"); 
	DYNALLOC2(graph,canon_graph1_result,canon_graph1_result_size,no_vertices,m,"malloc"); 
	DYNALLOC2(graph,canon_graph2_result,canon_graph2_result_size,no_vertices ,m,"malloc"); 
	
	common_nauty_routine(
		no_vertices,m,
		edges1,edges2,
		colors1,colors2,
		are_colored,
		are_graphs_directed,
		&options,
		canon_graph1_result,canon_graph2_result,
		lab1,lab2
		);
	
	result = are_canon_graphs_equal(canon_graph1_result,canon_graph2_result,m,no_vertices);
	
	DYNFREE(lab1,lab1_sz);
	DYNFREE(lab2,lab2_sz);
	DYNFREE(canon_graph1_result,canon_graph1_result_size);
	DYNFREE(canon_graph2_result,canon_graph2_result_size);
	return result;
}

void common_nauty_iso_mapping(
	int no_vertices,
	value *edges1,
	value *edges2,
	char are_colored,
	value *colors1,
	value *colors2,
	boolean are_graphs_directed,
	int** mapping_result, int** are_graphs_equal_result
	)
{
	
	int are_graphs_equal,m;
	optionblk options = get_default_options(are_graphs_directed);
	int *map;
	m=SETWORDSNEEDED(no_vertices);
	
	map = malloc(sizeof(int)*no_vertices);
	DYNALLSTAT(int,lab1,lab1_sz); 
	DYNALLSTAT(int,lab2,lab2_sz);
	DYNALLSTAT(graph,canon_graph1_result,canon_graph1_result_size); 
	DYNALLSTAT(graph,canon_graph2_result,canon_graph2_result_size); 
	
	DYNALLOC1(int,lab1,lab1_sz,no_vertices,"malloc"); 
	DYNALLOC1(int,lab2,lab2_sz,no_vertices,"malloc"); 
	DYNALLOC2(graph,canon_graph1_result,canon_graph1_result_size,no_vertices,m,"malloc"); 
	DYNALLOC2(graph,canon_graph2_result,canon_graph2_result_size,no_vertices ,m,"malloc"); 
	
	common_nauty_routine(
		no_vertices,m,
		edges1,edges2,
		colors1,colors2,
		are_colored,
		are_graphs_directed,
		&options,
		canon_graph1_result,canon_graph2_result,
		lab1,lab2
		);
	
	are_graphs_equal = are_canon_graphs_equal(canon_graph1_result,canon_graph2_result,m,no_vertices);
	
	if ( are_graphs_equal )
		make_mapping_of_iso_graphs(lab1,lab2,map,no_vertices);
	
	DYNFREE(lab1,lab1_sz);
	DYNFREE(lab2,lab2_sz);
	DYNFREE(canon_graph1_result,canon_graph1_result_size);
	DYNFREE(canon_graph2_result,canon_graph2_result_size);
	*mapping_result = map;
	*are_graphs_equal_result = malloc(sizeof(int));
	**are_graphs_equal_result = are_graphs_equal;
}

value make_ocaml_int_tuple(int v1, int v2)
{
	CAMLparam0();
	CAMLlocal1(result);
	
	result = caml_alloc_tuple(2);
	Store_field (result, 0, Val_int(v1));	
	Store_field (result, 1, Val_int(v2));	
	
	CAMLreturn(result);
}

value c_int_array_to_ocaml_int_tuple_array(int *input,int input_length)
{
	CAMLparam0();
	CAMLlocal1(result);
	int i;
	
	if ( DEBUG ) printf("c_int_array_to_ocaml_int_tuple_array - start\n");
	if(input_length > 0){
		if ( DEBUG ) printf("c_int_array_to_ocaml_int_tuple_array - input length = %d\n",input_length);
		result = caml_alloc_tuple(input_length);
	}
	else{
		if ( DEBUG ) printf("c_int_array_to_ocaml_int_tuple_array - input length is 0 \n");
		result = Atom(0);
	}
	
	for(i=0;i<input_length;i++)
		Store_field (result, i, make_ocaml_int_tuple(i,input[i]));	
	
	if ( DEBUG ) printf("c_int_array_to_ocaml_int_tuple_array - finished\n");
	
	CAMLreturn(result);
}

value common_ocaml_iso_map_routine(value graph1, value graph2,value are_colored,value are_directed)
{
    CAMLparam4 (graph1,graph2,are_colored,are_directed);
    CAMLlocal5 (result,edges1,edges2,colors1,colors2);
	int nov1_i,nov2_i,are_colored_i,are_directed_i;
	int *graphs_iso_mapping_result,*are_graphs_iso_result;
	if ( DEBUG )
		printf("common_ocaml_iso_map_routine - start\n");
	nov1_i = Int_val(Field(graph1,0));
	nov2_i = Int_val(Field(graph2,0));
	are_colored_i = Bool_val(are_colored);
	are_directed_i = Bool_val(are_directed);
	result = caml_alloc_tuple(2);
	
	if (nov1_i == nov2_i && nov1_i != 0)
	{
		
		if ( DEBUG )
			printf("common_ocaml_iso_map_routine - numbers of vertices are equal:%d\n",nov1_i);
		edges1 = Field(graph1,1);
		edges2 = Field(graph2,1);
		
		if (are_colored_i)
		{
			colors1 = Field(graph1,2);
			colors2 = Field(graph2,2);
			
			common_nauty_iso_mapping(nov1_i,&edges1,&edges2,TRUE,&colors1,&colors2,are_directed_i,&graphs_iso_mapping_result,&are_graphs_iso_result);
		}
		else
			common_nauty_iso_mapping(nov1_i,&edges1,&edges2,FALSE,NULL,NULL,are_directed_i,&graphs_iso_mapping_result,&are_graphs_iso_result);
		
		if ( DEBUG ) printf("common_ocaml_iso_map_routine - are_iso_result=%d\n",*are_graphs_iso_result);
		
		Store_field (result, 0, Val_int(*are_graphs_iso_result));
		
		if(*are_graphs_iso_result)
			Store_field (result, 1, c_int_array_to_ocaml_int_tuple_array(graphs_iso_mapping_result,nov1_i));
		else
			Store_field (result, 1, Atom(0));
		if ( DEBUG ) printf("common_ocaml_iso_check_routine - results converted\n");
	}
	else if (nov1_i==0 && nov2_i == 0)
	{
		if ( DEBUG )
			printf("common_ocaml_iso_map_routine - Numbers of vertices are equal to 0 in both graphs");
		
		Store_field (result, 0, Val_int(1));
		Store_field (result, 1, Atom(0));
	}
	else
	{
		if ( DEBUG )
			printf("common_ocaml_iso_map_routine - Numbers of vertices are not equal: nov1=%d nov2=%d\n",nov1_i,nov2_i);
		Store_field (result, 0, Val_int(0));
		Store_field (result, 1, Atom(0));
	}
    
	if ( DEBUG )
		printf("common_ocaml_iso_map_routine - finished\n");
	free(graphs_iso_mapping_result);
	free(are_graphs_iso_result);
	CAMLreturn (result);
}

value common_ocaml_iso_check_routine(value graph1, value graph2,value are_colored,value are_directed)
{
    CAMLparam4 (graph1,graph2,are_colored,are_directed);
    CAMLlocal5 (result,edges1,edges2,colors1,colors2);
	int nov1_i,nov2_i,result_i,are_colored_i,are_directed_i;
	if ( DEBUG )
		printf("common_ocaml_iso_check_routine - start\n");
	nov1_i = Int_val(Field(graph1,0));
	nov2_i = Int_val(Field(graph2,0));
	are_colored_i = Bool_val(are_colored);
	are_directed_i = Bool_val(are_directed);
	if (nov1_i == nov2_i && nov1_i != 0)
	{
		
		if ( DEBUG )
			printf("common_ocaml_iso_check_routine - numbers of vertices are equal:%d\n",nov1_i);
		edges1 = Field(graph1,1);
		edges2 = Field(graph2,1);
		
		if (are_colored_i)
		{
			colors1 = Field(graph1,2);
			colors2 = Field(graph2,2);
		
			result_i = common_nauty_iso_check(nov1_i,&edges1,&edges2,TRUE,&colors1,&colors2,are_directed_i);
		}
		else
			result_i = common_nauty_iso_check(nov1_i,&edges1,&edges2,FALSE,NULL,NULL,are_directed_i);
		
		if ( DEBUG )
			printf("common_ocaml_iso_check_routine - result=%d\n",result_i);
		
		result = Val_int( result_i );
		if ( DEBUG )
			printf("common_ocaml_iso_check_routine - result converted\n");
	}
	else if (nov1_i==0 && nov2_i == 0)
	{
		if ( DEBUG )
			printf("common_ocaml_iso_check_routine - Numbers of vertices are equal to 0 in both graphs");
		result = Val_int(1);
	}
	else
	{
		if ( DEBUG )
			printf("common_ocaml_iso_check_routine - Numbers of vertices are not equal: nov1=%d nov2=%d\n",nov1_i,nov2_i);
		result = Val_int(0);
	}
    
	if ( DEBUG )
		printf("common_ocaml_iso_check_routine - finished\n");
	CAMLreturn (result);
}
