CC=gcc
CFLAGS=-g -Wall
OUT=rend.out

OBJ=o/main.o o/wnd.o o/evt.o o/render.o

INCLUDE=-I ~/glfw/deps -I deps/glad/glad/include -I ./head
LINK=-L/usr/local/lib -lglfw3 -lrt -lm -ldl -lGL -lglut -lglfw3 -lX11 -lGLU -lpthread

run: build
	./$(OUT)

build: $(OBJ) o/glad.o
	$(CC) $(OBJ) o/glad.o $(LINK) -o$(OUT)

o/glad.o: ./deps/glad/glad/src/glad.c
	$(CC) $(CFLAGS) -c ./deps/glad/glad/src/glad.c -o o/glad.o

o/%.o: src/%.c
	$(CC) $(INCLUDE) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJ) o/glad.o $(OUT)

cleanbuild:
	make clean
	make