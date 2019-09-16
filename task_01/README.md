# task_01
Simple example of lexical and syntax analyzer. Without building AST (*abstract syntax tree*).

### What you have to do:
- rewrite synt structure (set more encapsulated);
- add structure for work with variables;
- add variable check (check of existen);
- add '+' and '-' operations (with variadic number of values);
- add function of error information (must pass the number line of code with error, type of error);
- rewrite work with table of lexemes (get lexemes directly from table);
- implement all 'TODO' tips (start with `TODO: Here you have to ...`);


### Build
*Note:* all instructions here for machine with *nix OS. For Windows users may be need some another instructions (you can try to use `Cygwin` or just change `g++` on `mingw`).

To build by make (Makefile):
```
$ cd <to repo path>/task_01
$ make
```

To build by cmake (CMakeLists.txt):
```
$ cd <to repo path>/task_01
$ cmake .
$ make
```
