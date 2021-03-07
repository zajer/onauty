open Common

type c_graph_colored = {nov:int ;e:(int*int) list;c:int list list}

external ext_iso_check : c_graph_colored -> c_graph_colored -> bool -> bool -> bool = "common_ocaml_iso_check_routine"
external ext_iso_map : c_graph_colored -> c_graph_colored -> bool -> bool -> bool *(int * int) array = "common_ocaml_iso_map_routine"

let common_iso_check (are_graphs_directed:bool) (check_colors:bool) (graph1:Common.graph) (graph2:Common.graph) =
    let _ = StringMap.bindings (if Option.is_some graph1.c then Option.get graph1.c else StringMap.empty)
    and _ = StringMap.bindings (if Option.is_some graph2.c then Option.get graph2.c else StringMap.empty)
    in
        if not check_colors then
            let c_graph1 = {nov=graph1.nov;e=graph1.e;c=[]}
            and c_graph2 = {nov=graph2.nov;e=graph2.e;c=[]}
            in
                ext_iso_check c_graph1 c_graph2 false are_graphs_directed
        else
            if not (Option.is_none graph1.c || Option.is_none graph2.c) then
                let colors1_list,vid1_order = StringMap.bindings (Option.get graph1.c) 
                    |> List.fold_left ( fun (res_cls,res_vid_order) (s,vid)-> ((s::res_cls),(vid :: res_vid_order))) ([],[])
                and colors2_list,vid2_order = StringMap.bindings (Option.get graph2.c)
                    |> List.fold_left ( fun (res_cls,res_vid_order) (s,vid)-> ((s::res_cls),(vid :: res_vid_order))) ([],[])
                in
                    let c_graph1 = {nov=graph1.nov;e=graph1.e;c=vid1_order}
                    and c_graph2 = {nov=graph2.nov;e=graph2.e;c=vid2_order}
                    in
                        if List.for_all2 (fun c1 c2 -> c1 = c2) colors1_list colors2_list then
                            ext_iso_check c_graph1 c_graph2 true are_graphs_directed
                        else
                            false
                    
            else
                raise (Invalid_argument ("Both graphs have to have set colors"))
let are_graphs_iso ?(check_colors=false) (graph1:Common.graph) (graph2:Common.graph) =
    common_iso_check false check_colors graph1 graph2
let are_digraphs_iso ?(check_colors=false) (graph1:Common.graph) (graph2:Common.graph) =
    common_iso_check true check_colors graph1 graph2
let common_iso_map (are_graphs_directed:bool) (check_colors:bool) (graph1:Common.graph) (graph2:Common.graph) =
    let _ = StringMap.bindings (if Option.is_some graph1.c then Option.get graph1.c else StringMap.empty)
    and _ = StringMap.bindings (if Option.is_some graph2.c then Option.get graph2.c else StringMap.empty)
    in
        if not check_colors then
            let c_graph1 = {nov=graph1.nov;e=graph1.e;c=[]}
            and c_graph2 = {nov=graph2.nov;e=graph2.e;c=[]}
            in
                ext_iso_map c_graph1 c_graph2 false are_graphs_directed
        else
            if not (Option.is_none graph1.c || Option.is_none graph2.c) then
                let colors1_list,vid1_order = StringMap.bindings (Option.get graph1.c) 
                    |> List.fold_left ( fun (res_cls,res_vid_order) (s,vid)-> ((s::res_cls),(vid :: res_vid_order))) ([],[])
                and colors2_list,vid2_order = StringMap.bindings (Option.get graph2.c)
                    |> List.fold_left ( fun (res_cls,res_vid_order) (s,vid)-> ((s::res_cls),(vid :: res_vid_order))) ([],[])
                in
                    let c_graph1 = {nov=graph1.nov;e=graph1.e;c=vid1_order}
                    and c_graph2 = {nov=graph2.nov;e=graph2.e;c=vid2_order}
                    in                    
						if List.for_all2 (fun c1 c2 -> c1 = c2) colors1_list colors2_list then
							ext_iso_map c_graph1 c_graph2 true are_graphs_directed
						else
							(false,[||])
                    
            else
                raise (Invalid_argument ("Both graphs have to have set colors"))
let graphs_iso_map ?(check_colors=false) (graph1:Common.graph) (graph2:Common.graph) =
    common_iso_map false check_colors graph1 graph2
let digraphs_iso_map ?(check_colors=false) (graph1:Common.graph) (graph2:Common.graph) =
    common_iso_map true check_colors graph1 graph2
