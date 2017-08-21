
all: lokmanKoksalan.o  gs.o algoritm1 gs

	
lokmanKoksalan.o : lokmanKoksalan.cpp
	g++ -lpthread -g -c  lokmanKoksalan.cpp

gs.o : gs.cpp
	g++ -lpthread -g -c  gs.cpp

		
algoritm1 : lokmanKoksalan.o  
	g++ -lpthread -m64 -g  -lm -o algoritm1 lokmanKoksalan.o -Llib/ -lgurobi_c++ -lgurobi65 -lm

gs : gs.o  
	g++ -lpthread -m64 -g  -lm -o gs gs.o -Llib/ -lgurobi_c++ -lgurobi65 -lm

