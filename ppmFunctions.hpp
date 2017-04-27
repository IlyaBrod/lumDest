#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

/**
 * Extract a color channel of a ppm image (R,G,V)
 * and save it as a new image.
 * @param entree Input image name witout ".ppm"
 * @param sortie Output image name witout ".pgm"
 * @param channel Channel to extract 1=Red, 2=Green, 3=Blue
 */
void getChannel(char entree[35],char sortie[35],int channel);

/**
 * Color some points of a pgm image
 * @param entree Input image name witout ".pgm"
 * @param sortie Output image name witout ".ppm"
 * @param  points List of points int[2]
 */
//void coloration(char entree[35], char sortie[35],unsigned char *points);