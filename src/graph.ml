open Common

let empty () =
    {nov=0;e=[];c=None}
let add_vertex g =
    {nov=g.nov+1;e=g.e;c=g.c}
let add_vertices nov2add g =
    {nov=g.nov+nov2add;e=g.e;c=g.c}
let add_conn c g =
    {nov=g.nov;e=c::g.e;c=g.c}
let add_conns cs g = 
    let res_cons = List.rev_append g.e cs
    in
    {nov=g.nov;e=res_cons;c=g.c}
let color_vertex c vid g =
    let curr_cm = if Option.is_some g.c then Option.get g.c else StringMap.empty
    and update_fun = 
        fun new_el curr_il_opt -> if Option.is_some curr_il_opt then let curr_il = Option.get curr_il_opt in Some (new_el::curr_il) else Some [new_el]
    in
        let res_cm = StringMap.update c (update_fun vid) curr_cm
        in
            {nov=g.nov;e=g.e;c=Some res_cm}
let color_vertices c vs g =
    let curr_cm = if Option.is_some g.c then Option.get g.c else StringMap.empty
    and update_fun = 
        fun new_els curr_il_opt -> if Option.is_some curr_il_opt then let curr_il = Option.get curr_il_opt in Some (List.rev_append new_els curr_il) else Some new_els
    in
        let res_cm = StringMap.update c (update_fun vs) curr_cm
        in
            {nov=g.nov;e=g.e;c=Some res_cm}
let set_colors cs g = 
    {nov=g.nov;e=g.e;c=Some cs}

    