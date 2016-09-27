#!/bin/bash
for x in "00000" "03510" "07200" "10650" "13976" "17357" "20448" "23366" "26843" "30155" "33646"
#for x in "00000" 
do
        python doctopic_topic_all.py $x
        echo $x
done

python combine.py
