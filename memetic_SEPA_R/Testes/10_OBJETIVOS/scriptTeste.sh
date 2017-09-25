#!/bin/bash


for i in 30 35 40 45 50 100 200 300 400 500
do
	c=1
		while [ $c -le 30 ]; 
		do
			ran=$(( $RANDOM % 99999999 )); #ran=$(shuf -i 2000-65000 -n 1);
			

			./memetic10Obj$i $ran $i/k_trimmed/correlated/$i.corr1/$i.corr1_sampleFile.log $i/k_trimmed/correlated/$i.corr1/$i.corr1_timeFile.log < ../../../INSTANCES/10_OBJETIVOS/k_trimmed/correlated/$i.corr1.in > $i/k_trimmed/correlated/$i.corr1/$i.corr1_"$c".out
			
			./memetic10Obj$i $ran $i/k_trimmed/correlated/$i.corr2/$i.corr2_sampleFile.log $i/k_trimmed/correlated/$i.corr2/$i.corr2_timeFile.log < ../../../INSTANCES/10_OBJETIVOS/k_trimmed/correlated/$i.corr2.in > $i/k_trimmed/correlated/$i.corr2/$i.corr2_"$c".out
			
			./memetic10Obj$i $ran $i/k_trimmed/correlated/$i.corr3/$i.corr3_sampleFile.log $i/k_trimmed/correlated/$i.corr3/$i.corr3_timeFile.log < ../../../INSTANCES/10_OBJETIVOS/k_trimmed/correlated/$i.corr3.in > $i/k_trimmed/correlated/$i.corr3/$i.corr3_"$c".out
			
			./memetic10Obj$i $ran $i/k_trimmed/anticorrelated/$i.anticorr1/$i.anticorr1_sampleFile.log $i/k_trimmed/anticorrelated/$i.anticorr1/$i.anticorr1_timeFile.log < ../../../INSTANCES/10_OBJETIVOS/k_trimmed/anticorrelated/$i.anticorr1.in > $i/k_trimmed/anticorrelated/$i.anticorr1/$i.anticorr1_"$c".out
						
			./memetic10Obj$i $ran $i/k_trimmed/anticorrelated/$i.anticorr2/$i.anticorr2_sampleFile.log $i/k_trimmed/anticorrelated/$i.anticorr2/$i.anticorr2_timeFile.log < ../../../INSTANCES/10_OBJETIVOS/k_trimmed/anticorrelated/$i.anticorr2.in > $i/k_trimmed/anticorrelated/$i.anticorr2/$i.anticorr2_"$c".out
						
			./memetic10Obj$i $ran $i/k_trimmed/anticorrelated/$i.anticorr3/$i.anticorr3_sampleFile.log $i/k_trimmed/anticorrelated/$i.anticorr3/$i.anticorr3_timeFile.log < ../../../INSTANCES/10_OBJETIVOS/k_trimmed/anticorrelated/$i.anticorr3.in > $i/k_trimmed/anticorrelated/$i.anticorr3/$i.anticorr3_"$c".out
			

			c=$((c+1))
		done 
done