main: main.o Playground.o Map.o Settings.o Player.o Enemy.o Game.o
	g++ -g -o C-urassic Game.o main.o Playground.o Map.o Player.o Enemy.o -lm

main.o: Game.o Settings.o 
	g++ -g -c Control/main.cpp

Game.o: Control/Game.cpp Control/Game.cpp Settings.o Player.o Enemy.o Playground.o
	g++ -g -c Control/Game.cpp

Settings.o: Control/Settings.hpp
	g++ -g -c Control/Settings.hpp

Map.o: Model/Map.cpp Model/Map.hpp Model/Directions.hpp Model/ItemTypes.hpp Settings.o Enemy.o
	g++ -g -c Model/Map.cpp 

Playground.o: View/Playground.cpp View/Playground.hpp Settings.o Map.o
	g++ -g -c View/Playground.cpp

Player.o: Model/Player.cpp Model/Player.hpp Settings.o Map.o
	g++ -g -c Model/Player.cpp

Enemy.o: Model/Enemy.cpp Model/Enemy.hpp Settings.o 
	g++ -g -c Model/Enemy.cpp

clean:
	rm *.o C-urassic