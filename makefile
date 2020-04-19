Fish:go_fish.o player.o deck.o card.o
	g++ -o fish go_fish.o player.o deck.o card.o

go_fish.o:go_fish.cpp
	g++ -c -g go_fish.cpp -std=c++11
	
player.o:player.cpp
	g++ -c -g player.cpp -std=c++11

deck.o: deck.cpp
	g++ -c -g deck.cpp -std=c++11

card.o: card.cpp
	g++ -c -g card.cpp -std=c++11