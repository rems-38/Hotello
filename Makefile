main : main.o functions.o
	gcc -o $@ $^

main.o : main.c core_game/functions/functions.h
	gcc -c $<

functions.o : core_game/functions/functions.c core_game/functions/functions.h
	gcc -c $<

clean: 
	rm main
	rm -rf *.o