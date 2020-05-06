CC = gcc
TARGET = digitalclock
OBJECTS = main.o localdate.o localtime.o elapsedtime.o

all : $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ -lncurses -lpthread

clean :
	rm *.o digitalclock
