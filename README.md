# Onauty
An OCaml library for determining whether provided graphs are isomorphic or not.  
In case they are, a map between vertices can also be calculated.
It uses nauty library as its backbone.

## Credits
This is software uses *nauty and Traces* library (http://pallini.di.uniroma1.it/) licensed under the Apache License 2.0. A boilerplate declaration is available in *LICENSE-Nauty&Traces.txt* file. 
The full license is available at: https://www.apache.org/licenses/LICENSE-2.0

## Usage
### Creating a graph
To create a graph one should specify its vertices and adjacency matrix<sup>1</sup>.
```
open Onauty

let g = Graph.empty ()
    |> Graph.add_vertices 4 
    |> Graph.add_conns [(0,1);(1,2);(3,2)]
```
It is possible to create a graph all at once (as shown above) or partially.
```
open Onauty

let g = Graph.empty () ;;
Graph.add_vertex g |> Graph.add_vertex ;;
.
. (* doing some stuff*)
.
Graph.add_conn (0,1) g;;
```
<sup>1</sup> The order of connections is only important if a graph will be later considered as a digraph (directed graph).
### Checking for isomorphism
Having two graphs, we can check whether they are isomorphic to each other.
```
let g1 = Onauty.Graph.empty ()
    |> Onauty.Graph.add_vertices 4 
    |> Onauty.Graph.add_conns [(0,1);(1,2);(3,2)]
let g2 = Onauty.Graph.empty () 
    |> Onauty.Graph.add_vertices 4 
    |> Onauty.Graph.add_conns [(0,1);(2,1);(3,2)]
(* g1 and g2 will be considered as undirected graphs *)
let are_iso1 = Onauty.Iso.are_graphs_iso g1 g2    
(* g1 and g2 will be considered as directed graphs*)
let are_iso2 = Onauty.Iso.are_digraphs_iso g1 g2    
```
### Coloring vertices
It is also possible to partition a set of vertices into groups of colors.
```
(*this creates a graph with vertex 0 colored with first color, vertices 2 and 3 are colored with second color and vertex 1 is colored with third color *)
let g = Onauty.Graph.empty () 
    |> Onauty.Graph.add_vertices 4 
    |> Onauty.Graph.add_conns [(0,1);(2,1);(3,2)]
    |> Onauty.Graph.set_colors 
      (Common.StringMap.empty 
        |> Common.StringMap.add "C1" [0]
        |> Common.StringMap.add "C2" [2;3]
        |> Common.StringMap.add "C3" [1]
```
Please note that order of colors is important for determing the ismorphism.
For example:
```
let g1 = Onauty.Graph.empty () 
    |> Onauty.Graph.add_vertices 4 
    |> Onauty.Graph.add_conns [(0,1);(2,1);(3,2)]
    |> Onauty.Graph.set_colors 
      (Common.StringMap.empty 
        |> Common.StringMap.add "A" [0]
        |> Common.StringMap.add "B" [2;3]
        |> Common.StringMap.add "C" [1]
let g2 = Onauty.Graph.empty () 
    |> Onauty.Graph.add_vertices 4 
    |> Onauty.Graph.add_conns [(0,1);(2,1);(3,2)]
    |> Onauty.Graph.set_colors 
      (Common.StringMap.empty 
        |> Common.StringMap.add "C" [0]
        |> Common.StringMap.add "A" [2;3]
        |> Common.StringMap.add "B" [1]
(*this result in false because colors (represented as strings "A", "B" and "C") are sorted alphbetically so the first graph has vertex 0 assigned to first color while the second graph has vertex 0 assigned to third color. Structurally graphs are identical but colors are different.  *)
let are_iso = Onauty.Iso.are_graphs_iso g1 g2 
```
### Mappig between graphs
TBD