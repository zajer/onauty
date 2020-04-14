open OUnit2

let test_graph_1 _ =
    let g = Onauty.Graph.empty ()
    in
        assert_equal 0 (g.nov);;
let test_graph_2 _ =
  let g = Onauty.Graph.empty ()
    |> Onauty.Graph.add_vertices 4 
  in
      assert_equal 4 (g.nov);;
      

let suite =
  "Graph tests" >::: [
    "graph test 1 - empty">::test_graph_1;
    "graph test 2 - num of vertices check">::test_graph_2;
]

let () =
  run_test_tt_main suite