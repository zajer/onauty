open Common
val empty : unit -> graph
val add_vertex : graph -> graph
val add_vertices : int -> graph -> graph
val add_conn : (int*int) -> graph -> graph
val add_conns : (int*int) list -> graph -> graph
val color_vertex : string -> int -> graph -> graph
val color_vertices : string -> int list -> graph -> graph
val set_colors : cm -> graph -> graph
