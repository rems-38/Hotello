CC = gcc
FLAGS = -Wall -g
OBJDIR = obj

game.out : main.o utils.o legal_moves.o make_move.o network.o artificial_intelligence.o
	$(CC) $(FLAGS) -o $@ $^

main.o : src/main.c src/utils/utils.h src/legal_moves/legal_moves.h
	$(CC) $(FLAGS) -c $< 

legal_moves.o : src/legal_moves/legal_moves.c src/legal_moves/legal_moves.h src/utils/utils.h
	$(CC) $(FLAGS) -c $< 

make_move.o : src/make_move/make_move.c src/make_move/make_move.h src/utils/utils.h
	$(CC) $(FLAGS) -c $< 

utils.o : src/utils/utils.c src/utils/utils.h src/legal_moves/legal_moves.c src/legal_moves/legal_moves.h src/make_move/make_move.c src/make_move/make_move.h
	$(CC) $(FLAGS) -c $< 

network.o : src/network/network.c src/network/network.h
	$(CC) $(FLAGS) -c $< 

artificial_intelligence.o : src/artificial_intelligence/artificial_intelligence.c src/artificial_intelligence/artificial_intelligence.h src/utils/utils.h src/legal_moves/legal_moves.h src/make_move/make_move.h
	$(CC) $(FLAGS) -c $< 

clean :
	rm *.o game.out