open OUnit2
open Onauty
let test_iso_1 _ =
    let g1 = Graph.empty ()
    and g2 = Graph.empty ()
    in
        assert_equal (true,[||]) (Iso.graphs_iso_map g1 g2);
        assert_equal (true,[||]) (Iso.digraphs_iso_map g1 g2);;
let test_iso_2 _ =
  let g1 = Graph.empty ()
    |> Graph.add_vertices 1
  and g2 = Graph.empty () 
    |> Graph.add_vertices 2
  in
      assert_equal (false,[||]) (Iso.graphs_iso_map g1 g2);
      assert_equal (false,[||]) (Iso.digraphs_iso_map g1 g2);;
let test_iso_3 _ =
  let g1 = Graph.empty ()
    |> Graph.add_vertices 4 
    |> Graph.add_conns [(0,1);(2,1);(3,2)]
  and g2 = Graph.empty () 
    |> Graph.add_vertices 4 
    |> Graph.add_conns [(0,1);(2,1);(3,2)]
  in
      assert_equal (true,[|(0,0);(1,1);(2,2);(3,3)|]) (Iso.graphs_iso_map g1 g2);
      assert_equal (true,[|(0,0);(1,1);(2,2);(3,3)|]) (Iso.digraphs_iso_map g1 g2);;      
let test_iso_4 _ =
  let g1 = Graph.empty ()
    |> Graph.add_vertices 4 
    |> Graph.add_conns [(0,1);(1,2);(3,2)]
  and g2 = Graph.empty () 
    |> Graph.add_vertices 4 
    |> Graph.add_conns [(0,1);(2,1);(3,2)]
  in
	  assert_equal (true,[|(0,0);(1,1);(2,2);(3,3)|]) (Iso.graphs_iso_map g1 g2);
	  assert_equal (true,[|(0,3);(1,2);(2,1);(3,0)|]) (Iso.digraphs_iso_map g1 g2);;
let test_iso_5 _ =
  let g1 = Graph.empty ()
    |> Graph.add_vertices 4 
    |> Graph.add_conns [(0,1);(2,1);(3,2)]
    |> Graph.set_colors 
      (Common.StringMap.empty 
        |> Common.StringMap.add "C1" [0]
        |> Common.StringMap.add "C2" [2;3]
        |> Common.StringMap.add "C3" [1]
      )
  and g2 = Graph.empty () 
    |> Graph.add_vertices 4 
    |> Graph.add_conns [(0,1);(2,1);(3,2)]
    |> Graph.set_colors 
      (Common.StringMap.empty 
        |> Common.StringMap.add "C1" [0]
        |> Common.StringMap.add "C2" [2;3]
        |> Common.StringMap.add "C3" [1]
      )
  in
      assert_equal (true,[|(0,0);(1,1);(2,2);(3,3)|]) (Iso.graphs_iso_map ~check_colors:true g1 g2);
      assert_equal (true,[|(0,0);(1,1);(2,2);(3,3)|]) (Iso.digraphs_iso_map ~check_colors:true g1 g2);;      
let test_iso_6 _ =
  let g1 = Graph.empty ()
    |> Graph.add_vertices 4 
    |> Graph.add_conns [(0,1);(1,2);(3,2)]
    |> Graph.set_colors 
      (Common.StringMap.empty 
        |> Common.StringMap.add "C1" [3]
        |> Common.StringMap.add "C2" [0;1]
        |> Common.StringMap.add "C3" [2]
      )
  and g2 = Graph.empty () 
    |> Graph.add_vertices 4 
    |> Graph.add_conns [(0,1);(2,1);(3,2)]
    |> Graph.set_colors 
      (Common.StringMap.empty 
        |> Common.StringMap.add "C1" [0]
        |> Common.StringMap.add "C2" [2;3]
        |> Common.StringMap.add "C3" [1]
      )
  in
      assert_equal (true,[|(0,3);(1,2);(2,1);(3,0)|]) (Iso.graphs_iso_map ~check_colors:true g1 g2);
      assert_equal (true,[|(0,3);(1,2);(2,1);(3,0)|]) (Iso.digraphs_iso_map ~check_colors:true g1 g2);;      
let test_iso_7 _ =
	let g1 = Graph.empty () 
    |> Graph.add_vertices 4 
    |> Graph.add_conns [(0,1);(2,1);(3,2)]
    |> Graph.set_colors 
      (Common.StringMap.empty 
        |> Common.StringMap.add "A" [0]
        |> Common.StringMap.add "B" [1]
        |> Common.StringMap.add "C" [2;3] 
      )   
	and g2 = Graph.empty () 
		|> Graph.add_vertices 4 
		|> Graph.add_conns [(0,1);(2,1);(3,2)]
		|> Graph.set_colors 
		  (Common.StringMap.empty 
			|> Common.StringMap.add "A" [3]
			|> Common.StringMap.add "B" [2]
			|> Common.StringMap.add "C" [0;1]
		  )
	in
		assert_equal (true,[|(0,3);(1,2);(2,1);(3,0)|]) (Iso.graphs_iso_map ~check_colors:true g1 g2);
		assert_equal (false,[||]) (Iso.digraphs_iso_map ~check_colors:true g1 g2);; 
		
let suite =
  "ISO tests" >::: [
    "iso map test 1 - empty">::test_iso_1;
    "iso map test 2 - different number of vertices">::test_iso_2;
	"iso map test 3 - both - identical">::test_iso_3;
	"iso map test 4 - isomorphic-not equal">::test_iso_4;
	"iso map test 5 - both - colored - identical">::test_iso_5;
    "iso map test 6 - both - colored - isomorphic-not equal">::test_iso_6;
    "iso map test 7 - readme">::test_iso_7;
]

let () =
  run_test_tt_main suite
