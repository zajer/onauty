open Common
type c_graph = {nov:int ;e:(int*int) list}

external nauty_graphs_iso_no_colors : c_graph -> c_graph -> bool = "nauty_graph_iso_no_colors"

let are_graphs_iso graph1 graph2 =
    let _ = StringMap.bindings (if Option.is_some graph1.c then Option.get graph1.c else StringMap.empty)
    and _ = StringMap.bindings (if Option.is_some graph2.c then Option.get graph2.c else StringMap.empty)
    in
        if Option.is_none graph1.c && Option.is_none graph2.c then
            let c_graph1 = {nov=graph1.nov;e=graph1.e}
            and c_graph2 = {nov=graph2.nov;e=graph2.e}
            in
                nauty_graphs_iso_no_colors c_graph1 c_graph2
        else
            failwith "yolo"