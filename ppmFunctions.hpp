/*
  This file is part of LumDest.

    Foobar is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    LumDest is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with LumDest.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2017 Brodoline Ilya & Pichon Hugot

*/

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
