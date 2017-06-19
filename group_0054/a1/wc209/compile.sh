#!/bin/bash

INFILE=$1

OUTFILE="./${INFILE%.c}"

# If the BINDIR does not exist, create it now


# Compile the source
gcc -g -Wall "${INFILE}" -o "${OUTFILE}"
