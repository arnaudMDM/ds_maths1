CC=gcc
EDL=gcc
RM=rm

CCFLAGS=-Wall
LDFLAGS=
RMFLAGS=-f
LIBS=

EXE=tri_fusion
INTERFACE=TriFusion.h
REALISATION=$(INTERFACE:.h=.c)
OBJ=$(REALISATION:.c=.o)

$(EXE): $(OBJ)
	$(EDL) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	$(RM) $(RMFLAGS) $(EXE) $(OBJ)

TriFusion.o: TriFusion.h

%.o: %.c
	$(CC) $(CCFLAGS) -c $<
