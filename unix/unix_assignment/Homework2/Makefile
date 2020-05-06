CC = gcc
CFLAGS = -g -Wall
TARGET = messenger
OBJECTS = chat.o printchat.o

all : $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm *.o messenger
	./shmremove

