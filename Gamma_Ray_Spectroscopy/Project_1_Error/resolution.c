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
double temperror,resolution,error;
double en,ener,fw,fwer,co,coer,iseu,intense;
data datainfo[50];
file=fopen("Europium","r");
while(EOF != fscanf(file, " %lf %lf %lf %lf %lf %lf %d %lf ", &datainfo[i].energy, &datainfo[i].energyerror, &datainfo[i].fwhm, &datainfo[i].fwhmerror, &datainfo[i].count, &datainfo[i].counterror,&datainfo[i].iseuropium,&datainfo[i].intensity))
{
//printf("RA:%s,DEC:%s,mag_j:%lf,mag_h:%lf,mag_k:%lf\n",datainfo[i].ra, datainfo[i].dec, datainfo[i].mag_j, datainfo[i].mag_h, datainfo[i].mag_k);
if(datainfo[i].iseuropium==1)
{
FILE *fp;
fp=fopen("resolution_Eu.txt","a");
resolution=datainfo[i].fwhm/datainfo[i].energy;
temperror=sqrt(pow((datainfo[i].fwhmerror/datainfo[i].fwhm),2)+pow((datainfo[i].energyerror/datainfo[i].energy),2));
error=temperror*resolution;
printf("%d %lf %lf %lf \n",i,datainfo[i].energy,resolution,error);
fprintf(fp,"%lf %lf %lf \n",datainfo[i].energy,resolution,error);
fclose(fp);
}
i=i+1;
}

fclose(file);
return 0;

}
