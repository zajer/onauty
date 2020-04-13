module StringMap = Map.Make(struct
  let compare = Stdlib.compare
  type t = string
end)

type cm = int list StringMap.t
type graph = { nov:int; e:(int*int) list; c: cm  option }