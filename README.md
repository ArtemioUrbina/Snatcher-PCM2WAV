# Snatcher-PCM2WAV
---------------------------------------------------------------------------
    Snatcher PCM to WAV (SPCM2WAV) v1.0.2.0 (8/26/08) by Artemio Urbina
---------------------------------------------------------------------------

Change Log:
-----------
v 1.0.0.0 
	-Initial release, private beta
v 1.0.1.0 (7/20/08)
	-Added Drum Sample extractor
	-Added Segmented PCM dumper
	-Changed single file dumper to eliminate in-between clip noise
v 1.0.2.0 (8/26/08)
	-Drum Sample extractor and Segment Extractor now create proper wav files
	-Eliminated empty wavs from the pcm file resulting in 1214 files
v 1.0.2.1 (1/09/22)
	-Compiled 64 bit executables
	-Fixed binary file usage for proper functionality
	
	
Contents of the package:
------------------------

	-spcm2wav.exe (Single wav Windows version)
	-spcm2wav.c (Single wav dump source code, compile for your own OS)
	-drumspcm.exe (extracts PCM files that contain the drum samples)
	-drumspcm.c (Drum sample extractor source code, compile for your own OS)
	-spcm2wav_seg.exe (Multiple wav extractor Windows version)
	-spcm2wav_seg.c (Multiple wav extractor source code, compile for your own OS)
	-readme.txt (this readme)

What it does:
------------

Thanks to the efforts of Artemio Urbina and the constant nagging of fellow 
Snatcher enthusiast Joey Migeed, a new program has been developed that 
successfully converts the 80.8 megabyte raw PCM file (PCMLD_01.BIN) from the
Sega/Mega CD version of Snatcher into a listenable WAV file at the highest 
quality possible. This PCM file that the program converts contains all of the
sound effects and most of the dialogue from Sega CD Snatcher (the rest of the
dialogue is contained in the redbook audio tracks on the disc, mixed with 
music). This program techically does not convert anything at all; it simply 
performs arithmetic on the PCM file to decode it into a standard wave file.

The previous method of converting this file involved using a utility called 
PCM2WAV, designed for converting audio from the Sega CD Lunar games. Using 
that program on the Snatcher PCM file unfortunately discarded half the data 
and therefore half the quality due to the linear fashion of PCM audio. You 
would get a mono, 8 kilohertz, 8 bit file. The full resolution is decoded by 
SPCM2WAV, at 16 kilohertz (also mono and 8 bits). As you might guess, those 
extra kilohertz make a world of difference!

So, how to use the program? It's very simple:

1. Copy the PCMLD_01.BIN file from a Sega CD or Mega CD Snatcher disc or 
image to a folder on your computer.
2. Put the contents of this zip file in the same folder as the BIN file.
3. Run the program of your choice. It is a command line program so cmd.exe
will open up if you're using Windows. Wait a few seconds, and the program will
have created a file called Snatcher_audio.wav in the directory it was in.
4. Open the WAV in your favorite audio player and enjoy the dialogue and 
sound effects from Snatcher at full quality!

The same process can be applied for the other two programs, but the segmented
version will output 1214 wav files instead of one wav file. The drum sample 
extractor will do likewise, but will get you 7 samples used for the in-game
music (probably Akira Yamaoka's work). The file used for this is PCMDRMDT.BIN.

Precompiled versions are available for Windows. The source code is also 
available so you may compile it yourself if you're using another operating
system.

Although questions are not anticipated, they may be asked at the JUNKER HQ 
forums at http://forums.junkerhq.net where a topic about these programs is 
currently open.

Credits:
Artemio Urbina (audio decoding, programming and primary beta tester)
Joey Migeed (concept, secondary beta tester, and readme)

http://junkerhq.net

