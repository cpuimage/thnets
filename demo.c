#include <string.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include "thnets.h"
// http://tntmonks.cnblogs.com/
THNETWORK * net;

char * labels[] = { "lamp"," bottle"," watch"," pen"," grass"," shoe"," wall"," chair"," mug"," fork"," table"," book"," tablet"," bookcase"," pencil"," door"," face"," ceiling"," sofa"," bicycle"," aluminum - can"," window"," road"," stairs"," floor"," painting"," toy"," remote"," computer"," plant"," television"," dog"," laptop"," microwave"," cat"," tree"," knife"," car"," motorcycle"," person"," cup"," sidewalk"," telephone"," spoon"," hand"," sofabed" };

int main(int argc, char ** argv) {
	img_t image = { 0 };
	//test.jpg 
	char * pic_file = argv[1];
	//model
	char * model_path = argv[2];

	int dropclassifier = 0;
	loadimage(pic_file, &image);
	THInit();
	printf("init_thnets.");
	net = THLoadNetwork(model_path);
	if (net) {
		THUseSpatialConvolutionMM(net, 2);
		if (dropclassifier == 1) {
			if (net->net->modules[net->net->nelem - 1].type == MT_SoftMax)
				net->net->nelem--;
			if (net->net->modules[net->net->nelem - 1].type == MT_Linear)
				net->net->nelem--;
			if (net->net->modules[net->net->nelem - 1].type == MT_View)
				net->net->nelem--;
		}
	}
	else {
		printf("Shiiiiit went down.");
		return -1;
	}
	float * percentages = 0;
	int outwidth, outheight;

	if (!net) {
		return 0;
	}
	int i = 0;
	int nbatch = 1;
	unsigned char *bitmaps[256];
	for (i = 0; i < nbatch; i++)
		bitmaps[i] = image.bitmap;
	int size = THProcessImages(net, bitmaps, nbatch, image.width, image.height, image.cp * image.width, &percentages, &outwidth, &outheight, 0);
	for (i = 0; i < nbatch; i++)
		if (bitmaps[i])
			free(bitmaps[i]);
	if (percentages)
	{
		float max[3] = { 0 };
		int maxPos[3] = { 0 };
		for (int j = 0; j < size; j++) {
			if (percentages[j] > max[0]) {
				maxPos[0] = j;
				max[0] = percentages[j];
			}
			else if (percentages[j] > max[1]) {
				maxPos[1] = j;
				max[1] = percentages[j];
			}
			else if (percentages[j] > max[2]) {
				maxPos[2] = j;
				max[2] = percentages[j];
			}
		}
		for (int index = 0; index < 3; index += 1) {
			const float predictionValue = max[index];
			if (predictionValue > 0.05f) {
				printf(" %f %s  \n", predictionValue, labels[maxPos[index] % size]);
			}
		}
		free(percentages);
	}
	getchar();
}