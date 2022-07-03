CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 
LIBS = -lm -lpng -lgmp
RELEASE_FLAGS = -Ofast -DNDEBUG -march=native -mtune=generic -flto -ftree-vectorize
DEBUG_FLAGS = -g  -fsanitize=address
TARGET = galleryofbabel
$(TARGET): src/*.c
	$(CC) $(CFLAGS) $(LIBS) $(DEBUG_FLAGS) -o $(TARGET) src/*.c

release: src/*.c
	$(CC) $(CFLAGS) $(LIBS) $(RELEASE_FLAGS) -o $(TARGET) src/*.c