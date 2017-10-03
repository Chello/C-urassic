main: main.o Playground.o Map.o Playground.o Settings.o Player.o
	g++ -g -o C-urassic main.o Playground.o Map.o Player.o -lm

main.o: Playground.o Map.o
	g++ -g -c Control/main.cpp

Settings.o: Control/Settings.hpp
	g++ -g -c Control/Settings.hpp

MapCharacter.o: Control/MapCharacter.hpp
	g++ -g -c Control/MapCharacter.hpp

Map.o: Model/Map.cpp Model/Map.hpp  Model/Directions.hpp Model/ItemTypes.hpp Settings.o Player.o Item.o 
	g++ -g -c Model/Map.cpp 

Playground.o: View/Playground.cpp View/Playground.hpp Settings.o
	g++ -g -c View/Playground.cpp

Player.o: Model/Player.cpp Model/Player.hpp Settings.o
	g++ -g -c Model/Player.cpp

Item.o: Model/Item.cpp Model/Item.hpp Settings.o Model/Directions.hpp Model/ItemTypes.hpp
	g++ -g -c Model/Item.cpp

clean:
	rm *.o C-urassic