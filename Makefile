all: automaton.out

automaton: mrproper main.o TileMap.o cli.o
	g++ -g main.o TileMap.o cli.o -o automaton -lsfml-graphics -lsfml-window -lsfml-system 
	make clean

main.o:
	g++ -c src/main.cpp -g 

TileMap.o:
	g++ -c src/TileMap.cpp -g 

cli.o:
	g++ -c src/cli.cpp -g 

clean:
	rm -rf *.o

mrproper: clean
	rm -rf automaton