 /*
 *  model.c
 *  LIME, The versatile 3D line modeling tool 
 *
 *  Created by Christian Brinch on 11/05/07.
 *  Copyright 2006-2011, Christian Brinch, 
 *  <brinch@nbi.dk>
 *  Niels Bohr institutet
 *  University of Copenhagen
 *	All rights reserved.
 *
 */

#include "lime.h"
#include <stdio.h>
#include "rho.h"
#include "temp.h"
#include "vz.h"
#include "vr.h"
/* #include "fH2.h" */
/* #include "fHII.h" */
/* #include "fHI.h" */

#define length_scale (16.71146539*AU)
#define centre_z (800)
#define unit_temp (1)
#define unit_density (1e6)
#define unit_velocity (1e3)
#define arr_size_R (200)
#define arr_size_Z (1000)


/******************************************************************************/

void
input(inputPars *par, image *img){
/*
 * Basic parameters. See cheat sheet for details.
 */
  par->radius		= 200*length_scale;
  par->minScale	   	= 0.25*length_scale;
  par->pIntensity    	= 30000;
  par->sinkPoints    	= 8000;
  //par->pregrid          = "populations.pop";
  //par->dust		= "jena_thin_e6.tab";
  par->moldatfile[0] 	= "sio.dat";
  par->outputfile 	= "populations.pop";
  par->gridfile		= "grid.vtk";
  par->sampling         = 4;
  
/* 
 * Definitions for image #0. Add blocks for additional images.
 */

  img[0].nchan =80;
  //  img[0].freq                   = 43.587806e9*(1+3.3e5/CLIGHT*cos(PI/2))+4.587806e8/6/3;
  //  img[0].bandwidth              = 4.587806e8/3.0; // 30km/s across whole bandwidth
  img[0].trans = 0;
  img[0].velres= 500;
  img[0].pxls			= 256;	      // Pixels per dimension
  img[0].imgres			= 2.5;		  // Resolution in arc seconds
  img[0].theta			= PI/2;		  // 0: face-on, pi/2: edge-on
  img[0].distance		= length_scale/AU*PC;	  //1" == 1 length scale
  img[0].source_vel		= 0;          // source velocity in m/s
  img[0].unit			= 0;		  // 0:Kelvin 1:Jansky/pixel 2:SI 3:Lsun/pixel 4:tau
  img[0].filename		= "image_J1-0_90deg_molcool.fits";	// Output filename

  img[1].nchan =80;
  //  img[0].freq                   = 43.587806e9*(1+3.3e5/CLIGHT*cos(PI/2))+4.587806e8/6/3;
  //  img[0].bandwidth              = 4.587806e8/3.0; // 30km/s across whole bandwidth
  img[1].trans = 1;
  img[1].velres= 500;
  img[1].pxls			= 256;	      // Pixels per dimension
  img[1].imgres			= 2.5;		  // Resolution in arc seconds
  img[1].theta			= PI/2;		  // 0: face-on, pi/2: edge-on
  img[1].distance		= length_scale/AU*PC;	  //1" == 1 length scale
  img[1].source_vel		= 0;          // source velocity in m/s
  img[1].unit			= 0;		  // 0:Kelvin 1:Jansky/pixel 2:SI 3:Lsun/pixel 4:tau
   img[1].filename		= "image_J2-1_90deg_molcool.fits";	// Output filename

  img[2].nchan =80;
  //  img[0].freq                   = 43.587806e9*(1+3.3e5/CLIGHT*cos(PI/2))+4.587806e8/6/3;
  //  img[0].bandwidth              = 4.587806e8/3.0; // 30km/s across whole bandwidth
  img[2].trans = 2;
  img[2].velres= 500;
  img[2].pxls			= 256;	      // Pixels per dimension
  img[2].imgres			= 2.5;		  // Resolution in arc seconds
  img[2].theta			= PI/2;		  // 0: face-on, pi/2: edge-on
  img[2].distance		= length_scale/AU*PC;	  //1" == 1 length scale
  img[2].source_vel		= 0;          // source velocity in m/s
  img[2].unit			= 0;		  // 0:Kelvin 1:Jansky/pixel 2:SI 3:Lsun/pixel 4:tau
  img[2].filename		= "image_J3-2_90deg_molcool.fits";	// Output filename

  img[3].nchan =80;
  //  img[0].freq                   = 43.587806e9*(1+3.3e5/CLIGHT*cos(PI/2))+4.587806e8/6/3;
  //  img[0].bandwidth              = 4.587806e8/3.0; // 30km/s across whole bandwidth
  img[3].trans = 4;
  img[3].velres= 500;
  img[3].pxls			= 256;	      // Pixels per dimension
  img[3].imgres			= 2.5;		  // Resolution in arc seconds
  img[3].theta			= PI/2;		  // 0: face-on, pi/2: edge-on
  img[3].distance		= length_scale/AU*PC;	  //1" == 1 length scale
  img[3].source_vel		= 0;          // source velocity in m/s
  img[3].unit			= 0;		  // 0:Kelvin 1:Jansky/pixel 2:SI 3:Lsun/pixel 4:tau
  img[3].filename		= "image_J5-4_90deg_molcool.fits";	// Output filename

  img[4].nchan =80;
  //  img[0].freq                   = 43.587806e9*(1+3.3e5/CLIGHT*cos(PI/2))+4.587806e8/6/3;
  //  img[0].bandwidth              = 4.587806e8/3.0; // 30km/s across whole bandwidth
  img[4].trans = 7;
  img[4].velres= 500;
  img[4].pxls			= 256;	      // Pixels per dimension
  img[4].imgres			= 2.5;		  // Resolution in arc seconds
  img[4].theta			= PI/2;		  // 0: face-on, pi/2: edge-on
  img[4].distance		= length_scale/AU*PC;	  //1" == 1 length scale
  img[4].source_vel		= 0;          // source velocity in m/s
  img[4].unit			= 0;		  // 0:Kelvin 1:Jansky/pixel 2:SI 3:Lsun/pixel 4:tau
  img[4].filename		= "image_J8-7_90deg_molcool.fits";	// Output filename

  img[5].nchan =80;
  //  img[0].freq                   = 43.587806e9*(1+3.3e5/CLIGHT*cos(PI/2))+4.587806e8/6/3;
  //  img[0].bandwidth              = 4.587806e8/3.0; // 30km/s across whole bandwidth
  img[5].trans = 4;
  img[5].velres= 500;
  img[5].pxls			= 256;	      // Pixels per dimension
  img[5].imgres			= 2.5;		  // Resolution in arc seconds
  img[5].theta			= PI/3;		  // 0: face-on, pi/2: edge-on
  img[5].distance		= length_scale/AU*PC;	  //1" == 1 length scale
  img[5].source_vel		= 0;          // source velocity in m/s
  img[5].unit			= 0;		  // 0:Kelvin 1:Jansky/pixel 2:SI 3:Lsun/pixel 4:tau
  img[5].filename		= "image_J5-4_60deg_molcool.fits";	// Output filename
}
/******************************************************************************/

void
density(double x, double y, double z, double *density){	
  int R,Z;
  double r=sqrt(x*x+y*y);
  R=r/length_scale+0.51; 
  Z=z/length_scale+centre_z+0.51;

  if (R>arr_size_R-1) R=arr_size_R-1;
  else if (R<0) R=0;
  if (Z>arr_size_Z-1) Z=arr_size_Z-1; //boundary checking
  else if (Z<0) Z=0;

  if ((R>199) || (Z>999) || (R<0) || (Z<0)) {density[0]=rho[199][999]*unit_density;}
  else {density[0]=rho[R][Z]*unit_density;}//*(1-fHII[R][Z]);}
  if (Z<0 && R<199) {
    Z=0;
    density[0]=rho[R][Z]*unit_density;//*(1-fHII[R][Z]);
  }
  //  fprintf(stderr, "%.3e %.3e %d %d %.3e \n",r,z,R,Z, rho[R][Z]);
  
}

/******************************************************************************/

void
temperature(double x, double y, double z, double *temperature){
  int R,Z;
  double r=sqrt(x*x+y*y);
  R=r/length_scale+0.51; 
  Z=z/length_scale+centre_z+0.51;

  if (R>arr_size_R-1) R=arr_size_R-1;
  else if (R<0) R=0;
  if (Z>arr_size_Z-1) Z=arr_size_Z-1; //boundary checking
  else if (Z<0) Z=0;

  

  //  if (R>199) R=199;
  //  else if (R<0) R=0;
  //  if (Z>999) Z=999; //boundary checking
  //  else if (Z<0) Z=0;
  if ((R>199) || (Z>999) || (R<0) || (Z<0)) temperature[0]=temp[199][999]*unit_temp;  
  else temperature[0]=temp[R][Z]*unit_temp;  

  if (Z<0 && R<199) {
    Z=0;
    temperature[0]=temp[R][Z]*unit_temp;   
  }
  if (temperature[0]<50) temperature[0]=50;


}

/******************************************************************************/

void
abundance(double x, double y, double z, double *abundance){
  double v[3], vtot, power=0;
  int i;

  double polyconsts[6] ={ -2.48365385e-08,   5.50142698e-06,  -4.28047577e-04,   1.23768864e-02,   2.51957730e-02,  -1.20187732e+01};

  double r=sqrt(x*x+y*y);
  int R=r/length_scale+0.51; 
  int Z=z/length_scale+centre_z+0.51;

  if (R>arr_size_R-1) R=arr_size_R-1;
  else if (R<0) R=0;
  if (Z>arr_size_Z-1) Z=arr_size_Z-1; //boundary checking
  else if (Z<0) Z=0;

  velocity(x,y,z,v);
  vtot=sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);

  if(vtot>100000){abundance[0]=1e-30;}
  else { 
    vtot/=1000;
    for(i=0;i<6;i++){
      power+=polyconsts[i]*pow(vtot, 5-i);
    }
    abundance[0]=pow(10,power);//*(1-fHII[R][Z]);
  }
  temperature(x,y,z,&vtot);
  if (vtot>92000) {abundance[0]=1e-30;}
}

/******************************************************************************/

void
doppler(double x, double y, double z, double *doppler){
  *doppler = 80.;
}

/******************************************************************************/

void
velocity(double x, double y, double z, double *vel){
  int R,Z;
  double r,phi;
  r=sqrt(x*x+y*y);
  phi=atan2(y,x);
  /*
   * Transform Cartesian coordinates into cylindrical coordinates
   */

  R=r/length_scale+0.51; 
  Z=z/length_scale+centre_z+0.51;

  if (R>arr_size_R-1) R=arr_size_R-1;
  else if (R<0) R=0;
  if (Z>arr_size_Z-1) Z=arr_size_Z-1; //boundary checking
  else if (Z<0) Z=0;

  double Vr=vr[R][Z];

  /*
   * Vector transformation back into Cartesian basis
   */
  vel[0]=Vr*cos(phi)*unit_velocity;
  vel[1]=Vr*sin(phi)*unit_velocity;
  vel[2]=vz[R][Z]*unit_velocity;
}

/******************************************************************************/


