



cd Testes/10_OBJETIVOS
for k in 30 35 40 45 50 100 200 300 400 500 600 700 800 900 1000 
do
	mkdir $k
	cd $k
	mkdir k_trimmed
	cd k_trimmed
	mkdir correlated
	cd correlated
	mkdir $k.corr1
	mkdir $k.corr2
	mkdir $k.corr3
	echo "" > $k.corr1/$k.corr1_sampleFile.log
	echo "" > $k.corr2/$k.corr2_sampleFile.log
	echo "" > $k.corr3/$k.corr3_sampleFile.log

	echo "" > $k.corr1/$k.corr1_timeFile.log
	echo "" > $k.corr2/$k.corr2_timeFile.log
	echo "" > $k.corr3/$k.corr3_timeFile.log
	cd ..
	mkdir anticorrelated
	cd anticorrelated
	mkdir $k.anticorr1
	mkdir $k.anticorr2
	mkdir $k.anticorr3
	echo "" > $k.anticorr1/$k.anticorr1_sampleFile.log
	echo "" > $k.anticorr2/$k.anticorr2_sampleFile.log
	echo "" > $k.anticorr3/$k.anticorr3_sampleFile.log

	echo "" > $k.anticorr1/$k.anticorr1_timeFile.log
	echo "" > $k.anticorr2/$k.anticorr2_timeFile.log
	echo "" > $k.anticorr3/$k.anticorr3_timeFile.log
	cd ..
	cd .. #dentro k



	mkdir k_centrum
	cd k_centrum
	mkdir correlated
	cd correlated
	mkdir $k.corr1
	mkdir $k.corr2
	mkdir $k.corr3
	echo "" > $k.corr1/$k.corr1_sampleFile.log
	echo "" > $k.corr2/$k.corr2_sampleFile.log
	echo "" > $k.corr3/$k.corr3_sampleFile.log

	echo "" > $k.corr1/$k.corr1_timeFile.log
	echo "" > $k.corr2/$k.corr2_timeFile.log
	echo "" > $k.corr3/$k.corr3_timeFile.log
	cd ..
	mkdir anticorrelated
	cd anticorrelated
	mkdir $k.anticorr1
	mkdir $k.anticorr2
	mkdir $k.anticorr3
	echo "" > $k.anticorr1/$k.anticorr1_sampleFile.log
	echo "" > $k.anticorr2/$k.anticorr2_sampleFile.log
	echo "" > $k.anticorr3/$k.anticorr3_sampleFile.log

	echo "" > $k.anticorr1/$k.anticorr1_timeFile.log
	echo "" > $k.anticorr2/$k.anticorr2_timeFile.log
	echo "" > $k.anticorr3/$k.anticorr3_timeFile.log
	cd ..
	cd .. #dentro k

	mkdir Hurwicz
	cd Hurwicz
	mkdir correlated
	cd correlated
	mkdir $k.corr1
	mkdir $k.corr2
	mkdir $k.corr3
	echo "" > $k.corr1/$k.corr1_sampleFile.log
	echo "" > $k.corr2/$k.corr2_sampleFile.log
	echo "" > $k.corr3/$k.corr3_sampleFile.log

	echo "" > $k.corr1/$k.corr1_timeFile.log
	echo "" > $k.corr2/$k.corr2_timeFile.log
	echo "" > $k.corr3/$k.corr3_timeFile.log
	cd ..
	mkdir anticorrelated
	cd anticorrelated
	mkdir $k.anticorr1
	mkdir $k.anticorr2
	mkdir $k.anticorr3
	echo "" > $k.anticorr1/$k.anticorr1_sampleFile.log
	echo "" > $k.anticorr2/$k.anticorr2_sampleFile.log
	echo "" > $k.anticorr3/$k.anticorr3_sampleFile.log

	echo "" > $k.anticorr1/$k.anticorr1_timeFile.log
	echo "" > $k.anticorr2/$k.anticorr2_timeFile.log
	echo "" > $k.anticorr3/$k.anticorr3_timeFile.log
	cd ..
	cd .. #dentro k

	cd .. #10_OBJETIVOS
	echo "#define NUMEROVERTICES $k" >> ../../param.h
	
	 g++ ../../transgenetic.cpp ../../rand/mersenne.o -Wall -O3 -o trans10Obj$k #$15
	

done



#for k in 50 100 200 300 400 500 600 700 800 900 1000
#do
	#mkdir instancias/executaveis/$k
#	echo "#define NUMEROVERTICES $k" >> param.h
	
	#g++ transgenetic.cpp rand/mersenne.o -Wall -O3 -o trans5_15 #$15
	#mkdir instancias/executaveis/$k/correlated
	#mkdir instancias/executaveis/$k/anticorrelated
	#mkdir instancias/executaveis/$k/concave

#	for i in 1 2 3 4 5
#	do
#		mkdir instancias/executaveis/$k/correlated/$k.corr$i
#		echo '' > instancias/executaveis/$k/correlated/$k.corr$i/$k.corr$i.timee.log
#		echo '' > instancias/executaveis/$k/correlated/$k.corr$i/$k.corr$i.PF.log
#		echo '' > instancias/executaveis/$k/correlated/$k.corr$i/$k.corr$i.lixo.log
#		mkdir instancias/executaveis/$k/anticorrelated/$k.anticorr$i
#		echo '' > instancias/executaveis/$k/anticorrelated/$k.anticorr$i/$k.anticorr$i.timee.log
#		echo '' > instancias/executaveis/$k/anticorrelated/$k.anticorr$i/$k.anticorr$i.PF.log
#		echo '' > instancias/executaveis/$k/anticorrelated/$k.anticorr$i/$k.anticorr$i.lixo.log
#		mkdir instancias/executaveis/$k/concave/$k.conc$i
#		echo '' > instancias/executaveis/$k/concave/$k.conc$i/$k.conc$i.timee.log
#		echo '' > instancias/executaveis/$k/concave/$k.conc$i/$k.conc$i.PF.log
#		echo '' > instancias/executaveis/$k/concave/$k.conc$i/$k.conc$i.lixo.log
		
#	done
#done
