CC = gcc
FLAGS = -Wall -Wextra
OBJDIR = obj

game.out : main.o utils.o legal_moves.o make_moves.o
	$(CC) $(FLAGS) -o $@ $^

main.o : src/main.c src/utils/utils.h src/legal_moves/legal_moves.h
	$(CC) $(FLAGS) -c $< 

legal_moves.o : src/legal_moves/legal_moves.c src/legal_moves/legal_moves.h src/utils/utils.h
	$(CC) $(FLAGS) -c $< 

make_moves.o : src/make_moves/make_moves.c src/make_moves/make_moves.h src/utils/utils.h
	$(CC) $(FLAGS) -c $< 

utils.o : src/utils/utils.c src/utils/utils.h
	$(CC) $(FLAGS) -c $< 

clean :
	rm *.o game.out