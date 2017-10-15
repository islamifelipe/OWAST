#!/bin/bash


for i in 200
do
		c=1
		while [ $c -le 30 ]; 
		do
			ran=$(( $RANDOM % 9999999 )); #ran=$(shuf -i 2000-65000 -n 1);
			#ran=$(shuf -i 2000-999999 -n 1);
			#i=$k;
			./memeticTeste $ran $i.corr1_sampleFile.log $i.corr1_timeFile.log < ../INSTANCES/10_OBJETIVOS/Hurwicz/correlated/$i.corr1.in
			cd ..
			cd transgenetic/
			./trans10Obj400 $ran $i.corr1_sampleFile.log $i.corr1_timeFile.log < ../INSTANCES/10_OBJETIVOS/Hurwicz/correlated/$i.corr1.in
			c=$((c+1))
			cd ..
			cd memetic_SEPA_R/
		done 

done