#!/bin/bash

helper() {
    echo $0
    echo $1
   echo "$@"
   return 11
}

helper a "B C" d
echo $?
