(lang dune 2.0)
(name onauty)
(version 0.1)
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
  (description "")
  (tags ("nauty" "graphs" "isomorphis" ) )
  (depends
    (dune (and :build (>= 2.0.0)))
    
  )
)
