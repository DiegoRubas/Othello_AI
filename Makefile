all: main clean


main: player.o  board.o game.o main.o gameMove.o humanPlayer.o playerFactory.o filePlayer.o  artificialIntelligence.o 
	g++  -Wall -o projet $^


main.o: main.cpp
	g++ -c -Wall  -o $@ main.cpp

board.o: board.cpp
	g++ -c  -Wall  -o $@ board.cpp


player.o: player.cpp
	g++ -c -Wall  -o $@ player.cpp


filePlayer.o: filePlayer.cpp
	g++ -c -Wall  -o $@ filePlayer.cpp

artificialIntelligence.o: artificialIntelligence.cpp
	g++ -c -Wall  -o $@ artificialIntelligence.cpp
humanPlayer.o: humanPlayer.cpp
	g++ -c  -Wall -o $@ humanPlayer.cpp

playerFactory.o: playerFactory.cpp
	g++ -c -Wall  -o $@ playerFactory.cpp

game.o: game.cpp
	g++ -c -Wall -o $@ game.cpp

gameMove.o: gameMove.cpp
	g++ -c -Wall  -o $@ gameMove.cpp

clean:
	rm *.o

