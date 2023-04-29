CC=gcc
CFALGS=-Wall -g
EXECUTABLE=graph
OBJ_DIR=obj

all: mkdir $(EXECUTABLE)

$(EXECUTABLE): main.o file.o matrix_parser.o graph.o
	$(CC) $(CFLAGS) -o $(EXECUTABLE) main.o file.o matrix_parser.o graph.o;
	mv *.o $(OBJ_DIR)/;

main.o: main.c
	$(CC) $(CFALGS) -c main.c

file.o: src/file.c
	$(CC) $(CFALGS) -c src/file.c

matrix_parser.o: src/matrix_parser.c
	$(CC) $(CFALGS) -c src/matrix_parser.c

graph.o: src/graph.c
	$(CC) $(CFALGS) -c src/graph.c

mkdir:
	mkdir $(OBJ_DIR) -p

clean:
	rm -rf *.o $(OBJ_DIR) $(EXECUTABLE) graph.txt graph_vizualization.png
