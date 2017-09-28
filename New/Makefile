main: main.o Playground.o Map.o Playground.o MapObject.o Wall.o Player.o
	g++ -g -o C-urassic main.o Playground.o Map.o MapObject.o Wall.o Player.o -lm

main.o: Playground.o Map.o
	g++ -g -c Control/main.cpp

Map.o: Model/Map.cpp Model/Map.hpp Model/Wall.hpp Model/Player.hpp
	g++ -g -c Model/Map.cpp 

Playground.o: View/Playground.cpp View/Playground.hpp
	g++ -g -c View/Playground.cpp

MapObject.o: Model/MapObject.cpp Model/MapObject.hpp
	g++ -g -c Model/MapObject.cpp

Wall.o: Model/Wall.cpp Model/Wall.hpp
	g++ -g -c Model/Wall.cpp

Settings.o: Control/Settings.hpp
	g++ -g -c Control/Settings.hpp

Player.o: Model/Player.cpp Model/Player.hpp
	g++ -g -c Model/Player.cpp
	
clean:
	rm *.o C-urassic