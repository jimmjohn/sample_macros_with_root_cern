
void get_pi()
{

TCanvas *c1 = new TCanvas("c1","Pi",0,0,1500,400);
c1->Divide(3,1);

c1->cd(1);
TGraph *g1= new TGraph();
long double random1,random2,sum;
long double pi,total=0;
unsigned int i;
unsigned int n=100;
char title[100];
for(i=0;i<n;i++)
{
random1=rand();
random1=random1/RAND_MAX;
random2=rand();
random2=random2/RAND_MAX;
sum=pow(random1-0.5,2)+pow(random2-0.5,2);
if(sum<.25)
{
total=total+1;
g1->SetPoint(i,random1-0.5,random2-0.5);
}
}
long double nconv=(long double)n;
pi=(long double)4.0*total/nconv;
cout<<"pi="<<pi<<endl;
sprintf(title, "Pi for n = 100 is %Lf", pi);
g1->GetXaxis()->SetTitle("X");
g1->GetXaxis()->CenterTitle();
g1->GetYaxis()->SetTitle("Y");
g1->GetYaxis()->CenterTitle();
g1->SetTitle(title);
g1->Draw("AP");

c1->cd(2);
TGraph *g2= new TGraph();
n=10000;
total=0;
for(i=0;i<n;i++)
{
random1=rand();
random1=random1/RAND_MAX;
random2=rand();
random2=random2/RAND_MAX;
sum=pow(random1-0.5,2)+pow(random2-0.5,2);
if(sum<.25)
{
total=total+1;
g2->SetPoint(i,random1-0.5,random2-0.5);
}
}
nconv=(long double)n;
pi=(long double)4.0*total/nconv;
cout<<"pi="<<pi<<endl;
sprintf(title, "Pi for n = 10000 is %Lf", pi);
g2->GetXaxis()->SetTitle("X");
g2->GetXaxis()->CenterTitle();
g2->GetYaxis()->SetTitle("Y");
g2->GetYaxis()->CenterTitle();
g2->SetTitle(title);
g2->Draw("AP");

c1->cd(3);
TGraph *g3= new TGraph();
n=1000000;
total=0;
for(i=0;i<n;i++)
{
random1=rand();
random1=random1/RAND_MAX;
random2=rand();
random2=random2/RAND_MAX;
sum=pow(random1-0.5,2)+pow(random2-0.5,2);
if(sum<.25)
{
total=total+1;
g3->SetPoint(i,random1-0.5,random2-0.5);
}
}
nconv=(long double)n;
pi=(long double)4.0*total/nconv;
cout<<"pi="<<pi<<endl;
sprintf(title, "Pi for n = 1000000 is %Lf", pi);
g3->GetXaxis()->SetTitle("X");
g3->GetXaxis()->CenterTitle();
g3->GetYaxis()->SetTitle("Y");
g3->GetYaxis()->CenterTitle();
g3->SetTitle(title);
g3->Draw("AP");


}






















