#!/bin/bash

for n in `seq 5 30`;
do
	for k in `seq 1 4`;
	do
		for i in `seq 1 5`;
		do
			echo "$n $k" >> asyntimenew.txt
			echo "$n $k" >> asynoutnew.txt
			/usr/bin/time --output=asyntimenew.txt -a  -f "%e %M" sh -c "./newfaspga 5 < newinst/net-$n-$k-$i.txt | clingo -n 0 --verbose=0 -W no-atom-undefined --time-limit=600 | grep -v SAT | sort | uniq | wc -l >> asynoutnew.txt"
		done
	done 
done

