

void pie()

{

TCanvas *c1 = new TCanvas("c1","Evaluvate Pi",0,0,400,400);
c1->cd();
TGraph *g1= new TGraph();
TEllipse *el1 = new TEllipse(0,0,0.5,0.5);
TBox *b = new TBox(-0.5,-0.5,0.5,0.5);
static unsigned int rn,p,k,total=0;
double r,x,s,sum;
double xm1,ym1,xm3;
double pie;
UInt_t n=10000,i;

for(i=0;i<n;i++)
{
k=rand();
r=(double)k/RAND_MAX;
k=rand();
s=(double)k/RAND_MAX;
sum=pow(r-0.5,2)+pow(s-0.5,2);
if(sum<.25)
{total=total+1;

}
g1->SetPoint(i,r-0.5,s-0.5);

}
pie=(double)4.0*total/10000.0;
cout<<"pie for n(10000)="<<pie<<endl;
g1->SetTitle("Graph for n=10000");
g1->Draw("AP*");
el1->SetFillStyle(0);
el1->SetLineWidth(3);
b->SetFillStyle(0);
b->SetLineWidth(3);
el1->SetLineColor(4);
b->SetLineColor(4);
el1->Draw("same");
b->Draw("same");
}





















