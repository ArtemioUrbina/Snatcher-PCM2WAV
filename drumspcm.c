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
	FILE	*file = NULL, *wav = NULL;
	int 	read = EOF, write, count = 0, create = 0, i = 0, icount = 1;
	long int size = 0;
	char	FileName[50];
	int   wavheader[] = {
		0x52, 0x49, 0x46, 0x46, 0x00, 0x00, 0x00, 0x00, 0x57, 0x41, 
		0x56, 0x45, 0x66, 0x6d, 0x74, 0x20, 0x10, 0x00, 0x00, 0x00, 
		0x01, 0x00, 0x01, 0x00, 0x80, 0x3e, 0x00, 0x00, 0x80, 0x3e, 
		0x00, 0x00, 0x01, 0x00, 0x08, 0x00, 0x64, 0x61, 0x74, 0x61,
		0x00, 0x00, 0x00, 0x00, 0xFF
			};
	int skip[] = {
	  5, 7, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32,
	  34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 59, 64,
	  72, 76, 81, 83, 89, 92, 129, 130, 131, 132, 133, 134, 135, 
	  136, 1258, 0
	    };

	printf("Snatcher Drum PCM extractor by Artemio Urbina V 1.0.2.0\n");
	file = fopen("PCMDRMDT.BIN", "r");
	if(!file)
	{
		printf("Could not open PCMDRMDT.BIN, please copy it to this folder\n");
		return(0);
	}

	do
	{
		read = fgetc(file);
		if(read != EOF)
		{
			if(create)
			{
				int i = 0, EmptyFile = 0;
				
			  count++;
			  
			  do
			  {
			  	if(skip[i] == count)
			  		EmptyFile = 1;
			  }while(!EmptyFile && skip[i++]);
			  
			  if(!EmptyFile)
				{
					sprintf(FileName, "SnatcherDrum%d.wav", icount++);
					printf("Writing to %s\n", FileName);
					wav = fopen(FileName, "w");
					if(!wav)
					{
						fclose(file);
						printf("Could not create output file\n");
						return(0);
					}
					
					i = 0;
					do
					{
						write = wavheader[i++];
						if(write != 0xFF)
							fputc(write, wav);
					}
					while(write != 0xFF);
				}
				create = 0;
				size = 0;
			}

			if(read < 0x80)
				write = 0x80 - read;
			else
				write = read;

			if(write == 0xFF)		
			{
				int skip = 0;

				// Fix Header
				if(wav)
				{
					// Finish File
					fputc(0x00, wav);
					
					if(!fseek(wav, 0x04, SEEK_SET) )
					{
						char high, low;
						
						high = ((size + 0x25) & 0x0000FF00) >> 8;
						low = 0x000000FF & (size + 0x25);
						fputc(low, wav);
						fputc(high, wav);
						
						high = ((size + 0x25) & 0xFF000000) >> 24;
						low = (0x00FF0000 & (size + 0x25)) >> 16;
						fputc(low, wav);
						fputc(high, wav);
					}
					else
					   printf("Could not fix header\n");
					
					if(!fseek(wav, 0x28, SEEK_SET) )
					{
					  char high, low;
						
						high = (size & 0x0000FF00) >> 8;
						low = 0x000000FF & size;
						fputc(low, wav);
						fputc(high, wav);
						
						high = (size & 0xFF000000) >> 24;
						low = (	0x00FF0000 & size) >> 16;
						fputc(low, wav);
						fputc(high, wav);
					}
					else
					   printf("Could not fix header\n");
					   
					fclose(wav);
					wav = NULL;
				}

				do
				{
					read = fgetc(file);
					skip ++;
				}
				while(skip < 12 && read != EOF);
				
				create = 1;
			}
			else
				if(wav)
				{
					fputc(write, wav);
					size ++;
				}
		}
	}
	while(read != EOF);
	
	fclose(wav);
	fclose(file);
	printf("Conversion complete\n");
	return(1);
}

