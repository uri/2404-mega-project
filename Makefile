bsg: main.o Menu.o NetworkUtility.o Observer.o Server.o Client.o  GameSuper.o GameHost.o GameClient.o GamePvC.o GameCvC.o GameObserver.o  Board.o mtrand.o Position.o Random.o Renderer.o Ship.o ShipList.o ShipTypes.o Player.o PositionList.o Statistics.o
	g++ -o bsg main.o Menu.o NetworkUtility.o Observer.o  Server.o Client.o  GameSuper.o GameHost.o GameClient.o GamePvC.o GameCvC.o GameObserver.o  Board.o mtrand.o Position.o Random.o Renderer.o Ship.o ShipList.o ShipTypes.o Player.o PositionList.o Statistics.o

Board.o: Board.cpp Board.h
	g++ -c Board.cpp

NetworkUtility.o: NetworkUtility.cpp NetworkUtility.h
	g++ -c NetworkUtility.cpp

Server.o: Server.cpp Server.h
	g++ -c Server.cpp

Client.o: Client.cpp Client.h
	g++ -c Client.cpp

Observer.o: Observer.cpp Observer.h
	g++ -c Observer.cpp

Menu.o: Menu.cpp Menu.h
	g++ -c Menu.cpp

GameSuper.o: GameSuper.cpp GameSuper.h
	g++ -c GameSuper.cpp

GameHost.o: GameHost.cpp GameHost.h
	g++ -c GameHost.cpp

GameClient.o: GameClient.cpp GameClient.h
	g++ -c GameClient.cpp

GameObserver.o: GameObserver.cpp GameObserver.h
	g++ -c GameObserver.cpp

GamePvC.o: GamePvC.cpp GamePvC.h
	g++ -c GamePvC.cpp

GameCvC.o: GameCvC.cpp GameCvC.h
	g++ -c GameCvC.cpp

main.o: main.cpp
	g++ -c main.cpp

mtrand.o: mtrand.cpp mtrand.h
	g++ -c mtrand.cpp

Position.o: Position.cpp Position.h
	g++ -c Position.cpp

Random.o: Random.cpp Random.h
	g++ -c Random.cpp

Renderer.o: Renderer.cpp Renderer.h
	g++ -c Renderer.cpp

Ship.o: Ship.cpp Ship.h
	g++ -c Ship.cpp

ShipList.o: ShipList.cpp ShipList.h
	g++ -c ShipList.cpp

ShipTypes.o: ShipTypes.cpp ShipTypes.h
	g++ -c ShipTypes.cpp

Statistics.o: Statistics.cpp Statistics.h
	g++ -c Statistics.cpp

PositionList.o: PositionList.cpp PositionList.h
	g++ -c PositionList.cpp

Player.o: Player.cpp Player.h
	g++ -c Player.cpp
clean:
	rm -f *.o bsg
