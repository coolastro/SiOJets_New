/*
 *  weights.c
 *  LIME, The versatile 3D line modeling environment 
 *
 *  Created by Christian Brinch on 11/16/06.
 *  Copyright 2006-2012, Christian Brinch, 
 *  <brinch@nbi.dk>
 *  Niels Bohr institutet
 *  University of Copenhagen
 *	All rights reserved.
 *
 */

#include "lime.h"
/*
double
setup(inputPars  *par){
  double val[99],n0;
  density  (par->minScale*5,    0,         0, val);
  n0=val[0];
  density  (par->minScale*10,    0,         0, val);
  if (n0<val[0]) n0=val[0];
  density  (par->minScale*20,    0,         0, val);
  if (n0<val[0]) n0=val[0];
  density  (par->minScale*30,    0,         0, val);
  if (n0<val[0]) n0=val[0];
  density  (par->minScale*40,    0,         0, val);
  if (n0<val[0]) n0=val[0];
  density  (par->minScale*50,    0,         0, val);
  if (n0<val[0]) n0=val[0];
  return n0;
  }*/

int
pointEvaluation(inputPars *par,double ran, double x, double y, double z){
  double weight1=0, weight2=0, val[99],m0,n0,val2[99], eta=10;
//  double t0=200000;

//////// compare with ambient medium /////////  
  density  (par->radius*sqrt(0.25), par->radius*sqrt(0.25), par->radius*sqrt(0.25), val);
  n0=val[0]*eta*0.8;
  m0=1.0e-6;
    

/////////// compare with central region in z=0 plane ////////
    /* density  (par->minScale*5,    0,          0, val);  //disc w/ hole */
    /* n0=val[0]; */
    /* density  (0,             par->minScale*5, 0, val);  //disc w/ hole */
    /* n0+=val[0]; */
    /* n0/=2; */
    /* //    n0=5.0e12; */

    /* abundance(      0,      par->minScale*5, 0, val2); */
    /* m0=val2[0]; */
    /* abundance(par->minScale*5,       0,      0, val2); */
    /* m0+=val2[0]; m0/=2; */
    /* m0*=n0; */


//    density(par->minScale,par->minScale,par->minScale, val); //spherical
//    n0=val[0];
  
//    density(x,y,z,val);
//    abundance(x,y,z,val2);
//    weight1=pow(val[0]*val2[0]/n0,0.3);
  
  
//    temperature(x,y,z,val2);
 
  
//  density  (0, 0, par->minScale*5*400, val);  //bowshock for jet models
//  n0=val[0];
//  d0=1e-6;

//  density(x,y,z,val);
//  weight1=pow(val[0]/n0, 0.3);
//  abundance(x,y,z, val2);
//  weight2=pow(val[0]*val2[0]/n0/d0, 0.5);
 


  //  density(par->minScale,par->minScale,par->minScale,val);
  //abundance(par->minScale,par->minScale,par->minScale,val2);
  //  n0=val[0];
  //  density(x,y,z,val);
  //  weight1=pow(val[0]/n0,0.5);

  //  abundance(x,y,z,val2);
  //  weight2=sqrt(val2[0]*val[0]/d0)*0.5;

    density  (x,y,z, val);
    abundance(x,y,z, val2);   
    weight1=pow(val[0]/n0,0.3);
    weight2=pow(val2[0]*val[0]/m0, 0.3);


  if (verbose ) fprintf(stderr, "weighting n0:%.2e n:%.2e x:%.2e minscale:%.2e r/minscale:%.2e (%.2eAU)\n", n0, val[0], val2[0], par->minScale, sqrt(x*x+y*y)/par->minScale, sqrt(x*x+y*y)/AU);
  if(ran < weight1 || ran < weight2) return 1;
  else return 0;
}
