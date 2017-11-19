#!/bin/bash

for s in 1 10 100 1000 10000 100000 1000000 ;do
	rm *.tape
	./gen/gentext.o $s | ./gen/tobin.out > stage.tape
	for b in 33 330 3300 ;do
		for n in 3 10 100 1000;do
		cp stage.tape input.tape;
		echo "$n bufers  $b bytes big sort  $s records"
		./main/sort.out  $n $b -d
		done
	done
done
