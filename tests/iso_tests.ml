open OUnit2

let test_iso_1 _ =
    let g1 = Onauty.Graph.empty ()
    and g2 = Onauty.Graph.empty ()
    in
        assert_equal true (Onauty.Iso.are_graphs_iso g1 g2);;

let suite =
  "ISO tests" >::: [
    "iso test 1">::test_iso_1;
]

let () =
  run_test_tt_main suite