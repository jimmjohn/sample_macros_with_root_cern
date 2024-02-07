
#define PI 3.14159265

void uniform_sphere()
{
TCanvas *c1 = new TCanvas("c1","Pi",0,0,600,600);
c1->cd();
TGraph2D *g= new TGraph2D();

Double_t theta,pie,radius,x,y,z;

for(int i=0;i<100000;i++)
{
theta=gRandom->Uniform(0,1);
theta=acos(2*theta-1);
pie=gRandom->Uniform(0,1);
pie=pie*2.0*PI;
radius=gRandom->Uniform(0,1);
radius=pow(15*radius,1.0/3.0);
x=radius*sin(theta)*cos(pie);
y=radius*sin(theta)*sin(pie);
z=radius*cos(theta);
g->SetPoint(i,x,y,z);
}
g->SetMarkerColor(kGreen);
g->SetTitle("Uniform Points inside solid sphere");
g->Draw("p");
}
