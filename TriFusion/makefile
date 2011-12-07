CC=gcc
EDL=gcc
RM=del

CCFLAGS=-Wall
LDFLAGS=
RMFLAGS=
LIBS=

EXE=TriFusion.exe
INTERFACE=Trifusion.h
REALISATION=$(INTERFACE:.h=.c)
OBJ=$(REALISATION:.c=.o)

$(EXE): $(OBJ)
	$(EDL) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	$(RM) $(RMFLAGS) $(EXE) $(OBJ)

TriFusion.o: TriFusion.h

%.o: %.c
	$(CC) $(CCFLAGS) -c $<
