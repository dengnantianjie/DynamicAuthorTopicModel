#!/bin/bash
for x in "00000" "01631" "03510" "05350" "07200" "08947" "10650" "12405" "13976" "15515" "17357" "19136" "20448" "21765" "23366" "25081" "26843" "28588" "30155" "31930" "33646" "35310"
do
        python doctopic_topic_all.py $x
        echo $x
done
