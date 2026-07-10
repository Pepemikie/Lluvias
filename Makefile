all: athmosphere

athmosphere: main.o shower.o #moon.o state.o clock.o arduino.o
	gcc main.o shower.o -o athmosphere
#moon.o state.o clock.o arduino.o
main.o: main.c
	gcc -Wall -c main.c -o main.o

#moon.o: moon.c
#	gcc -Wall moon.o -c moon.c

shower.o: shower.c
	gcc -Wall -c shower.c -o shower.o

#state.o: state.c
#	gcc -Wall state.o -c state.c

#clock.o: clock.c
#	gcc -Wall clock.o -c clock.c

#arduino.o: arduino.c
#	gcc -Wall arduino.o -c arduino.c

run:
	./athmosphere 

clean:
	-rm -rf *.o athmosphere