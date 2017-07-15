#!/bin/bash

for n in `seq 5 30`;
do
	for k in `seq 1 4`;
	do
		echo "$n $k"
		for i in `seq 1 5`;
		do
			echo "$n $k">> newsteadytime.txt
			echo "$n $k">> newsteadyoutput.txt
			/usr/bin/time --output=newsteadytime.txt -a -f "%e %M"  sh -c "./faspg < newinst/net-$n-$k-$i.txt | clingo -n 0 --verbose=0 -W no-atom-undefined >> newsteadyoutput.txt"
		done
	done 
done

