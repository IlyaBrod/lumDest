/**
 *  Fonctions qui concernent le traitement d'images en couleur
 *                                      (PPM)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

/**
 * Extract a color channel of a ppm image (R,G,V)
 * and save it as a new image.
 * @param entree Input image name
 * @param sortie Output image name
 * @param channel Channel to extract 1=Red, 2=Green, 3=Blue
 */
void getChannel(char entree[35],char sortie[35],int channel);
