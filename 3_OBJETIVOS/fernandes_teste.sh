#!/bin/bash

for i in 5 7 10 12 15 17 20 22 25 27 30 33 35 38 40 42 45 48 50
do
	.././fernandes < correlated/$i.corr1.in > TESTE/fernandes/correlated/$i.corr1.out
	.././fernandes < correlated/$i.corr2.in > TESTE/fernandes/correlated/$i.corr2.out
	.././fernandes < correlated/$i.corr3.in > TESTE/fernandes/correlated/$i.corr3.out
	
	.././fernandes < anticorrelated/$i.anticorr1.in > TESTE/fernandes/anticorrelated/$i.anticorr1.out
	.././fernandes < anticorrelated/$i.anticorr2.in > TESTE/fernandes/anticorrelated/$i.anticorr2.out
	.././fernandes < anticorrelated/$i.anticorr3.in > TESTE/fernandes/anticorrelated/$i.anticorr3.out
	
done