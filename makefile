#configure variables
CC = gcc
CFLAGS = -Wall
OBJFILES = asg1.o area.o perimeter.o
TARGET = asg1

# target for compiling
all: $(TARGET)

#run program with c-l arguments
run: all
	./asg1 10 5 "hi"

#compile using gcc and variables specified
$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

#clean file directory of object files
clean:
	rm -f makefile~ $(OBJFILES) $(TARGET)
