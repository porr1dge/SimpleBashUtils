#!/bin/bush

COUNT_YES=0
COUNT_NO=0
RES=""
RES_TEST="Files s21_cat.txt and cat.txt are identical"
TEST_F="case.txt"

for var in -b -e -n -s -t -v 
do
          TEST1="$var $TEST_F"
          echo "$TEST1"
          ./s21_cat $TEST1 > s21_cat.txt
          cat $TEST1 > cat.txt
          RES_TEST="$(diff -s s21_cat.txt cat.txt)"
          if [ "$RES_TEST" = "$RES_TEST" ]
            then
              (( COUNT_YES=COUNT_YES+1 ))
            else
              echo "$TEST1" >> log.txt
              (( COUNT_NO=COUNT_NO+1 ))
          fi
          rm s21_cat.txt cat.txt
done

for var in -b -e -n -s -t -v 
do
  for var2 in -b -e -n -s -t -v 
  do
        if [ $var != $var2 ]
        then
          TEST1="$var $var2 $TEST_F"
          echo "$TEST1"
          ./s21_cat $TEST1 > s21_cat.txt
          cat $TEST1 > cat.txt
          DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
          if [ "$RES_TEST" == "$RES_TEST" ]
            then
              (( COUNT_YES=COUNT_YES+1 ))
            else
              echo "$TEST1" >> log.txt
              (( COUNT_NO=COUNT_NO+1 ))
          fi
          rm s21_cat.txt cat.txt
        fi
  done
done

echo "SUCCESS: $COUNT_YES"
echo "FAIL: $COUNT_NO"