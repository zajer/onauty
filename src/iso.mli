open Common
val are_graphs_iso : ?check_colors:bool -> graph -> graph -> bool
val are_digraphs_iso : ?check_colors:bool -> graph -> graph -> bool
val graphs_iso_map : ?check_colors:bool -> graph -> graph -> bool * (int*int) array
val digraphs_iso_map : ?check_colors:bool -> graph -> graph -> bool * (int*int) array
