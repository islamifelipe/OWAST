#!/bin/bash
for p in 30 35 40 45 50 100 200 300 400 500 600 700 800 900 1000
do
	for i in 1 2 3
	do
		./lerPvalores k_trimmed/correlated/mann_whit_"$p".corr"$i".out teste.log
	done

done