#define CAML_NAME_SPACE
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/custom.h>

value nauty_graph_iso_no_colors(value graph1, value graph2)
{
    CAMLparam2 (graph1,graph2);
    CAMLlocal1 (result);
    result = Val_bool(0);
    CAMLreturn (result);
}