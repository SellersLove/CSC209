#!/bin/bash

#execute the *c file
./compile.sh untar.c

# one single file
./untar t1.tar
cd realtar
tar -xf t1.tar
cd ..
diff -Nru test/ realtar/test/
# two files
./untar t2.tar
cd realtar
tar -xf t2.tar
cd ..
diff -Nru test/ realtar/test/
# empty folder with a single file
./untar t3.tar
cd realtar
tar -xf t3.tar
cd ..
diff -Nru test/ realtar/test/
# nonempty folder with single file
./untar t4.tar
cd realtar
tar -xf t4.tar
cd ..
diff -Nru test/ realtar/test/
# folder within a folder
./untar t5.tar
cd realtar
tar -xf t5.tar
cd ..
diff -Nru test/ realtar/test/
# file within a folder within another folder 
./untar t6.tar
cd realtar
tar -xf t6.tar
cd ..
diff -Nru test/ realtar/test/
# finall test
./untar t7.tar
cd realtar
tar -xf t7.tar
cd ..
diff -Nru tar/ realtar/tar/

