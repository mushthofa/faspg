#!/bin/bash

for n in `seq 5 30`;
do
	for k in `seq 1 4`;
	do
		for i in `seq 1 5`;
		do
			echo "$n $k" >> syncyctimenew.txt
			echo "$n $k" >> syncycoutnew.txt
			/usr/bin/time --output=syncyctimenew.txt -a  -f "%e %M" sh -c "./faspga 0 5 < newinst/net-$n-$k-$i.txt | clingo -n $n --verbose=0 -W no-atom-undefined --time-limit=600 | grep -v SAT | sort | uniq | wc -l >> syncycoutnew.txt"
		done
	done 
done

