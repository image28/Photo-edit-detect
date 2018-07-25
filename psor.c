// By Kevin
// Old version of photoshop or real detection, might require tweaking of the sensitivity value marked by a comment bellow
// requires SDL and SDL_image to compile

#include "defines.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

int main(int argc, char *argv[])
{
	if ( argc < 1 )
	{
		printf("USAGE: %s [image file to check]\n",argv[0]);
		return(1);
	}else{
		find(argc,argv);
		return(0);
	}
}

int find(int argc, char *files[])
{
	FILE *output;
	SDL_Surface *surface;
	unsigned long filesize=0;
	unsigned long pixel_count=0;
	int start=0;
	int d,i,l;
	int inbyte=0;
	Uint8 *pixel;
	int temp=0;
	long pos=0;
	int count=0;
	int count2=0;

	surface=IMG_Load(files[1]);
	pixel_count=(surface->w*surface->h)*3;
	pixel=(Uint8 *)surface->pixels;
	
	if( SDL_MUSTLOCK( surface ) ) 
	{ //Lock the surface 
		SDL_LockSurface( surface ); 
	} 
	
	for(l=0;l<pixel_count-64;l=l+4)
	{

		for(i=0; i < 3; i++)
		{
			inbyte=0;
			inbyte=pixel[l+i]%2;
			printf("%d ",pixel[l+i]);
			if ( ( inbyte != 254 ) && ( inbyte != 0 ) )
			{
				if ( inbyte == pixel[l+i+3]%2 )
				{
					count++;
		
				}
			}
				
	
		}
	
		if ( count == 3 )
		{
			count2++;
		}else{
			count2=0;
		}


		if ( count2 > 4 ) // Adjust the 4 to change sensitivity
		{
			printf("Photoshopped");
	
			if( SDL_MUSTLOCK( surface ) ) 
			{ //Lock the surface 
				SDL_UnlockSurface( surface ); 
			} 
			
			SDL_FreeSurface(surface);
			exit(-1);
		}
	
		printf("\n");
		count=0;

	
		pos++;
	}
	
	
	if( SDL_MUSTLOCK( surface ) ) 
	{ //Lock the surface 
		SDL_UnlockSurface( surface ); 
	} 
	
	SDL_FreeSurface(surface);

	printf("Real");
	return(0);
}