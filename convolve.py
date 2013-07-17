import numpy,pyfits,os,tarfile,Gnuplot,pprocess
from math import exp,log,sqrt,pi,ceil
from numpy.fft import fft2,ifft2, irfft2, rfft2
from scipy import constants as cnst
from scipy.interpolate import griddata
import numpy as np
import pprocess as pp
from pylab import imshow
import pylab as pyl
from numpy import outer
import pyfits as P

def garray(shape, sigma):
    a=numpy.empty(shape, dtype=float)
    midi,midj=shape[0]/2,shape[1]/2
    for i in xrange(shape[0]):
        for j in xrange(shape[1]):
            a[i,j]=exp(-1*sqrt((i-midi)**2+(j-midj)**2)**2 / (2*sigma*sigma))/(sigma*sqrt(2*pi))**2
#exp(-1*(i-midi)**2 / (2*sigma*sigma))*exp(-1*(j-midj)**2 / (2*sigma*sigma))/(sqrt(2*pi*sigma**2))    
    return a

def FWHM2sigma (FWHM): return FWHM/(2*sqrt(2*log(2)))

def next_pow2 (n):
    if n<0: sign=-1
    else  : sign=1
    X=abs(n)
    ans=1
    while ans<X: ans*=2
    return ans

def cube_convolve(imcube, sigma):
    "performs a convolution with a gaussian beam of width sigma on each yz plane of the cube"
#    imcube=imcube.copy()
    shape=imcube.shape[1:]
    if len(shape)!=2:
        raise ValueError ("cube is not a cube")
    gauss_mask=garray(shape,sigma)
    s=[next_pow2(y*2+1) for y in gauss_mask.shape]
    ftg=fft2(gauss_mask, s).reshape(s)
    for i in xrange(imcube.shape[0]):
        imcube[i,...]=np.real(ifft2(fft2(imcube[i,...],s)*ftg)[shape[0]/2:3*shape[0]/2, shape[1]/2:3*shape[1]/2])
    return imcube
 
