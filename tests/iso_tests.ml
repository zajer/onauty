open OUnit2
open Onauty
let test_iso_1 _ =
    let g1 = Onauty.Graph.empty ()
    and g2 = Onauty.Graph.empty ()
    in
        assert_equal true (Onauty.Iso.are_graphs_iso g1 g2);;
let test_iso_2 _ =
  let g1 = Onauty.Graph.empty ()
    |> Onauty.Graph.add_vertices 4 
    |> Onauty.Graph.add_conns [(0,1);(2,1);(3,2)]
  and g2 = Onauty.Graph.empty () 
    |> Onauty.Graph.add_vertices 4 
    |> Onauty.Graph.add_conns [(0,1);(2,1);(3,2)]
  in
      assert_equal true (Onauty.Iso.are_graphs_iso g1 g2);;      
let test_iso_3 _ =
  let g1 = Onauty.Graph.empty () |> Onauty.Graph.add_vertex
  and g2 = Onauty.Graph.empty ()
  in
      assert_equal false (Onauty.Iso.are_graphs_iso g1 g2);;
let test_iso_4 _ =
  let g1 = Onauty.Graph.empty ()
    |> Onauty.Graph.add_vertices 4 
    |> Onauty.Graph.add_conns [(0,1);(1,2);(3,2)]
  and g2 = Onauty.Graph.empty () 
    |> Onauty.Graph.add_vertices 4 
    |> Onauty.Graph.add_conns [(0,1);(2,1);(3,2)]
  in
      assert_equal true (Onauty.Iso.are_graphs_iso g1 g2);;    
let test_iso_5 _ =
  let g1 = Onauty.Graph.empty ()
    |> Onauty.Graph.add_vertices 4 
    |> Onauty.Graph.add_conns [(0,1);(2,1);(3,2)]
    |> Onauty.Graph.set_colors 
      (Common.StringMap.empty 
        |> Common.StringMap.add "C1" [0]
        |> Common.StringMap.add "C2" [2;3]
        |> Common.StringMap.add "C3" [1]
      )
  and g2 = Onauty.Graph.empty () 
    |> Onauty.Graph.add_vertices 4 
    |> Onauty.Graph.add_conns [(0,1);(2,1);(3,2)]
    |> Onauty.Graph.set_colors 
      (Common.StringMap.empty 
        |> Common.StringMap.add "C1" [0]
        |> Common.StringMap.add "C2" [2;3]
        |> Common.StringMap.add "C3" [1]
      )
  in
      assert_equal true (Onauty.Iso.are_graphs_iso g1 g2);;
let test_iso_6 _ =
  let g1 = Onauty.Graph.empty ()
    |> Onauty.Graph.add_vertices 4 
    |> Onauty.Graph.add_conns [(0,1);(1,2);(3,2)]
    |> Onauty.Graph.set_colors 
      (Common.StringMap.empty 
        |> Common.StringMap.add "C1" [3]
        |> Common.StringMap.add "C2" [0;1]
        |> Common.StringMap.add "C3" [2]
      )
  and g2 = Onauty.Graph.empty () 
    |> Onauty.Graph.add_vertices 4 
    |> Onauty.Graph.add_conns [(0,1);(2,1);(3,2)]
    |> Onauty.Graph.set_colors 
      (Common.StringMap.empty 
        |> Common.StringMap.add "C1" [0]
        |> Common.StringMap.add "C2" [2;3]
        |> Common.StringMap.add "C3" [1]
      )
  in
      assert_equal true (Onauty.Iso.are_graphs_iso g1 g2);;    
let test_iso_7 _ =
  let g1 = Onauty.Graph.empty ()
  and g2 = Onauty.Graph.empty ()
  in
      assert_equal true (Onauty.Iso.are_digraphs_iso g1 g2);;
let test_iso_8 _ =
  let g1 = Onauty.Graph.empty ()
    |> Onauty.Graph.add_vertices 4 
    |> Onauty.Graph.add_conns [(0,1);(2,1);(3,2)]
  and g2 = Onauty.Graph.empty () 
    |> Onauty.Graph.add_vertices 4 
    |> Onauty.Graph.add_conns [(0,1);(2,1);(3,2)]
  in
      assert_equal true (Onauty.Iso.are_digraphs_iso g1 g2);;      
let test_iso_9 _ =
  let g1 = Onauty.Graph.empty () |> Onauty.Graph.add_vertex
  and g2 = Onauty.Graph.empty ()
  in
      assert_equal false (Onauty.Iso.are_digraphs_iso g1 g2);;
let test_iso_10 _ =
  let g1 = Onauty.Graph.empty ()
    |> Onauty.Graph.add_vertices 4 
    |> Onauty.Graph.add_conns [(0,1);(1,2);(3,2)]
  and g2 = Onauty.Graph.empty () 
    |> Onauty.Graph.add_vertices 4 
    |> Onauty.Graph.add_conns [(0,1);(2,1);(3,2)]
  in
      assert_equal true (Onauty.Iso.are_digraphs_iso g1 g2);;    
let test_iso_11 _ =
  let g1 = Onauty.Graph.empty ()
    |> Onauty.Graph.add_vertices 4 
    |> Onauty.Graph.add_conns [(0,1);(2,1);(3,2)]
    |> Onauty.Graph.set_colors 
      (Common.StringMap.empty 
        |> Common.StringMap.add "C1" [0]
        |> Common.StringMap.add "C2" [2;3]
        |> Common.StringMap.add "C3" [1]
      )
  and g2 = Onauty.Graph.empty () 
    |> Onauty.Graph.add_vertices 4 
    |> Onauty.Graph.add_conns [(0,1);(2,1);(3,2)]
    |> Onauty.Graph.set_colors 
      (Common.StringMap.empty 
        |> Common.StringMap.add "C1" [0]
        |> Common.StringMap.add "C2" [2;3]
        |> Common.StringMap.add "C3" [1]
      )
  in
      assert_equal true (Onauty.Iso.are_digraphs_iso g1 g2);;
let test_iso_12 _ =
  let g1 = Onauty.Graph.empty ()
    |> Onauty.Graph.add_vertices 4 
    |> Onauty.Graph.add_conns [(0,1);(1,2);(3,2)]
    |> Onauty.Graph.set_colors 
      (Common.StringMap.empty 
        |> Common.StringMap.add "C1" [3]
        |> Common.StringMap.add "C2" [0;1]
        |> Common.StringMap.add "C3" [2]
      )
  and g2 = Onauty.Graph.empty () 
    |> Onauty.Graph.add_vertices 4 
    |> Onauty.Graph.add_conns [(0,1);(2,1);(3,2)]
    |> Onauty.Graph.set_colors 
      (Common.StringMap.empty 
        |> Common.StringMap.add "C1" [0]
        |> Common.StringMap.add "C2" [2;3]
        |> Common.StringMap.add "C3" [1]
      )
  in
      assert_equal true (Onauty.Iso.are_digraphs_iso g1 g2);;    
let test_iso_13 _ =
  let g1 = Onauty.Graph.empty ()
    |> Onauty.Graph.add_vertices 4 
    |> Onauty.Graph.add_conns [(1,0);(2,1);(2,3)]
  and g2 = Onauty.Graph.empty () 
    |> Onauty.Graph.add_vertices 4 
    |> Onauty.Graph.add_conns [(0,1);(2,1);(3,2)]
  in
      assert_equal true (Onauty.Iso.are_graphs_iso g1 g2);;        
let test_iso_14 _ =
  let g1 = Onauty.Graph.empty ()
    |> Onauty.Graph.add_vertices 4 
    |> Onauty.Graph.add_conns [(0,1);(1,2);(3,2)]
  and g2 = Onauty.Graph.empty () 
    |> Onauty.Graph.add_vertices 4 
    |> Onauty.Graph.add_conns [(0,1);(1,2);(2,3)]
  in
      assert_equal false (Onauty.Iso.are_digraphs_iso g1 g2);;        
      
let suite =
  "ISO tests" >::: [
    "iso test 1 - ndir - empty">::test_iso_1;
    "iso test 2 - ndir - identical">::test_iso_2;
    "iso test 3 - ndir - different number of vertices">::test_iso_3;
    "iso test 4 - ndir - isomorphic-not equal">::test_iso_4;
    "iso test 5 - ndir - colored - identical">::test_iso_5;
    "iso test 6 - ndir - colored - isomorphic-not equal">::test_iso_6;
    "iso test 7 - dir - empty">::test_iso_7;
    "iso test 8 - dir - identical">::test_iso_8;
    "iso test 9 - dir - different number of vertices">::test_iso_9;
    "iso test 10 - dir - isomorphic-not equal">::test_iso_10;
    "iso test 11 - dir - colored - identical">::test_iso_11;
    "iso test 12 - dir - colored - isomorphic-not equal">::test_iso_12;
    "iso test 13 - ndir - isomorphic - order of edges">::test_iso_13;
    "iso test 14 - dir - not isomorphic - order of edges">::test_iso_14;
]

let () =
  run_test_tt_main suite