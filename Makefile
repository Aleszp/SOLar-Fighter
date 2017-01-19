.SILENT:

#nagłówki
_DEPS = object.hpp simple_object.hpp renderable.hpp star.hpp camera.hpp math.hpp orb.hpp mobile_object.hpp multi.hpp

#pliki obiektowe (nazwa jak dla źródłowych .cpp)
_OBJ = main.o  object.o simple_object.o star.o camera.o math.o orb.o mobile_object.o multi.o

#bibiloteki
LIBS=`allegro-config --libs` -lm -lalleggl
SETUPLIBS=-lncurses

IDIR =src
CXX=g++
CFLAGS=-I$(IDIR) -O3 -Wall -pedantic -std=c++11 -mtune=native -march=native

#katalog na tymczasowe pliki obiektowe
ODIR=obj
#katalog z plikami źródłowymi
SDIR=src
#katalog na plik(i) wynikowe
BDIR=bin

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	echo Kompiluję $<...
	@$(CXX) -c -o $@ $< $(CFLAGS)

all:  $(BDIR)/SOLar_Fighter	$(BDIR)/SOLar_Setup

$(BDIR)/SOLar_Fighter: $(OBJ)
	echo Buduję program...
	@$(CXX) -o $@ $^ $(CFLAGS) $(LIBS)

$(BDIR)/SOLar_Setup: $(SDIR)/setup.cpp
	echo Buduję program konfiguracyjny...
	@$(CXX) -o $(BDIR)/SOLar_Setup $(SDIR)/setup.cpp $(CFLAGS) $(SETUPLIBS)

.PHONY: clean

clean:
	echo Usuwam pliki wynikowe...
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ $(BDIR)/*

.PHONY: install

install:
	echo Tworzę katalog plików konfiguracyjnych...
	mkdir -p ~/.SOLar-Fighter
	echo Kopiuję pliki gry...
	sudo cp ./bin/SOLar_Fighter /usr/games/SOLar_Fighter
	sudo cp ./bin/SOLar_Setup /usr/games/SOLar_Setup
	echo "Gotowe :)"
