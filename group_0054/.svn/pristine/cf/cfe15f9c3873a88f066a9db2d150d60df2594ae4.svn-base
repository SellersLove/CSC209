#!/bin/bash

#execute the *c file
./compile.sh wc209.c

# test for one single file
# 3 options
./wc209 t2.txt > 209-wc.txt
 wc t2.txt > real-wc.txt
 diff -u -b real-wc.txt 209-wc.txt
#2 options
./wc209 -wl t2.txt  > 209-wc.txt
 wc -wl t2.txt > real-wc.txt
 diff -u -b real-wc.txt 209-wc.txt
#1 options
./wc209 -w t2.txt > 209-wc.txt
 wc -w t2.txt > real-wc.txt
 diff -u -b real-wc.txt 209-wc.txt
 
 # test for more than one file
 # 3 options
 ./wc209 t1.txt t2.txt > 209-wc.txt
 wc t1.txt t2.txt > real-wc.txt
 diff -u -b real-wc.txt 209-wc.txt
# 2 options
 ./wc209 -wc t1.txt t2.txt > 209-wc.txt
 wc -wc t1.txt t2.txt > real-wc.txt
 diff -u -b real-wc.txt 209-wc.txt
# 1 option
 ./wc209 -c t1.txt t2.txt > 209-wc.txt
 wc -c t1.txt t2.txt > real-wc.txt
 diff -u -b real-wc.txt 209-wc.txt

 #test for echo

 # case1 1 line with \n
 # 3 options
 echo "first line\nsecond line" | wc -wlc > real-wc.txt
 echo "first line\nsecond line" | ./wc209 > 209-wc.txt
 diff -u -b real-wc.txt 209-wc.txt
 # 2 options
 echo "first line\nsecond line" | wc -wl > real-wc.txt
 echo "first line\nsecond line" | ./wc209 -wl > 209-wc.txt
 diff -u -b real-wc.txt 209-wc.txt
 # 1 option
 echo "first line\nsecond line" | wc -w > real-wc.txt
 echo "first line\nsecond line" | ./wc209 -w > 209-wc.txt
 diff -u -b real-wc.txt 209-wc.txt
 
 #case2 2 line with \n -e
 # 3 options
 echo -e "first line\nsecond line" | wc -wlc > real-wc.txt
 echo -e "first line\nsecond line" | ./wc209 > 209-wc.txt
 diff -u -b real-wc.txt 209-wc.txt
 # 2 options
 echo -e "first line\nsecond line" | wc -wc > real-wc.txt
 echo -e "first line\nsecond line" | ./wc209 -wc > 209-wc.txt
 diff -u -b real-wc.txt 209-wc.txt
 # 1 options
 echo -e "first line\nsecond line" | wc -c > real-wc.txt
 echo -e "first line\nsecond line" | ./wc209 -c > 209-wc.txt
 diff -u -b real-wc.txt 209-wc.txt
 #case2 2 line with \n -e -n
 # 3 options
 echo -e -n "first line\nsecond line" | wc -wlc > real-wc.txt
 echo -e -n "first line\nsecond line" | ./wc209 > 209-wc.txt
 diff -u -b real-wc.txt 209-wc.txt 
 # 2 options
 echo -e -n "first line\nsecond line" | wc -lc > real-wc.txt
 echo -e -n "first line\nsecond line" | ./wc209 -lc > 209-wc.txt
 diff -u -b real-wc.txt 209-wc.txt 
 # 1 options
 echo -e -n "first line\nsecond line" | wc -l > real-wc.txt
 echo -e -n "first line\nsecond line" | ./wc209 -l > 209-wc.txt
 diff -u -b real-wc.txt 209-wc.txt



