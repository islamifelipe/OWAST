
all: fernandes.o  gs.o fernandes gs

	
fernandes.o : fernandes.cpp
	g++ -lpthread -g -c  fernandes.cpp

gs.o : gs.cpp
	g++ -lpthread -g -c  gs.cpp

		
fernandes : fernandes.o  
	g++ -lpthread -m64 -g  -lm -o fernandes fernandes.o -Llib/ -lgurobi_c++ -lgurobi65 -lm

gs : gs.o  
	g++ -lpthread -m64 -g  -lm -o gs gs.o -Llib/ -lgurobi_c++ -lgurobi65 -lm

