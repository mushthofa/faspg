#!/bin/bash

for n in `seq 5 30`;
do
	for k in `seq 5 5`;
	do
		echo "$n $k"
		for i in `seq 1 5`;
		do
			./gennet $n $k >  newinst/net-$n-$k-$i.txt
			sleep 1
		done
	done 
done

