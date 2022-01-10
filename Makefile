CC     = gcc
OPT    = -O3

BASE_CCFLAGS    = -Wfatal-errors -Wpedantic -Wall -Wextra -std=gnu99
BASE_LIBS       = 

#-Wstrict-prototypes -Wfloat-equal -Wconversion

#For local builds
EXTRA_CFLAGS_SYMBOLS  = -fdata-sections -ffunction-sections
EXTRA_LFLAGS_SYMBOLS  = -Wl,--gc-sections -Wl,--strip-all
EXTRA_LFLAGS_STATIC   = -Wl,-Bstatic

#generic release
all: CCFLAGS    = $(LOCAL_INCLUDE) $(BASE_CCFLAGS) $(OPT)
all: LFLAGS     = $(LOCAL_LINK) $(BASE_LIBS)
all: executable

#extra flags for static release
msys-s: CCFLAGS = $(LOCAL_INCLUDE) $(BASE_CCFLAGS) $(OPT) $(EXTRA_CFLAGS_SYMBOLS)
msys-s: LFLAGS  = $(LOCAL_LINK) $(EXTRA_LFLAGS_STATIC) $(EXTRA_LFLAGS_SYMBOLS) $(BASE_LIBS) 
msys-s: executable

#Linux/Un*x release
linux: CCFLAGS  = $(BASE_CCFLAGS) $(OPT) $(EXTRA_CFLAGS_SYMBOLS)
linux: LFLAGS   = $(EXTRA_LFLAGS_SYMBOLS) $(BASE_LIBS) 
linux: executable

#Cygwin release
cygwin: CCFLAGS = $(LOCAL_INCLUDE) $(BASE_CCFLAGS) $(OPT)
cygwin: LFLAGS = $(LOCAL_LINK) $(BASE_LIBS) -Wl,--strip-all
cygwin: executable


executable: spcm2wav
executable: spcm2wav_seg
executable: drumspcm


spcm2wav: spcm2wav.o 
	$(CC) $(CCFLAGS) -o $@ $^ $(LFLAGS)

spcm2wav_seg: spcm2wav_seg.o 
	$(CC) $(CCFLAGS) -o $@ $^ $(LFLAGS)

drumspcm: drumspcm.o 
	$(CC) $(CCFLAGS) -o $@ $^ $(LFLAGS)

.c.o:
	$(CC) -c $(CCFLAGS) $< -o $@

clean:
	rm -f *.o
	rm -f drumspcm.exe
	rm -f spcm2wav.exe
	rm -f spcm2wav_seg.exe
