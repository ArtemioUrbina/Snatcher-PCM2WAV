/* 
 * Copyright (C)2008 Artemio Urbina
 *
 *
 * Snatcher PCM to WAV is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Snatcher PCM to WAV is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with 240p Test Suite; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "stdio.h"

int ConvertToWav();

int main()
{
	if(!ConvertToWav())
		return(1);

	return(0);
}

int ConvertToWav()
{
	FILE	*file, *wav;
	int		read = EOF, write, i = 0;
	int		wavheader[] = {
				0x52, 0x49, 0x46, 0x46, 0x42, 0xe8, 0x0c, 0x05, 0x57, 0x41,
				0x56, 0x45, 0x66, 0x6d, 0x74, 0x20, 0x10, 0x00, 0x00, 0x00,
				0x01, 0x00, 0x01, 0x00, 0x80, 0x3e, 0x00, 0x00, 0x80, 0x3e,
				0x00, 0x00, 0x01, 0x00, 0x08, 0x00, 0x64, 0x61, 0x74, 0x61,
				0x1e, 0xe8, 0x0c, 0x05, 0xFF
			};

	printf("Snatcher PCM to WAV converter by Artemio Urbina V 1.0.2.1\n");
	file = fopen("PCMLD_01.BIN", "rb");
	if(!file)
	{
		printf("Could not open PCMLD_01.BIN, please copy it to this folder\n");
		return(0);
	}
	wav = fopen("Snatcher_PCM.wav", "wb");
	if(!wav)
	{
		fclose(file);
		printf("Could not create output file\n");
		return(0);
	}

	do
	{
		write = wavheader[i++];
		if(write != 0xFF)
			fputc(write, wav);
	}
	while(write != 0xFF);

	printf("Writing to Snatcher_PCM.wav\n");
	fflush(stdout);
	do
	{
		read = fgetc(file);
		if(read != EOF)
		{
			if(read < 0x80)
				write = 0x80 - read;
			else
				write = read;

			if(write == 0xFF)
			{
				int skip = 0;

				do
				{
					read = fgetc(file);
					skip ++;
				}
				while(skip < 12 && read != EOF);
			}
			else
				fputc(write, wav);
		}
	}
	while(read != EOF);

	fclose(wav);
	fclose(file);
	printf("Conversion complete\n");
	return(1);
}
