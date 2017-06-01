#include "tgm.hpp"

TGM::TGM(const char* pgmin,const char* pgmout)
{
pic = new PgmFunctions(pgmin,pgmout);
}

void TGM::cramer(double lig1[3], double lig2[3],double result[2])
{   
    //a1X+b1Y = c1  => X = result[0] & Y = result[1]
    //a2X+b2Y = c2 
    double Delta  = (lig1[0]*lig2[1]) - (lig2[0]*lig1[1]);
    result[0] = ( lig1[2]*lig2[1]-lig2[2]*lig1[1] ) / Delta;
    result[1] = ( lig1[0]*lig2[2]-lig2[0]*lig1[2] ) / Delta;
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

    /* CALCUL DE X0 (position du laser)
    grâce aux points aux exttrémités où  Z=0*/

    long int point[2];
    pic -> point_un(point); //récupération de l'extrémité
    readCSV(); //récupération de la matriec de calobrage

    //point[0] = 787;
    //point[1] = 1283;
    //point[0] = 877;
    //point[1] = 1173;
    double lig1[3];
    lig1[0] = (M[8]*point[0]-M[0]);
    lig1[1] = (M[9]*point[0]-M[1]);
    lig1[2] = (M[3]-M[11]*point[0]);
    double lig2[3];
    lig2[0] = (M[8]*point[1]-M[4]);
    lig2[1] = (M[9]*point[1]-M[5]);
    lig2[2] = (M[7]-M[11]*point[1]);
    /*
    printf("M : \n");
    for(int i =0;i<12;i++)
        printf("%1.10f\n",M[i]);
    */
    //printf("lig : %1.10f ; %1.10f ; %1.10f\n",lig1[0],lig1[1],lig1[2]);
    //printf("lig : %f ; %f ; %f\n",lig2[0],lig2[1],lig2[2]);
    double result[2];
    cramer(lig1,lig2,result);

    printf("2D point : X=%ld Y=%ld\n", point[0],point[1]);
    printf("3D point : X=%f Y=%f Z=%f\n",result[0],result[1],0.0);

    double laser_x = result[0];
    printf("X = %f\n",laser_x);
    /* CALCUL DES POINTS Y,Z */

    pic ->pgm_uv_reader();
    for(long int i=0;i<pic->point_u.size();i++)
    {
        point[0] = pic->point_u[i];
        point[1] = pic->point_v[i];

        lig1[0] = point[0]*M[9]-M[1];
        lig1[1] = point[0]*M[10]-M[2];
        lig1[2] = -laser_x*(point[0]*M[8]-M[0]) - (point[0]*M[11]-M[3]);

        lig2[0] = point[1]*M[9]-M[5];
        lig2[1] = point[1]*M[10]-M[6];
        lig2[2] = -laser_x*(point[1]*M[8]-M[4]) - (point[1]*M[11]-M[7]);

        cramer(lig1,lig2,result);
        x.push_back(laser_x);
        y.push_back(result[0]);
        z.push_back(result[1]);
    }

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


void TGM::saveXYZ(const char* outputName)
{
    FILE *fir;

    fir = fopen(outputName, "wb+");
    if (fir == NULL) printf("ExportError: Impossible to create output XYZ file\n");
    fprintf(fir,"X;Y;Z\n");

    for(long int i=0;i<x.size();i++)
    {
        fprintf(fir,"%1.10f;%1.10f;%1.10f\n",x[i],y[i],z[i]);
    }
    fclose(fir);

}

TGM::~TGM()
{
    free(pic);
}