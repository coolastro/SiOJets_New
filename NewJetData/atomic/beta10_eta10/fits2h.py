#!/opt/epd-7.2-2-rh5-x86_64/bin/python
import pyfits as P
import numpy as np

def writer (data, name, opath):
    S=np.array(data.shape)
    SS=np.array([S[i:].prod() for i in xrange(-S.size+1,0)])
    c=0
    of=open(opath,'w')
    print SS
    of.write('const static double '+name+''.join(tuple([str([x]) for x in data.shape]))+' = {')
    for x in data.flat:
        c+=1
        ns=c%SS
        for n in ns:
            if n==1: of.write('{')
        of.write("%.3e"%x)
        if (ns!=0).all()or c==0: of.write(', ')
        elif c!=0: 
            for (i,n) in enumerate(ns[::-1]):
                if n==0: 
                    of.write('}')
                    if i==ns.size-1: 
                        if c!=data.size: of.write(',\n')
                        else: of.write('\n')
                    else:
                        if ns[::-1][i+1]==0: 
                            of.write('\n')
                        else: of.write(',\n')
    of.write('};')

                                                       
if __name__ == '__main__':
 fitsf=raw_input("name of fits file to convert: ")
 while fitsf:
    data=P.getdata(fitsf)
    opath=raw_input("name of output header file: ")
    if not(opath): opath=fitsf.split('.')[0]+'.h'
    elif opath.split('.')[-1]!='h' : opath=opath+'.h'
    name=raw_input("name of array in header file: ")
    if not(name): name=opath.split('.')[0]
    writer(data, name, opath)
    fitsf=raw_input("name of fits file to convert: ")
