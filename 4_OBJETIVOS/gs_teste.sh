#!/bin/bash

for i in 5 #7 10 12 15 17 20 22 25 27 30 33 35 38 40 42 45 48 50
do
	.././gs < correlated/$i.corr1.in > TESTE/gs/correlated/$i.corr1.out
	.././gs < correlated/$i.corr2.in > TESTE/gs/correlated/$i.corr2.out
	.././gs < correlated/$i.corr3.in > TESTE/gs/correlated/$i.corr3.out
	
	.././gs < anticorrelated/$i.anticorr1.in > TESTE/gs/anticorrelated/$i.anticorr1.out
	.././gs < anticorrelated/$i.anticorr2.in > TESTE/gs/anticorrelated/$i.anticorr2.out
	.././gs < anticorrelated/$i.anticorr3.in > TESTE/gs/anticorrelated/$i.anticorr3.out
	
done