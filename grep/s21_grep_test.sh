#!/bin/bash

COUNT_YES=0
COUNT_NO=0
RES=""
RES_TEST="s21_grep.txt and grep.txt are identical"
TEST_F="patern.txt"

for var1 in -v -c -l -n -i
do
    for var2 in -v -c -l -n -i
    do 
        for var3 in -v -c -l -n -i
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
                then
                TEST1="for s21_grep.c s21_grep.h Makefile $var1 $var2 $var3"
                echo "$TEST1"
                ./s21_grep $TEST1 > s21_grep.txt
                grep $TEST1 > grep.txt
                RES="$(diff -s s21_grep.txt grep.txt)"
                if [ "$RES" == "$RES_TEST" ]
                    then 
                        ((COUNT_YES = COUNT_YES + 1))
                    else 
                        ((COUNT_NO = COUNT_NO + 1))
                fi
                TEST2="-e regex -e ^print s21_grep.c $var1 $var2 $var3"
                echo "$TEST2"
                ./s21_grep $TEST2 > s21_grep.txt
                grep $TEST2 > grep.txt
                RES="$(diff -s s21_grep.txt grep.txt)"
                if [ "$RES" == "$RES_TEST" ]
                    then 
                        ((COUNT_YES = COUNT_YES + 1))
                    else 
                        ((COUNT_NO = COUNT_NO + 1))
                fi
                TEST3="-f $TEST_T Makefile s21_grep.h $var1 $var2 $var3"
                echo "$TEST3"
                ./s21_grep $TEST3 > s21_grep.txt
                grep $TEST3 > grep.txt
                RES="$(diff -s s21_grep.txt grep.txt)"
                if [ "$RES" == "$RES_TEST" ]
                    then
                        ((COUNT_YES = COUNT_YES + 1))
                    else 
                        ((COUNT_NO = COUNT_NO + 1))
                fi
            fi
        done
    done
done 

rm s21_grep.txt grep.txt

echo "SUCCES: $COUNT_YES"
echo "FAIL: $COUNT_NO"