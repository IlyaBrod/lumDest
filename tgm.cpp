#include "tgm.hpp"

TGM::TGM(const char* pgmin,const char* pgmout)
{
pic = new PgmFunctions(pgmin,pgmout);
}

void TGM::cramer(float lig1[3], float lig2[3],float result[2])
{   
    float Delta  = (lig1[0]*lig2[1]) - (lig2[0]*lig1[1]);
    result[0] = ( lig1[0]*lig2[2]-lig2[0]*lig1[2] ) / Delta;
    result[1] = ( lig1[1]*lig2[2]-lig2[1]*lig1[2] ) / Delta;
}


void TGM::open(const char* pgmin,const char* pgmout)
{
    free(pic);
   pic = new PgmFunctions(pgmin,pgmout);

}

void TGM::calcule_XYZ()
{
    /* TRAITEMENT DE L'IMAGE */
    pic->seuil();
    pic->complete_ligne();
    pic->select_haut();
    pic->passe_bas(1);
    pic->pas_isole();
    pic->passe_bas(10);
    pic->capt_point_extremite();
    pic->pgm_point_extremiter();
    pic->trace_Lines();

    /* CALCUL DE X0 */
    long int point[2];
    pic -> point_un(point);
    readCSV();
    //printf("%ld ;%ld\n",point[0],point[1]);

    float lig1[3];
    lig1[0] = (M[0]-M[8]*point[0]);
    lig1[1] = (M[1]-M[9]*point[0]);
    lig1[2] = (M[11]*point[0]);
    float lig2[3];
    lig2[0] = (M[4]-M[8]*point[1]);
    lig2[1] = (M[5]-M[9]*point[1]);
    lig2[2] = (M[11]*point[1]);
    //printf("lig : %f ; %f ; %f\n",lig1[0],lig1[1],lig1[2]);
    //printf("lig : %f ; %f ; %f\n",lig2[0],lig2[1],lig2[2]);
    float result[2];
    cramer(lig1,lig2,result);
    printf("%f \n%f \n", result[0], result[1]);

    /* CALCUL DES POINTS Y,Z */

}


void TGM::readCSV()
{
    FILE *fcvs = fopen("M.cvs","rb");
    if(fcvs == NULL)
    {
        printf("M.CVS doesn't exist\n");
        exit(EXIT_FAILURE);
    }

    for(int i=0;i<12;i++)
        fscanf(fcvs,"%f\n",&M[i]);
    
    fclose(fcvs);
}

TGM::~TGM()
{
    free(pic);
}