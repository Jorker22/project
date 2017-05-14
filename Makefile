

ifeq ($(OSTYPE),WINDOWS)
	EXECEXT =.exe
	COMP	=__MINGCC__
	PLATFORM	=mingw
else
	EXECEXT =
	COMP	=__GCC__
	PLATFORM	=linux
endif

EXECUTABLES= Main$(EXECEXT) 

all : $(EXECUTABLES)

Main.o : Main.c AddRel.h familynetwork.h networkwriter.h
	gcc -c Main.c

AddRel.o :	AddRel.c networkWriter.h familynetwork.h
	gcc -c AddRel.c

familywriter.o : familywriter.c familynetwork.h networkwriter.h
	gcc -c familywriter.c

Main$(EXECEXT) : Main.o AddRel.o familywriter.o
	gcc -o Main$(EXECEXT) Main.o AddRel.o \
	familywriter.o

clean : 
	-rm *.o
	-rm $(EXECUTABLES) 