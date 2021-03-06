#define  _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef MEMORYDEBUG
#include "memorydebug.h"
#endif
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "thnets.h"
#ifdef USECUDAHOSTALLOC

void *cmalloc(size_t size)
{
	void *ptr = 0;

	errcheck(cudaHostAlloc(&ptr, size, cudaHostAllocMapped));
	return ptr;
}

#else
#define cmalloc(a) malloc(a)
#endif


int loadimage(const char *path, img_t *image)
{
	const char *p = strrchr(path, '.');
	if(!p)
		return -1;
	const char *fn = strrchr(path, '/');
	if(fn)
		fn++;
	else fn = path;
	strcpy(image->filename, fn);
	image->bitmap = stbi_load(path, &image->width, &image->height, &image->cp, 0);
	if(image->cp == 4)
	{
		free(image->bitmap);
		image->bitmap = stbi_load(path, &image->width, &image->height, &image->cp, 3);
	}
	if(!image->bitmap)
		return -1;
#ifdef USECUDAHOSTALLOC
	unsigned char *data = image->bitmap;
	image->bitmap = cmalloc(image->cp * image->width * image->height);
	if(image->bitmap)
	{
		memcppy(image->bitmap, data, image->cp * image->width * image->height);
		free(data);
		return 0;
	} else {
		free(data);
		return -1;
	}
#endif
	return 0;
}
