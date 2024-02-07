#define PI 3.14159265

void question4()
{
TCanvas *c1 = new TCanvas("c1", "canvas",1000,1000);
c1->cd();
c1->Divide(2,1);
gStyle->SetOptFit(1111);
double x1,x2,x3,y1,y2,a1,a2,normalization;
TGraph *g1= new TGraph();
TGraph *g2= new TGraph();


for(int i=0;i<100000;i++)
{
x1=((double) rand() / (RAND_MAX));
x2=((double) rand() / (RAND_MAX));
x3=((double) rand() / (RAND_MAX));
y1=sqrt(-2.0*log(x1))*cos(2.0*PI*x2);
y2=sqrt(-2.0*log(x1))*sin(2.0*PI*x2);
a1=-0.6*y1+0.8*y2;
a2=-0.6*y1+y2;
y1=y1*4.0+3.0;
y2=y2*4.0+3.0;
g1->SetPoint(i,y1,y2);
a1=a1*3.2+3.0;                            //Modified Variance (sigma_y)^2(1-rho^2) . (Mean is not modified, since both are having same mean)
a2=a2*3.2+3.0;                            //Modified Variance (sigma_y)^2(1-rho^2) . (Mean is not modified, since both are having same mean)

g2->SetPoint(i,a1,y1);

}
c1->cd(1);
g1->Draw("AP");

c1->cd(2);

g2->Draw("AP");

cout<< g2->GetCorrelationFactor() <<endl;
}
