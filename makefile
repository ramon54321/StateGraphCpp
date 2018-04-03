
BASE=clang++ -std=c++14
OBJ=./obj/
INCS=-I./ -I../boost_1_66_0/
LIBS=-L../boost_1_66_0/stage/lib/ -lboost_system -lpthread -static

main: $(OBJ)main.o \
		$(OBJ)net_client_manager.o \
		$(OBJ)net_client.o \
		$(OBJ)logic_core.o \
		$(OBJ)event_manager.o
	$(BASE) $(OBJ)main.o \
		$(OBJ)net_client_manager.o \
		$(OBJ)net_client.o \
		$(OBJ)logic_core.o \
		$(OBJ)event_manager.o \
		$(INCS) $(LIBS) -o main.out


$(OBJ)main.o: main.cpp
	$(BASE) -c main.cpp \
		$(INCS) -o $(OBJ)main.o

$(OBJ)net_client_manager.o: ./networking/net_client_manager.cpp \
		./networking/net_client_manager.hpp
	$(BASE) -c ./networking/net_client_manager.cpp \
		$(INCS) -o $(OBJ)net_client_manager.o

$(OBJ)net_client.o: ./networking/net_client.cpp \
		./networking/net_client.hpp
	$(BASE) -c ./networking/net_client.cpp \
		$(INCS) -o $(OBJ)net_client.o

$(OBJ)logic_core.o: ./game_logic/logic_core.cpp \
		./game_logic/logic_core.hpp \
		./game_logic/constants.hpp \
		./game_logic/entity.hpp \
		./game_logic/event_manager.hpp
	$(BASE) -c ./game_logic/logic_core.cpp \
		$(INCS) -o $(OBJ)logic_core.o

$(OBJ)event_manager.o: ./game_logic/event_manager.cpp \
		./game_logic/event_manager.hpp
	$(BASE) -c ./game_logic/event_manager.cpp \
		$(INCS) -o $(OBJ)event_manager.o


