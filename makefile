#makefile

FTM_EXTRACT.exe: FTM_EXTRACT.o
		gcc -static -o FTM_EXTRACT.exe FTM_EXTRACT.o
		del FTM_EXTRACT.o

FTM_EXTRACT.o: FTM_EXTRACT.cpp Instrument.h FILE_OUTPUT.h FILE_INPUT.h EXTRACT_LIB.h 2A03Address.h stdafx.h
		gcc -c FTM_EXTRACT.cpp