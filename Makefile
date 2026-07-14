all: athmosphere

athmosphere: main.o shower.o moon.o clock.o #arduino.o
	gcc main.o shower.o moon.o clock.o -o athmosphere -lm
# arduino.o
main.o: main.c
	gcc -Wall -c main.c -o main.o

moon.o: moon.c
	gcc -Wall -c moon.c -o moon.o

shower.o: shower.c
	gcc -Wall -c shower.c -o shower.o

clock.o: clock.c
	gcc -Wall -c clock.c -o clock.o

#arduino.o: arduino.c
#	gcc -Wall arduino.o -c arduino.c

run:
	./athmosphere 

clean:
	-rm -rf *.o athmosphere