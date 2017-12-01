CC=g++
OPCOES_COMPILADOR=-I../include
OPCOES_LINKEDITOR=-L../lib/linux -lSOIL -lGL -lm -lstdc++
TODOS_ARQUIVOS_PONTOH = ../output.h ../ray.h ../raytracer.h ../scene.h ../vector.h
TODOS_ARQUIVOS_OBJ = main.o output.o vector.o scene.o raytracer.o

%.o: ../%.cpp $(TODOS_ARQUIVOS_PONTOH)
	$(CC) -o $@ -c $< $(OPCOES_COMPILADOR)

all: $(TODOS_ARQUIVOS_OBJ)
	$(CC) -o raytracer $^ $(OPCOES_COMPILADOR) $(OPCOES_LINKEDITOR)

run: all
	(cd ../.. && exec cpp/Makefile/raytracer cena-simples.txt)

run-simples: all
	(cd ../.. && exec cpp/Makefile/raytracer cena-simples.txt)

run-2-fontes-luz: all
	(cd ../.. && exec cpp/Makefile/raytracer cena-2-fontes-luz.txt)

run-3-esferas: all
	(cd ../.. && exec cpp/Makefile/raytracer cena-3-esferas.txt)

run-esferas: all
	(cd ../.. && exec cpp/Makefile/raytracer cena-esferas.txt)

clean:
	rm *.o raytracer
