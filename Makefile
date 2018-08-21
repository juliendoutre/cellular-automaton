all: automaton

automaton: mrproper main.o TileMap.o cli.o
	g++ -g main.o TileMap.o cli.o -o automaton -lsfml-graphics -lsfml-window -lsfml-system -std=c++11
	make clean

main.o:
	g++ -c src/main.cpp -g -std=c++11

TileMap.o:
	g++ -c src/TileMap.cpp -g -std=c++11

cli.o:
	g++ -c src/cli.cpp -g -std=c++11

clean:
	rm -rf *.o

mrproper: clean
	rm -rf automaton