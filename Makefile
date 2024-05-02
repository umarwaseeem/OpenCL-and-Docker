CC = gcc
CFLAGS = -Wall -Wextra -g
LFLAGS = -lOpenCL
SRCS = host.c
TARGET = host

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LFLAGS)

# Remove object file
clean:
	rm -f $(TARGET)

# Run the compiled file
run:
	./$(TARGET) 

# remove old file, Compile again, run the update file
crun: clean all run