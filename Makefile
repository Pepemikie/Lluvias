all: athmosphere

athmosphere: main.o moon.o shower.o state.o time.o arduino.o
	gcc main.o moon.o shower.o state.o time.o arduino.o -o athmosphere

main.o: main.c
	gcc -Wall main.o -c main.c

moon.o: moon.c
	gcc -Wall moon.o -c moon.c

shower.o: shower.c
	gcc -Wall shower.o -c shower.c

state.o: state.c
	gcc -Wall state.o -c state.c

time.o: time.c
	gcc -Wall time.o -c time.c

arduino.o: arduino.c
	gcc -Wall arduino.o -c arduino.c

clean:
	-rm -rf *.o athmosphere