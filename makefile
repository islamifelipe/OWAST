
all: fernandes.o fernandes2.o gs.o fernandes fernandes2 gs

	
fernandes.o : fernandes.cpp
	g++ -lpthread -g -c  fernandes.cpp


	
fernandes2.o : fernandes2.cpp
	g++ -lpthread -g -c  fernandes2.cpp


gs.o : gs.cpp
	g++ -lpthread -g -c  gs.cpp

		
fernandes : fernandes.o  
	g++ -lpthread -m64 -g  -lm -o fernandes fernandes.o -Llib/ -lgurobi_c++ -lgurobi65 -lm

fernandes2 : fernandes2.o  
	g++ -lpthread -m64 -g  -lm -o fernandes2 fernandes2.o -Llib/ -lgurobi_c++ -lgurobi65 -lm


gs : gs.o  
	g++ -lpthread -m64 -g  -lm -o gs gs.o -Llib/ -lgurobi_c++ -lgurobi65 -lm

