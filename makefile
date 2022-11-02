# $< => o arquivo de prerequisito (.c)
# $@ => o arquivo otimizado/arquivo objeto (.o)
# $^ => os nomes de todos os prerequisitos separados por espacos
#
#
PROJ_NAME=luta
C_SOURCE=$(wildcard *.cpp)
H_SOURCE=$(wildcard *.h)
OBJ=$(C_SOURCE:.c=.o)
CC=g++
CC_FLAGS=-c         \
         -W         \
         -Wall      \
         -std=c11      \
         -pedantic    \
	 -lm         \
	 -O2

all: $(PROJ_NAME)
 
$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^ -lGL -lGLU -lglut
 
%.o: %.c %.h
	$(CC) -o $@ $< $(CC_FLAGS)
 
main.o: main.c $(H_SOURCE)
	$(CC) -o $@ $< $(CC_FLAGS)
 
clean:
	rm -rf *.o $(PROJ_NAME) *~
