#!/bin/bash

#30 ja foi
for k in 35 40 45 50 100 200 300 400 500 600 700 800 900 1000
do
		c=1
		while [ $c -le 30 ]; 
		do
			#ran=$(( $RANDOM % 99999999 )); #ran=$(shuf -i 2000-65000 -n 1);
			ran=$(shuf -i 2000-9999999 -n 1);
			i=$k;
			./memetic8Obj$i $ran $i/k_trimmed/correlated/$i.corr1/$i.corr1_sampleFile.log $i/k_trimmed/correlated/$i.corr1/$i.corr1_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_trimmed/correlated/$i.corr1.in > $i/k_trimmed/correlated/$i.corr1/$i.corr1_"$c".out
			cd ..
			cd ..
			cd ..
			cd transgenetic/Testes/8_OBJETIVOS/
			./trans8Obj$i $ran $i/k_trimmed/correlated/$i.corr1/$i.corr1_sampleFile.log $i/k_trimmed/correlated/$i.corr1/$i.corr1_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_trimmed/correlated/$i.corr1.in > $i/k_trimmed/correlated/$i.corr1/$i.corr1_"$c".out
			cd ..
                        cd ..
                        cd ..
                        cd memetic_SEPA_R_naive/Testes/8_OBJETIVOS/
			./memetic8Obj$i $ran $i/k_trimmed/correlated/$i.corr1/$i.corr1_sampleFile.log $i/k_trimmed/correlated/$i.corr1/$i.corr1_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_trimmed/correlated/$i.corr1.in > $i/k_trimmed/correlated/$i.corr1/$i.corr1_"$c".out
			cd ..
                        cd ..
                        cd ..
			cd memetic_SEPA_R/Testes/8_OBJETIVOS/
			c=$((c+1))
		done 

		c=1
		while [ $c -le 30 ]; 
		do
			ran=$(shuf -i 2000-9999999 -n 1);
			i=$k;
			./memetic8Obj$i $ran $i/k_trimmed/correlated/$i.corr2/$i.corr2_sampleFile.log $i/k_trimmed/correlated/$i.corr2/$i.corr2_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_trimmed/correlated/$i.corr2.in > $i/k_trimmed/correlated/$i.corr2/$i.corr2_"$c".out
			cd ..
			cd ..
			cd ..
			cd transgenetic/Testes/8_OBJETIVOS/
			./trans8Obj$i $ran $i/k_trimmed/correlated/$i.corr2/$i.corr2_sampleFile.log $i/k_trimmed/correlated/$i.corr2/$i.corr2_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_trimmed/correlated/$i.corr2.in > $i/k_trimmed/correlated/$i.corr2/$i.corr2_"$c".out
			cd ..
                        cd ..
                        cd ..
                        cd memetic_SEPA_R_naive/Testes/8_OBJETIVOS/
			./memetic8Obj$i $ran $i/k_trimmed/correlated/$i.corr2/$i.corr2_sampleFile.log $i/k_trimmed/correlated/$i.corr2/$i.corr2_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_trimmed/correlated/$i.corr2.in > $i/k_trimmed/correlated/$i.corr2/$i.corr2_"$c".out
			cd ..
                        cd ..
                        cd ..
                        cd memetic_SEPA_R/Testes/8_OBJETIVOS/
			c=$((c+1))
		done 

		c=1
		while [ $c -le 30 ]; 
		do
			ran=$(shuf -i 2000-9999999 -n 1);
			i=$k;

			./memetic8Obj$i $ran $i/k_trimmed/correlated/$i.corr3/$i.corr3_sampleFile.log $i/k_trimmed/correlated/$i.corr3/$i.corr3_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_trimmed/correlated/$i.corr3.in > $i/k_trimmed/correlated/$i.corr3/$i.corr3_"$c".out
			cd ..
			cd ..
			cd ..
			cd transgenetic/Testes/8_OBJETIVOS/
			./trans8Obj$i $ran $i/k_trimmed/correlated/$i.corr3/$i.corr3_sampleFile.log $i/k_trimmed/correlated/$i.corr3/$i.corr3_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_trimmed/correlated/$i.corr3.in > $i/k_trimmed/correlated/$i.corr3/$i.corr3_"$c".out
			cd ..
                        cd ..
                        cd ..
                        cd memetic_SEPA_R_naive/Testes/8_OBJETIVOS/
			./memetic8Obj$i $ran $i/k_trimmed/correlated/$i.corr3/$i.corr3_sampleFile.log $i/k_trimmed/correlated/$i.corr3/$i.corr3_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_trimmed/correlated/$i.corr3.in > $i/k_trimmed/correlated/$i.corr3/$i.corr3_"$c".out
			cd ..
                        cd ..
                        cd ..
                        cd memetic_SEPA_R/Testes/8_OBJETIVOS/
			c=$((c+1))
		done 
			
		c=1
		while [ $c -le 30 ]; 
		do
			ran=$(shuf -i 2000-9999999 -n 1);
			i=$k;

			./memetic8Obj$i $ran $i/k_trimmed/anticorrelated/$i.anticorr1/$i.anticorr1_sampleFile.log $i/k_trimmed/anticorrelated/$i.anticorr1/$i.anticorr1_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_trimmed/anticorrelated/$i.anticorr1.in > $i/k_trimmed/anticorrelated/$i.anticorr1/$i.anticorr1_"$c".out
			cd ..
			cd ..
			cd ..
			cd transgenetic/Testes/8_OBJETIVOS/
			./trans8Obj$i $ran $i/k_trimmed/anticorrelated/$i.anticorr1/$i.anticorr1_sampleFile.log $i/k_trimmed/anticorrelated/$i.anticorr1/$i.anticorr1_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_trimmed/anticorrelated/$i.anticorr1.in > $i/k_trimmed/anticorrelated/$i.anticorr1/$i.anticorr1_"$c".out
			cd ..
                        cd ..
                        cd ..
                        cd memetic_SEPA_R_naive/Testes/8_OBJETIVOS/
			./memetic8Obj$i $ran $i/k_trimmed/anticorrelated/$i.anticorr1/$i.anticorr1_sampleFile.log $i/k_trimmed/anticorrelated/$i.anticorr1/$i.anticorr1_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_trimmed/anticorrelated/$i.anticorr1.in > $i/k_trimmed/anticorrelated/$i.anticorr1/$i.anticorr1_"$c".out
			cd ..
                        cd ..
                        cd ..
                        cd memetic_SEPA_R/Testes/8_OBJETIVOS/
			c=$((c+1))
		done 	

		c=1
		while [ $c -le 30 ]; 
		do
			ran=$(shuf -i 2000-9999999 -n 1);
			i=$k;
			./memetic8Obj$i $ran $i/k_trimmed/anticorrelated/$i.anticorr2/$i.anticorr2_sampleFile.log $i/k_trimmed/anticorrelated/$i.anticorr2/$i.anticorr2_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_trimmed/anticorrelated/$i.anticorr2.in > $i/k_trimmed/anticorrelated/$i.anticorr2/$i.anticorr2_"$c".out
			cd ..
			cd ..
			cd ..
			cd transgenetic/Testes/8_OBJETIVOS/
			./trans8Obj$i $ran $i/k_trimmed/anticorrelated/$i.anticorr2/$i.anticorr2_sampleFile.log $i/k_trimmed/anticorrelated/$i.anticorr2/$i.anticorr2_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_trimmed/anticorrelated/$i.anticorr2.in > $i/k_trimmed/anticorrelated/$i.anticorr2/$i.anticorr2_"$c".out
			cd ..
                        cd ..
                        cd ..
                        cd memetic_SEPA_R_naive/Testes/8_OBJETIVOS/
			./memetic8Obj$i $ran $i/k_trimmed/anticorrelated/$i.anticorr2/$i.anticorr2_sampleFile.log $i/k_trimmed/anticorrelated/$i.anticorr2/$i.anticorr2_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_trimmed/anticorrelated/$i.anticorr2.in > $i/k_trimmed/anticorrelated/$i.anticorr2/$i.anticorr2_"$c".out
			cd ..
                        cd ..
                        cd ..
                        cd memetic_SEPA_R/Testes/8_OBJETIVOS/
			c=$((c+1))
		done 	

		c=1
		while [ $c -le 30 ]; 
		do
			ran=$(shuf -i 2000-9999999 -n 1);
			i=$k;			
			./memetic8Obj$i $ran $i/k_trimmed/anticorrelated/$i.anticorr3/$i.anticorr3_sampleFile.log $i/k_trimmed/anticorrelated/$i.anticorr3/$i.anticorr3_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_trimmed/anticorrelated/$i.anticorr3.in > $i/k_trimmed/anticorrelated/$i.anticorr3/$i.anticorr3_"$c".out
			cd ..
			cd ..
			cd ..
			cd transgenetic/Testes/8_OBJETIVOS/
			./trans8Obj$i  $ran $i/k_trimmed/anticorrelated/$i.anticorr3/$i.anticorr3_sampleFile.log $i/k_trimmed/anticorrelated/$i.anticorr3/$i.anticorr3_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_trimmed/anticorrelated/$i.anticorr3.in > $i/k_trimmed/anticorrelated/$i.anticorr3/$i.anticorr3_"$c".out
			cd ..
                        cd ..
                        cd ..
                        cd memetic_SEPA_R_naive/Testes/8_OBJETIVOS/
			./memetic8Obj$i $ran $i/k_trimmed/anticorrelated/$i.anticorr3/$i.anticorr3_sampleFile.log $i/k_trimmed/anticorrelated/$i.anticorr3/$i.anticorr3_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_trimmed/anticorrelated/$i.anticorr3.in > $i/k_trimmed/anticorrelated/$i.anticorr3/$i.anticorr3_"$c".out
			cd ..
                        cd ..
                        cd ..
                        cd memetic_SEPA_R/Testes/8_OBJETIVOS/
			c=$((c+1))
		done 







		c=1
		while [ $c -le 30 ]; 
		do
			#ran=$(( $RANDOM % 99999999 )); #ran=$(shuf -i 2000-65000 -n 1);
			ran=$(shuf -i 2000-9999999 -n 1);
			i=$k;
			./memetic8Obj$i $ran $i/k_centrum/correlated/$i.corr1/$i.corr1_sampleFile.log $i/k_centrum/correlated/$i.corr1/$i.corr1_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_centrum/correlated/$i.corr1.in > $i/k_centrum/correlated/$i.corr1/$i.corr1_"$c".out
			cd ..
			cd ..
			cd ..
			cd transgenetic/Testes/8_OBJETIVOS/
			./trans8Obj$i $ran $i/k_centrum/correlated/$i.corr1/$i.corr1_sampleFile.log $i/k_centrum/correlated/$i.corr1/$i.corr1_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_centrum/correlated/$i.corr1.in > $i/k_centrum/correlated/$i.corr1/$i.corr1_"$c".out
			cd ..
                        cd ..
                        cd ..
                        cd memetic_SEPA_R_naive/Testes/8_OBJETIVOS/
			./memetic8Obj$i $ran $i/k_centrum/correlated/$i.corr1/$i.corr1_sampleFile.log $i/k_centrum/correlated/$i.corr1/$i.corr1_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_centrum/correlated/$i.corr1.in > $i/k_centrum/correlated/$i.corr1/$i.corr1_"$c".out
			cd ..
                        cd ..
                        cd ..
			cd memetic_SEPA_R/Testes/8_OBJETIVOS/
			c=$((c+1))
		done 

		c=1
		while [ $c -le 30 ]; 
		do
			ran=$(shuf -i 2000-9999999 -n 1);
			i=$k;
			./memetic8Obj$i $ran $i/k_centrum/correlated/$i.corr2/$i.corr2_sampleFile.log $i/k_centrum/correlated/$i.corr2/$i.corr2_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_centrum/correlated/$i.corr2.in > $i/k_centrum/correlated/$i.corr2/$i.corr2_"$c".out
			cd ..
			cd ..
			cd ..
			cd transgenetic/Testes/8_OBJETIVOS/
			./trans8Obj$i $ran $i/k_centrum/correlated/$i.corr2/$i.corr2_sampleFile.log $i/k_centrum/correlated/$i.corr2/$i.corr2_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_centrum/correlated/$i.corr2.in > $i/k_centrum/correlated/$i.corr2/$i.corr2_"$c".out
			cd ..
                        cd ..
                        cd ..
                        cd memetic_SEPA_R_naive/Testes/8_OBJETIVOS/
			./memetic8Obj$i $ran $i/k_centrum/correlated/$i.corr2/$i.corr2_sampleFile.log $i/k_centrum/correlated/$i.corr2/$i.corr2_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_centrum/correlated/$i.corr2.in > $i/k_centrum/correlated/$i.corr2/$i.corr2_"$c".out
			cd ..
                        cd ..
                        cd ..
                        cd memetic_SEPA_R/Testes/8_OBJETIVOS/
			c=$((c+1))
		done 

		c=1
		while [ $c -le 30 ]; 
		do
			ran=$(shuf -i 2000-9999999 -n 1);
			i=$k;

			./memetic8Obj$i $ran $i/k_centrum/correlated/$i.corr3/$i.corr3_sampleFile.log $i/k_centrum/correlated/$i.corr3/$i.corr3_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_centrum/correlated/$i.corr3.in > $i/k_centrum/correlated/$i.corr3/$i.corr3_"$c".out
			cd ..
			cd ..
			cd ..
			cd transgenetic/Testes/8_OBJETIVOS/
			./trans8Obj$i $ran $i/k_centrum/correlated/$i.corr3/$i.corr3_sampleFile.log $i/k_centrum/correlated/$i.corr3/$i.corr3_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_centrum/correlated/$i.corr3.in > $i/k_centrum/correlated/$i.corr3/$i.corr3_"$c".out
			cd ..
                        cd ..
                        cd ..
                        cd memetic_SEPA_R_naive/Testes/8_OBJETIVOS/
			./memetic8Obj$i $ran $i/k_centrum/correlated/$i.corr3/$i.corr3_sampleFile.log $i/k_centrum/correlated/$i.corr3/$i.corr3_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_centrum/correlated/$i.corr3.in > $i/k_centrum/correlated/$i.corr3/$i.corr3_"$c".out
			cd ..
                        cd ..
                        cd ..
                        cd memetic_SEPA_R/Testes/8_OBJETIVOS/
			c=$((c+1))
		done 
			
		c=1
		while [ $c -le 30 ]; 
		do
			ran=$(shuf -i 2000-9999999 -n 1);
			i=$k;

			./memetic8Obj$i $ran $i/k_centrum/anticorrelated/$i.anticorr1/$i.anticorr1_sampleFile.log $i/k_centrum/anticorrelated/$i.anticorr1/$i.anticorr1_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_centrum/anticorrelated/$i.anticorr1.in > $i/k_centrum/anticorrelated/$i.anticorr1/$i.anticorr1_"$c".out
			cd ..
			cd ..
			cd ..
			cd transgenetic/Testes/8_OBJETIVOS/
			./trans8Obj$i $ran $i/k_centrum/anticorrelated/$i.anticorr1/$i.anticorr1_sampleFile.log $i/k_centrum/anticorrelated/$i.anticorr1/$i.anticorr1_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_centrum/anticorrelated/$i.anticorr1.in > $i/k_centrum/anticorrelated/$i.anticorr1/$i.anticorr1_"$c".out
			cd ..
                        cd ..
                        cd ..
                        cd memetic_SEPA_R_naive/Testes/8_OBJETIVOS/
			./memetic8Obj$i $ran $i/k_centrum/anticorrelated/$i.anticorr1/$i.anticorr1_sampleFile.log $i/k_centrum/anticorrelated/$i.anticorr1/$i.anticorr1_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_centrum/anticorrelated/$i.anticorr1.in > $i/k_centrum/anticorrelated/$i.anticorr1/$i.anticorr1_"$c".out
			cd ..
                        cd ..
                        cd ..
                        cd memetic_SEPA_R/Testes/8_OBJETIVOS/
			c=$((c+1))
		done 	

		c=1
		while [ $c -le 30 ]; 
		do
			ran=$(shuf -i 2000-9999999 -n 1);
			i=$k;
			./memetic8Obj$i $ran $i/k_centrum/anticorrelated/$i.anticorr2/$i.anticorr2_sampleFile.log $i/k_centrum/anticorrelated/$i.anticorr2/$i.anticorr2_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_centrum/anticorrelated/$i.anticorr2.in > $i/k_centrum/anticorrelated/$i.anticorr2/$i.anticorr2_"$c".out
			cd ..
			cd ..
			cd ..
			cd transgenetic/Testes/8_OBJETIVOS/
			./trans8Obj$i $ran $i/k_centrum/anticorrelated/$i.anticorr2/$i.anticorr2_sampleFile.log $i/k_centrum/anticorrelated/$i.anticorr2/$i.anticorr2_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_centrum/anticorrelated/$i.anticorr2.in > $i/k_centrum/anticorrelated/$i.anticorr2/$i.anticorr2_"$c".out
			cd ..
                        cd ..
                        cd ..
                        cd memetic_SEPA_R_naive/Testes/8_OBJETIVOS/
			./memetic8Obj$i $ran $i/k_centrum/anticorrelated/$i.anticorr2/$i.anticorr2_sampleFile.log $i/k_centrum/anticorrelated/$i.anticorr2/$i.anticorr2_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_centrum/anticorrelated/$i.anticorr2.in > $i/k_centrum/anticorrelated/$i.anticorr2/$i.anticorr2_"$c".out
			cd ..
                        cd ..
                        cd ..
                        cd memetic_SEPA_R/Testes/8_OBJETIVOS/
			c=$((c+1))
		done 	

		c=1
		while [ $c -le 30 ]; 
		do
			ran=$(shuf -i 2000-9999999 -n 1);
			i=$k;			
			./memetic8Obj$i $ran $i/k_centrum/anticorrelated/$i.anticorr3/$i.anticorr3_sampleFile.log $i/k_centrum/anticorrelated/$i.anticorr3/$i.anticorr3_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_centrum/anticorrelated/$i.anticorr3.in > $i/k_centrum/anticorrelated/$i.anticorr3/$i.anticorr3_"$c".out
			cd ..
			cd ..
			cd ..
			cd transgenetic/Testes/8_OBJETIVOS/
			./trans8Obj$i  $ran $i/k_centrum/anticorrelated/$i.anticorr3/$i.anticorr3_sampleFile.log $i/k_centrum/anticorrelated/$i.anticorr3/$i.anticorr3_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_centrum/anticorrelated/$i.anticorr3.in > $i/k_centrum/anticorrelated/$i.anticorr3/$i.anticorr3_"$c".out
			cd ..
                        cd ..
                        cd ..
                        cd memetic_SEPA_R_naive/Testes/8_OBJETIVOS/
			./memetic8Obj$i $ran $i/k_centrum/anticorrelated/$i.anticorr3/$i.anticorr3_sampleFile.log $i/k_centrum/anticorrelated/$i.anticorr3/$i.anticorr3_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/k_centrum/anticorrelated/$i.anticorr3.in > $i/k_centrum/anticorrelated/$i.anticorr3/$i.anticorr3_"$c".out
			cd ..
                        cd ..
                        cd ..
                        cd memetic_SEPA_R/Testes/8_OBJETIVOS/
			c=$((c+1))
		done 




		c=1
		while [ $c -le 30 ]; 
		do
			#ran=$(( $RANDOM % 99999999 )); #ran=$(shuf -i 2000-65000 -n 1);
			ran=$(shuf -i 2000-9999999 -n 1);
			i=$k;
			./memetic8Obj$i $ran $i/Hurwicz/correlated/$i.corr1/$i.corr1_sampleFile.log $i/Hurwicz/correlated/$i.corr1/$i.corr1_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/Hurwicz/correlated/$i.corr1.in > $i/Hurwicz/correlated/$i.corr1/$i.corr1_"$c".out
			cd ..
			cd ..
			cd ..
			cd transgenetic/Testes/8_OBJETIVOS/
			./trans8Obj$i $ran $i/Hurwicz/correlated/$i.corr1/$i.corr1_sampleFile.log $i/Hurwicz/correlated/$i.corr1/$i.corr1_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/Hurwicz/correlated/$i.corr1.in > $i/Hurwicz/correlated/$i.corr1/$i.corr1_"$c".out
			cd ..
                        cd ..
                        cd ..
                        cd memetic_SEPA_R_naive/Testes/8_OBJETIVOS/
			./memetic8Obj$i $ran $i/Hurwicz/correlated/$i.corr1/$i.corr1_sampleFile.log $i/Hurwicz/correlated/$i.corr1/$i.corr1_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/Hurwicz/correlated/$i.corr1.in > $i/Hurwicz/correlated/$i.corr1/$i.corr1_"$c".out
			cd ..
                        cd ..
                        cd ..
			cd memetic_SEPA_R/Testes/8_OBJETIVOS/
			c=$((c+1))
		done 

		c=1
		while [ $c -le 30 ]; 
		do
			ran=$(shuf -i 2000-9999999 -n 1);
			i=$k;
			./memetic8Obj$i $ran $i/Hurwicz/correlated/$i.corr2/$i.corr2_sampleFile.log $i/Hurwicz/correlated/$i.corr2/$i.corr2_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/Hurwicz/correlated/$i.corr2.in > $i/Hurwicz/correlated/$i.corr2/$i.corr2_"$c".out
			cd ..
			cd ..
			cd ..
			cd transgenetic/Testes/8_OBJETIVOS/
			./trans8Obj$i $ran $i/Hurwicz/correlated/$i.corr2/$i.corr2_sampleFile.log $i/Hurwicz/correlated/$i.corr2/$i.corr2_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/Hurwicz/correlated/$i.corr2.in > $i/Hurwicz/correlated/$i.corr2/$i.corr2_"$c".out
			cd ..
                        cd ..
                        cd ..
                        cd memetic_SEPA_R_naive/Testes/8_OBJETIVOS/
			./memetic8Obj$i $ran $i/Hurwicz/correlated/$i.corr2/$i.corr2_sampleFile.log $i/Hurwicz/correlated/$i.corr2/$i.corr2_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/Hurwicz/correlated/$i.corr2.in > $i/Hurwicz/correlated/$i.corr2/$i.corr2_"$c".out
			cd ..
                        cd ..
                        cd ..
                        cd memetic_SEPA_R/Testes/8_OBJETIVOS/
			c=$((c+1))
		done 

		c=1
		while [ $c -le 30 ]; 
		do
			ran=$(shuf -i 2000-9999999 -n 1);
			i=$k;

			./memetic8Obj$i $ran $i/Hurwicz/correlated/$i.corr3/$i.corr3_sampleFile.log $i/Hurwicz/correlated/$i.corr3/$i.corr3_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/Hurwicz/correlated/$i.corr3.in > $i/Hurwicz/correlated/$i.corr3/$i.corr3_"$c".out
			cd ..
			cd ..
			cd ..
			cd transgenetic/Testes/8_OBJETIVOS/
			./trans8Obj$i $ran $i/Hurwicz/correlated/$i.corr3/$i.corr3_sampleFile.log $i/Hurwicz/correlated/$i.corr3/$i.corr3_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/Hurwicz/correlated/$i.corr3.in > $i/Hurwicz/correlated/$i.corr3/$i.corr3_"$c".out
			cd ..
                        cd ..
                        cd ..
                        cd memetic_SEPA_R_naive/Testes/8_OBJETIVOS/
			./memetic8Obj$i $ran $i/Hurwicz/correlated/$i.corr3/$i.corr3_sampleFile.log $i/Hurwicz/correlated/$i.corr3/$i.corr3_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/Hurwicz/correlated/$i.corr3.in > $i/Hurwicz/correlated/$i.corr3/$i.corr3_"$c".out
			cd ..
                        cd ..
                        cd ..
                        cd memetic_SEPA_R/Testes/8_OBJETIVOS/
			c=$((c+1))
		done 
			
		c=1
		while [ $c -le 30 ]; 
		do
			ran=$(shuf -i 2000-9999999 -n 1);
			i=$k;

			./memetic8Obj$i $ran $i/Hurwicz/anticorrelated/$i.anticorr1/$i.anticorr1_sampleFile.log $i/Hurwicz/anticorrelated/$i.anticorr1/$i.anticorr1_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/Hurwicz/anticorrelated/$i.anticorr1.in > $i/Hurwicz/anticorrelated/$i.anticorr1/$i.anticorr1_"$c".out
			cd ..
			cd ..
			cd ..
			cd transgenetic/Testes/8_OBJETIVOS/
			./trans8Obj$i $ran $i/Hurwicz/anticorrelated/$i.anticorr1/$i.anticorr1_sampleFile.log $i/Hurwicz/anticorrelated/$i.anticorr1/$i.anticorr1_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/Hurwicz/anticorrelated/$i.anticorr1.in > $i/Hurwicz/anticorrelated/$i.anticorr1/$i.anticorr1_"$c".out
			cd ..
                        cd ..
                        cd ..
                        cd memetic_SEPA_R_naive/Testes/8_OBJETIVOS/
			./memetic8Obj$i $ran $i/Hurwicz/anticorrelated/$i.anticorr1/$i.anticorr1_sampleFile.log $i/Hurwicz/anticorrelated/$i.anticorr1/$i.anticorr1_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/Hurwicz/anticorrelated/$i.anticorr1.in > $i/Hurwicz/anticorrelated/$i.anticorr1/$i.anticorr1_"$c".out
			cd ..
                        cd ..
                        cd ..
                        cd memetic_SEPA_R/Testes/8_OBJETIVOS/
			c=$((c+1))
		done 	

		c=1
		while [ $c -le 30 ]; 
		do
			ran=$(shuf -i 2000-9999999 -n 1);
			i=$k;
			./memetic8Obj$i $ran $i/Hurwicz/anticorrelated/$i.anticorr2/$i.anticorr2_sampleFile.log $i/Hurwicz/anticorrelated/$i.anticorr2/$i.anticorr2_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/Hurwicz/anticorrelated/$i.anticorr2.in > $i/Hurwicz/anticorrelated/$i.anticorr2/$i.anticorr2_"$c".out
			cd ..
			cd ..
			cd ..
			cd transgenetic/Testes/8_OBJETIVOS/
			./trans8Obj$i $ran $i/Hurwicz/anticorrelated/$i.anticorr2/$i.anticorr2_sampleFile.log $i/Hurwicz/anticorrelated/$i.anticorr2/$i.anticorr2_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/Hurwicz/anticorrelated/$i.anticorr2.in > $i/Hurwicz/anticorrelated/$i.anticorr2/$i.anticorr2_"$c".out
			cd ..
                        cd ..
                        cd ..
                        cd memetic_SEPA_R_naive/Testes/8_OBJETIVOS/
			./memetic8Obj$i $ran $i/Hurwicz/anticorrelated/$i.anticorr2/$i.anticorr2_sampleFile.log $i/Hurwicz/anticorrelated/$i.anticorr2/$i.anticorr2_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/Hurwicz/anticorrelated/$i.anticorr2.in > $i/Hurwicz/anticorrelated/$i.anticorr2/$i.anticorr2_"$c".out
			cd ..
                        cd ..
                        cd ..
                        cd memetic_SEPA_R/Testes/8_OBJETIVOS/
			c=$((c+1))
		done 	

		c=1
		while [ $c -le 30 ]; 
		do
			ran=$(shuf -i 2000-9999999 -n 1);
			i=$k;			
			./memetic8Obj$i $ran $i/Hurwicz/anticorrelated/$i.anticorr3/$i.anticorr3_sampleFile.log $i/Hurwicz/anticorrelated/$i.anticorr3/$i.anticorr3_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/Hurwicz/anticorrelated/$i.anticorr3.in > $i/Hurwicz/anticorrelated/$i.anticorr3/$i.anticorr3_"$c".out
			cd ..
			cd ..
			cd ..
			cd transgenetic/Testes/8_OBJETIVOS/
			./trans8Obj$i  $ran $i/Hurwicz/anticorrelated/$i.anticorr3/$i.anticorr3_sampleFile.log $i/Hurwicz/anticorrelated/$i.anticorr3/$i.anticorr3_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/Hurwicz/anticorrelated/$i.anticorr3.in > $i/Hurwicz/anticorrelated/$i.anticorr3/$i.anticorr3_"$c".out
			cd ..
                        cd ..
                        cd ..
                        cd memetic_SEPA_R_naive/Testes/8_OBJETIVOS/
			./memetic8Obj$i $ran $i/Hurwicz/anticorrelated/$i.anticorr3/$i.anticorr3_sampleFile.log $i/Hurwicz/anticorrelated/$i.anticorr3/$i.anticorr3_timeFile.log < ../../../INSTANCES/8_OBJETIVOS/Hurwicz/anticorrelated/$i.anticorr3.in > $i/Hurwicz/anticorrelated/$i.anticorr3/$i.anticorr3_"$c".out
			cd ..
                        cd ..
                        cd ..
                        cd memetic_SEPA_R/Testes/8_OBJETIVOS/
			c=$((c+1))
		done 






done
