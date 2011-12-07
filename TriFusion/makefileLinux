CC=gcc
EDL=gcc
RM=rm

CCFLAGS=-Wall
LDFLAGS=
RMFLAGS=-f
LIBS=

EXE=TpReferencesCroisees
INTERFACE=AssocRefFichier.h References.h
REALISATION=$(INTERFACE:.h=.cpp) Main.cpp
OBJ=$(REALISATION:.cpp=.o)

$(EXE): $(OBJ)
	$(EDL) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	$(RM) $(RMFLAGS) $(EXE) $(OBJ)

Main.o: References.h
	
References.o: References.h AssocRefFichier.h

AssocRefFichier.o: AssocRefFichier.h

%.o: %.cpp
	$(CC) $(CCFLAGS) -c $<
