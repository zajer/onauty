(lang dune 2.0)
(name onauty)
(version 0.5)
(generate_opam_files true)

(source (github zajer/onauty))
(license MIT)
(authors "Piotr Cybulski <pikus3@list.pl>")
(maintainers "Piotr Cybulski <pikus3@list.pl>")
(homepage "https://github.com/zajer/onauty")
(bug_reports "https://github.com/zajer/onauty/issues")

(package
  (name onauty)
  (synopsis "OCaml bindings to nauty library")
  (description "
    Library for deternining isomorphis between graphs and digraphs. 
    It uses nauty library as its backbone.")
  (tags ("nauty" "graphs" "isomorphism" ) )
  (depends
    (dune (and :build (>= 2.0.0)))
    (ocaml (>= 4.06.0))
    conf-nauty
    (ounit2 :with-test)
  )
)
