#!/bin/bash

for i in 5 7 10 12 15 17 20 22 25 27 30 33 35 38 40 42 45 48 50 100 200 300 400 500 600 700 800 900 1000
do
	./converte < ../../../../../1\ Reta\ Final\ da\ Graduação\ /Monografia/Implementações/AGMO_exactAlgoritms/AllInstâncias/10_OBJETIVOS/correlate/$i.corr1.in > correlated/$i.corr1.in
	sleep 1 
	./converte < ../../../../../1\ Reta\ Final\ da\ Graduação\ /Monografia/Implementações/AGMO_exactAlgoritms/AllInstâncias/10_OBJETIVOS/correlate/$i.corr2.in > correlated/$i.corr2.in
	sleep 1 
	./converte < ../../../../../1\ Reta\ Final\ da\ Graduação\ /Monografia/Implementações/AGMO_exactAlgoritms/AllInstâncias/10_OBJETIVOS/correlate/$i.corr3.in > correlated/$i.corr3.in
	sleep 1 
	./converte < ../../../../../1\ Reta\ Final\ da\ Graduação\ /Monografia/Implementações/AGMO_exactAlgoritms/AllInstâncias/10_OBJETIVOS/anticorrelate/$i.anticorr1.in > anticorrelated/$i.anticorr1.in
	sleep 1 
	./converte < ../../../../../1\ Reta\ Final\ da\ Graduação\ /Monografia/Implementações/AGMO_exactAlgoritms/AllInstâncias/10_OBJETIVOS/anticorrelate/$i.anticorr2.in > anticorrelated/$i.anticorr2.in
	sleep 1 
	./converte < ../../../../../1\ Reta\ Final\ da\ Graduação\ /Monografia/Implementações/AGMO_exactAlgoritms/AllInstâncias/10_OBJETIVOS/anticorrelate/$i.anticorr3.in > anticorrelated/$i.anticorr3.in
	sleep 1 
	
done