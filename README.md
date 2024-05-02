# Cres: C dependency resolution

## Intro

This project mainly aims to compile the objects of a set of c files based on the header include statements; then output the executable result of linking those objects. Other functionality might be implemented as well e.g.: generating a header declaration for a concrete C file, adding commands to a build pipeline (similar but not as complex as makefile), among others to decide.

## TLDR
Automatically generate a command that compiles a modular C project from an entry file.
