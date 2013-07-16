#!/usr/bin/python
from numpy import *
from scipy import interpolate
from pylab import plot, loglog, semilogx, semilogy, clf, imshow
import pylab as plt
from matplotlib.pyplot import gca

def _f(a,b):
    if   a[0]<b[0] : return -1
    elif a[0]>b[0] : return 1
    else           : return _f(a[1:], b[1:])

def datafile(path):
    lines=[]
    if isinstance(path, str): f=open(path)
    else: f=path
    for line in f: 
        l=line.strip()
        if len(l) > 0 and l[0] in '1234567890.-+': lines.append([float(x) for x in l.split()])
    f.close()
    return array(lines)

def __main__():
    g1=g2=g3=g4=g5=0
    path=raw_input("enter path: ")

    try :dat=datafile (path)
    except IOError: 
        print "IOERROR"
        dat=datafile(raw_input("enter path: "))

    sdat=empty((dat.shape[0],dat.shape[1]-2))
    sdat[:,1:]=dat[:,3:]
    sdat[:,0]=sqrt((dat[:,:3]**2).sum(1))

    sdat=array(sorted(list(sdat), cmp=_f))

    r,z = sqrt((dat[:,:2]**2).sum(1)), dat[:,2]
    H, xedges, yedges = histogram2d(r, z, bins=(20, 100))
    clf();plt.imshow(log10(H.T+0.1), vmin=0, interpolation='nearest',origin='image', cmap=plt.cm.gist_heat)
    plt.colorbar()
    plt.draw()
    plt.savefig('grid.png')
