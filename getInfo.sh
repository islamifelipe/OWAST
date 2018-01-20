#!/bin/bash


for i in 30 35 40 45 50 100 200 300 400 500 600 700 800 900 1000
do
	c=1
	while [ $c -le 30 ]; 
    do
    	./getInfo <  transgenetic64bit/Testes/5_OBJETIVOS/$i/k_trimmed/correlated/$i.corr1/$i.corr1_"$c".out  >> transgenetic64bit/Testes/5_OBJETIVOS/$i/k_trimmed/correlated/$i.corr1/$i.corr1_saTrans.log
		./getInfo <  transgenetic64bit/Testes/5_OBJETIVOS/$i/k_trimmed/correlated/$i.corr2/$i.corr2_"$c".out  >> transgenetic64bit/Testes/5_OBJETIVOS/$i/k_trimmed/correlated/$i.corr2/$i.corr2_saTrans.log
		./getInfo <  transgenetic64bit/Testes/5_OBJETIVOS/$i/k_trimmed/correlated/$i.corr3/$i.corr3_"$c".out  >> transgenetic64bit/Testes/5_OBJETIVOS/$i/k_trimmed/correlated/$i.corr3/$i.corr3_saTrans.log
		
		./getInfo <  transgenetic64bit/Testes/5_OBJETIVOS/$i/k_trimmed/anticorrelated/$i.anticorr1/$i.anticorr1_"$c".out  >> transgenetic64bit/Testes/5_OBJETIVOS/$i/k_trimmed/anticorrelated/$i.anticorr1/$i.anticorr1_saTrans.log
		./getInfo <  transgenetic64bit/Testes/5_OBJETIVOS/$i/k_trimmed/anticorrelated/$i.anticorr2/$i.anticorr2_"$c".out  >> transgenetic64bit/Testes/5_OBJETIVOS/$i/k_trimmed/anticorrelated/$i.anticorr2/$i.anticorr2_saTrans.log
		./getInfo <  transgenetic64bit/Testes/5_OBJETIVOS/$i/k_trimmed/anticorrelated/$i.anticorr3/$i.anticorr3_"$c".out  >> transgenetic64bit/Testes/5_OBJETIVOS/$i/k_trimmed/anticorrelated/$i.anticorr3/$i.anticorr3_saTrans.log
		

		./getInfo <  transgenetic64bit/Testes/5_OBJETIVOS/$i/k_centrum/correlated/$i.corr1/$i.corr1_"$c".out  >> transgenetic64bit/Testes/5_OBJETIVOS/$i/k_centrum/correlated/$i.corr1/$i.corr1_saTrans.log
		./getInfo <  transgenetic64bit/Testes/5_OBJETIVOS/$i/k_centrum/correlated/$i.corr2/$i.corr2_"$c".out  >> transgenetic64bit/Testes/5_OBJETIVOS/$i/k_centrum/correlated/$i.corr2/$i.corr2_saTrans.log
		./getInfo <  transgenetic64bit/Testes/5_OBJETIVOS/$i/k_centrum/correlated/$i.corr3/$i.corr3_"$c".out  >> transgenetic64bit/Testes/5_OBJETIVOS/$i/k_centrum/correlated/$i.corr3/$i.corr3_saTrans.log
		
		./getInfo <  transgenetic64bit/Testes/5_OBJETIVOS/$i/k_centrum/anticorrelated/$i.anticorr1/$i.anticorr1_"$c".out  >> transgenetic64bit/Testes/5_OBJETIVOS/$i/k_centrum/anticorrelated/$i.anticorr1/$i.anticorr1_saTrans.log
		./getInfo <  transgenetic64bit/Testes/5_OBJETIVOS/$i/k_centrum/anticorrelated/$i.anticorr2/$i.anticorr2_"$c".out  >> transgenetic64bit/Testes/5_OBJETIVOS/$i/k_centrum/anticorrelated/$i.anticorr2/$i.anticorr2_saTrans.log
		./getInfo <  transgenetic64bit/Testes/5_OBJETIVOS/$i/k_centrum/anticorrelated/$i.anticorr3/$i.anticorr3_"$c".out  >> transgenetic64bit/Testes/5_OBJETIVOS/$i/k_centrum/anticorrelated/$i.anticorr3/$i.anticorr3_saTrans.log
		

		./getInfo <  transgenetic64bit/Testes/5_OBJETIVOS/$i/Hurwicz/correlated/$i.corr1/$i.corr1_"$c".out  >> transgenetic64bit/Testes/5_OBJETIVOS/$i/Hurwicz/correlated/$i.corr1/$i.corr1_saTrans.log
		./getInfo <  transgenetic64bit/Testes/5_OBJETIVOS/$i/Hurwicz/correlated/$i.corr2/$i.corr2_"$c".out  >> transgenetic64bit/Testes/5_OBJETIVOS/$i/Hurwicz/correlated/$i.corr2/$i.corr2_saTrans.log
		./getInfo <  transgenetic64bit/Testes/5_OBJETIVOS/$i/Hurwicz/correlated/$i.corr3/$i.corr3_"$c".out  >> transgenetic64bit/Testes/5_OBJETIVOS/$i/Hurwicz/correlated/$i.corr3/$i.corr3_saTrans.log
		
		./getInfo <  transgenetic64bit/Testes/5_OBJETIVOS/$i/Hurwicz/anticorrelated/$i.anticorr1/$i.anticorr1_"$c".out  >> transgenetic64bit/Testes/5_OBJETIVOS/$i/Hurwicz/anticorrelated/$i.anticorr1/$i.anticorr1_saTrans.log
		./getInfo <  transgenetic64bit/Testes/5_OBJETIVOS/$i/Hurwicz/anticorrelated/$i.anticorr2/$i.anticorr2_"$c".out  >> transgenetic64bit/Testes/5_OBJETIVOS/$i/Hurwicz/anticorrelated/$i.anticorr2/$i.anticorr2_saTrans.log
		./getInfo <  transgenetic64bit/Testes/5_OBJETIVOS/$i/Hurwicz/anticorrelated/$i.anticorr3/$i.anticorr3_"$c".out  >> transgenetic64bit/Testes/5_OBJETIVOS/$i/Hurwicz/anticorrelated/$i.anticorr3/$i.anticorr3_saTrans.log
		




		./getInfo <  transgenetic64bit/Testes/8_OBJETIVOS/$i/k_trimmed/correlated/$i.corr1/$i.corr1_"$c".out  >> transgenetic64bit/Testes/8_OBJETIVOS/$i/k_trimmed/correlated/$i.corr1/$i.corr1_saTrans.log
		./getInfo <  transgenetic64bit/Testes/8_OBJETIVOS/$i/k_trimmed/correlated/$i.corr2/$i.corr2_"$c".out  >> transgenetic64bit/Testes/8_OBJETIVOS/$i/k_trimmed/correlated/$i.corr2/$i.corr2_saTrans.log
		./getInfo <  transgenetic64bit/Testes/8_OBJETIVOS/$i/k_trimmed/correlated/$i.corr3/$i.corr3_"$c".out  >> transgenetic64bit/Testes/8_OBJETIVOS/$i/k_trimmed/correlated/$i.corr3/$i.corr3_saTrans.log
		
		./getInfo <  transgenetic64bit/Testes/8_OBJETIVOS/$i/k_trimmed/anticorrelated/$i.anticorr1/$i.anticorr1_"$c".out  >> transgenetic64bit/Testes/8_OBJETIVOS/$i/k_trimmed/anticorrelated/$i.anticorr1/$i.anticorr1_saTrans.log
		./getInfo <  transgenetic64bit/Testes/8_OBJETIVOS/$i/k_trimmed/anticorrelated/$i.anticorr2/$i.anticorr2_"$c".out  >> transgenetic64bit/Testes/8_OBJETIVOS/$i/k_trimmed/anticorrelated/$i.anticorr2/$i.anticorr2_saTrans.log
		./getInfo <  transgenetic64bit/Testes/8_OBJETIVOS/$i/k_trimmed/anticorrelated/$i.anticorr3/$i.anticorr3_"$c".out  >> transgenetic64bit/Testes/8_OBJETIVOS/$i/k_trimmed/anticorrelated/$i.anticorr3/$i.anticorr3_saTrans.log
		

		./getInfo <  transgenetic64bit/Testes/8_OBJETIVOS/$i/k_centrum/correlated/$i.corr1/$i.corr1_"$c".out  >> transgenetic64bit/Testes/8_OBJETIVOS/$i/k_centrum/correlated/$i.corr1/$i.corr1_saTrans.log
		./getInfo <  transgenetic64bit/Testes/8_OBJETIVOS/$i/k_centrum/correlated/$i.corr2/$i.corr2_"$c".out  >> transgenetic64bit/Testes/8_OBJETIVOS/$i/k_centrum/correlated/$i.corr2/$i.corr2_saTrans.log
		./getInfo <  transgenetic64bit/Testes/8_OBJETIVOS/$i/k_centrum/correlated/$i.corr3/$i.corr3_"$c".out  >> transgenetic64bit/Testes/8_OBJETIVOS/$i/k_centrum/correlated/$i.corr3/$i.corr3_saTrans.log
		
		./getInfo <  transgenetic64bit/Testes/8_OBJETIVOS/$i/k_centrum/anticorrelated/$i.anticorr1/$i.anticorr1_"$c".out  >> transgenetic64bit/Testes/8_OBJETIVOS/$i/k_centrum/anticorrelated/$i.anticorr1/$i.anticorr1_saTrans.log
		./getInfo <  transgenetic64bit/Testes/8_OBJETIVOS/$i/k_centrum/anticorrelated/$i.anticorr2/$i.anticorr2_"$c".out  >> transgenetic64bit/Testes/8_OBJETIVOS/$i/k_centrum/anticorrelated/$i.anticorr2/$i.anticorr2_saTrans.log
		./getInfo <  transgenetic64bit/Testes/8_OBJETIVOS/$i/k_centrum/anticorrelated/$i.anticorr3/$i.anticorr3_"$c".out  >> transgenetic64bit/Testes/8_OBJETIVOS/$i/k_centrum/anticorrelated/$i.anticorr3/$i.anticorr3_saTrans.log
		

		./getInfo <  transgenetic64bit/Testes/8_OBJETIVOS/$i/Hurwicz/correlated/$i.corr1/$i.corr1_"$c".out  >> transgenetic64bit/Testes/8_OBJETIVOS/$i/Hurwicz/correlated/$i.corr1/$i.corr1_saTrans.log
		./getInfo <  transgenetic64bit/Testes/8_OBJETIVOS/$i/Hurwicz/correlated/$i.corr2/$i.corr2_"$c".out  >> transgenetic64bit/Testes/8_OBJETIVOS/$i/Hurwicz/correlated/$i.corr2/$i.corr2_saTrans.log
		./getInfo <  transgenetic64bit/Testes/8_OBJETIVOS/$i/Hurwicz/correlated/$i.corr3/$i.corr3_"$c".out  >> transgenetic64bit/Testes/8_OBJETIVOS/$i/Hurwicz/correlated/$i.corr3/$i.corr3_saTrans.log
		
		./getInfo <  transgenetic64bit/Testes/8_OBJETIVOS/$i/Hurwicz/anticorrelated/$i.anticorr1/$i.anticorr1_"$c".out  >> transgenetic64bit/Testes/8_OBJETIVOS/$i/Hurwicz/anticorrelated/$i.anticorr1/$i.anticorr1_saTrans.log
		./getInfo <  transgenetic64bit/Testes/8_OBJETIVOS/$i/Hurwicz/anticorrelated/$i.anticorr2/$i.anticorr2_"$c".out  >> transgenetic64bit/Testes/8_OBJETIVOS/$i/Hurwicz/anticorrelated/$i.anticorr2/$i.anticorr2_saTrans.log
		./getInfo <  transgenetic64bit/Testes/8_OBJETIVOS/$i/Hurwicz/anticorrelated/$i.anticorr3/$i.anticorr3_"$c".out  >> transgenetic64bit/Testes/8_OBJETIVOS/$i/Hurwicz/anticorrelated/$i.anticorr3/$i.anticorr3_saTrans.log
		





		./getInfo <  transgenetic64bit/Testes/10_OBJETIVOS/$i/k_trimmed/correlated/$i.corr1/$i.corr1_"$c".out  >> transgenetic64bit/Testes/10_OBJETIVOS/$i/k_trimmed/correlated/$i.corr1/$i.corr1_saTrans.log
		./getInfo <  transgenetic64bit/Testes/10_OBJETIVOS/$i/k_trimmed/correlated/$i.corr2/$i.corr2_"$c".out  >> transgenetic64bit/Testes/10_OBJETIVOS/$i/k_trimmed/correlated/$i.corr2/$i.corr2_saTrans.log
		./getInfo <  transgenetic64bit/Testes/10_OBJETIVOS/$i/k_trimmed/correlated/$i.corr3/$i.corr3_"$c".out  >> transgenetic64bit/Testes/10_OBJETIVOS/$i/k_trimmed/correlated/$i.corr3/$i.corr3_saTrans.log
		
		./getInfo <  transgenetic64bit/Testes/10_OBJETIVOS/$i/k_trimmed/anticorrelated/$i.anticorr1/$i.anticorr1_"$c".out  >> transgenetic64bit/Testes/10_OBJETIVOS/$i/k_trimmed/anticorrelated/$i.anticorr1/$i.anticorr1_saTrans.log
		./getInfo <  transgenetic64bit/Testes/10_OBJETIVOS/$i/k_trimmed/anticorrelated/$i.anticorr2/$i.anticorr2_"$c".out  >> transgenetic64bit/Testes/10_OBJETIVOS/$i/k_trimmed/anticorrelated/$i.anticorr2/$i.anticorr2_saTrans.log
		./getInfo <  transgenetic64bit/Testes/10_OBJETIVOS/$i/k_trimmed/anticorrelated/$i.anticorr3/$i.anticorr3_"$c".out  >> transgenetic64bit/Testes/10_OBJETIVOS/$i/k_trimmed/anticorrelated/$i.anticorr3/$i.anticorr3_saTrans.log
		

		./getInfo <  transgenetic64bit/Testes/10_OBJETIVOS/$i/k_centrum/correlated/$i.corr1/$i.corr1_"$c".out  >> transgenetic64bit/Testes/10_OBJETIVOS/$i/k_centrum/correlated/$i.corr1/$i.corr1_saTrans.log
		./getInfo <  transgenetic64bit/Testes/10_OBJETIVOS/$i/k_centrum/correlated/$i.corr2/$i.corr2_"$c".out  >> transgenetic64bit/Testes/10_OBJETIVOS/$i/k_centrum/correlated/$i.corr2/$i.corr2_saTrans.log
		./getInfo <  transgenetic64bit/Testes/10_OBJETIVOS/$i/k_centrum/correlated/$i.corr3/$i.corr3_"$c".out  >> transgenetic64bit/Testes/10_OBJETIVOS/$i/k_centrum/correlated/$i.corr3/$i.corr3_saTrans.log
		
		./getInfo <  transgenetic64bit/Testes/10_OBJETIVOS/$i/k_centrum/anticorrelated/$i.anticorr1/$i.anticorr1_"$c".out  >> transgenetic64bit/Testes/10_OBJETIVOS/$i/k_centrum/anticorrelated/$i.anticorr1/$i.anticorr1_saTrans.log
		./getInfo <  transgenetic64bit/Testes/10_OBJETIVOS/$i/k_centrum/anticorrelated/$i.anticorr2/$i.anticorr2_"$c".out  >> transgenetic64bit/Testes/10_OBJETIVOS/$i/k_centrum/anticorrelated/$i.anticorr2/$i.anticorr2_saTrans.log
		./getInfo <  transgenetic64bit/Testes/10_OBJETIVOS/$i/k_centrum/anticorrelated/$i.anticorr3/$i.anticorr3_"$c".out  >> transgenetic64bit/Testes/10_OBJETIVOS/$i/k_centrum/anticorrelated/$i.anticorr3/$i.anticorr3_saTrans.log
		


		c=$((c+1))
    done
done 
