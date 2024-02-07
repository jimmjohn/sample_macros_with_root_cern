#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

typedef struct node {
    double energy;
    double energyerror;
    double fwhm;
    double fwhmerror;
    double count;
    double counterror;
    int iseuropium;
    double intensity;
} data;

int main(void)
{
FILE *file;
int i=0,j=0;
double efficiency,activity,error;
activity=25521;
data datainfo[50];
file=fopen("Europium","r");
while(EOF != fscanf(file, " %lf %lf %lf %lf %lf %lf %d %lf ", &datainfo[i].energy, &datainfo[i].energyerror, &datainfo[i].fwhm, &datainfo[i].fwhmerror, &datainfo[i].count, &datainfo[i].counterror,&datainfo[i].iseuropium,&datainfo[i].intensity))
{
//printf("RA:%s,DEC:%s,mag_j:%lf,mag_h:%lf,mag_k:%lf\n",datainfo[i].ra, datainfo[i].dec, datainfo[i].mag_j, datainfo[i].mag_h, datainfo[i].mag_k);
if(datainfo[i].iseuropium==1)
{
FILE *fp;
fp=fopen("efficency_Eu.txt","a");
efficiency=datainfo[i].count/(datainfo[i].intensity*34*activity);
error=(sqrt((pow(datainfo[i].counterror/datainfo[i].count,2))+(pow(0.0023,2))))*efficiency;
fprintf(fp,"%lf %lf %lf\n",datainfo[i].energy,efficiency,error);
fclose(fp);
}
i=i+1;
}

fclose(file);
return 0;

}
