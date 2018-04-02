
BASE=clang++ -std=c++14
OBJ=./obj/
INCS=-I./ -I../boost_1_66_0/
LIBS=-L../boost_1_66_0/stage/lib/ -lboost_system -lpthread -static

main: $(OBJ)main.o $(OBJ)net_client_manager.o $(OBJ)net_client.o
	$(BASE) $(OBJ)main.o $(OBJ)net_client_manager.o $(OBJ)net_client.o $(INCS) $(LIBS) -o main.out


$(OBJ)main.o: main.cpp
	$(BASE) -c main.cpp $(INCS) -o $(OBJ)main.o

$(OBJ)net_client_manager.o: ./networking/net_client_manager.cpp
	$(BASE) -c ./networking/net_client_manager.cpp $(INCS) -o $(OBJ)net_client_manager.o

$(OBJ)net_client.o: ./networking/net_client.cpp
	$(BASE) -c ./networking/net_client.cpp $(INCS) -o $(OBJ)net_client.o


