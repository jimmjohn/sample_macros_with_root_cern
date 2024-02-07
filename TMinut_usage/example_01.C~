//Minuit is conceived as a tool to find the minimum value of a multiparameter function and analyze the shape of the function around the minimum.
//It is especially suited to handle difficult problems, including those which may require guidance in order to find the correct solution. 



//Let’s perform a 2D minimum finding with the TMinuit class:

//THE CORE FCN FUNCTION
//The most important function is the “FCN”. The user of Minuit must always supply a routine which calculates the function value to be minimized or analyzed.

//The structure:
//npar – number of currently variable parameters. 
//gin – the (optional) vector of first derivatives.
//f – the calculated function value. 
//par – vector of (constant and variable) parameters. 
//iflag – indicates the stage of minimization

//Here are how a Minuit program runs:
//Your main program has to initialize the TMinuit class and provide your core fcn function.
//Parameters have to be defined, either floated or fixed. 
//Send the corresponding commands to Minuit, which will call your fcn function to obtain the function values.


void fcn(int &npar, double *gin, double &f, double *par, int iflag)
{
 double x = par[0], y = par[1];
 f = pow(x-2.,2)+pow(y-3.,2);
}

void example_01()
{
 TMinuit *gMinuit = new TMinuit(2);
 gMinuit->SetFCN(fcn);
 gMinuit->DefineParameter(0, "x", 18. , 1., 0., 0.);
 gMinuit->DefineParameter(1, "y", 20. , 1., 0., 0.);
 gMinuit->Command("MIGRAD");
 gMinuit->Command("MIGRAD");
 double x,y,xerr,yerr;
 gMinuit->GetParameter(0,x,xerr);
 gMinuit->GetParameter(1,y,yerr);
 printf("x: %+.7f +- %.7f\n",x,xerr);
 printf("y: %+.7f +- %.7f\n",y,yerr);
}
