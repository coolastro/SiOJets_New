from numpy import *
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import pyfits as pf
import os
import matplotlib.gridspec as gridspec
import sys
import nice_plots as nplt
nplt.nice_plots(fs=15)

def RA2ICRS(arr):
    arr1 = []
    for i in arr:
        RAdeg = (i/360.0)*24.0 
        RAh = int(floor(RAdeg))
        RAm = (RAdeg-RAh)*60.0
        RAm2 = int(floor(RAm))
        RAs = (RAm-RAm2)*60.0
        arr1.append(str(RAh)+'h'+str(RAm2)+'m'+str('%.1f'%RAs)+'s')
    return arr1

def DEC2ICRS(arr):
    arr1 = []
    for i in arr:
        DECdeg = int(floor(i))
        DECm = (i - DECdeg)*60.0
        DECm2 = int(floor(DECm))
        DECs = (DECm-DECm2)*60.0
        arr1.append(str(DECdeg)+'$^\circ$'+str(DECm2)+"'"+str('%.1f'%DECs)+"''")
    return arr1

def Velarr(ang,V0, A):
    arr1 = [i - 120.0 for i in range(A['NAXIS3'])]
    return arr1

def fig11():
    hdulist1 = pf.open('/home/pytd/documents/SiOJets_New/imagedless1Shock_J2-1_45deg_molcool_dirty.fits')
    hdulist2 = pf.open('/home/pytd/documents/SiOJets_New/imagedless1Shock_J8-7_45deg_molcool_dirty.fits')
    hdulist3 = pf.open('/home/pytd/documents/SiOJets_New/imagedless1Shock_J5-4_45deg_molcool_dirty.fits')
    
    
    A = hdulist1[0].header

    RAarr = [A['CRVAL1'] - i*A['CDELT1'] for i in range(A['NAXIS1']/2)] + [A['CRVAL1'] + i*A['CDELT1'] for i in range(A['NAXIS1']/2,A['NAXIS1'])]
    DECarr = [A['CRVAL2'] - i*A['CDELT2'] for i in range(A['NAXIS2']/2)] + [A['CRVAL2'] + i*A['CDELT2'] for i in range(A['NAXIS2']/2,A['NAXIS2'])]
    RAarr2 = RA2ICRS(RAarr)
    DECarr2 = DEC2ICRS(DECarr)
    VELarr2 = Velarr(pi/4.,100.0, A)
    print VELarr2[0]

    clevs1 = [0.01,0.03, 0.05]
    clevs2 = [0.01, 0.1, 0.2, 0.4,0.8,1.2] 
    # Get ALMA images
    f1 = plt.figure(figsize=[11,8])
    plt.subplots_adjust(wspace=0.05)
    ax1 = f1.add_subplot(121)
    
    im1 = imshow(hdulist2[0].data[:,:,:].sum(0),origin='image',vmin = 0.001, vmax = 0.35,cmap=cm.gist_heat)
    plt.colorbar(im1,ticks=clevs2)
    im2 = contour(hdulist3[0].data[:,:,:].sum(0),levels=clevs2,colors='b',linewidths=1.0)
    im3 = contour(hdulist1[0].data[:,:,:].sum(0),levels=clevs2,colors='g',linewidths=1.0)
    
    axis([100.0,250.0,0.0,320.0])
    ax1.xaxis.set_major_locator(MaxNLocator(4))
    ax1.yaxis.set_major_locator(MaxNLocator(4))
    locs,labels = plt.xticks()
    plt.xticks(locs,[RAarr2[int(i)] for i in locs],rotation=15)
    locs,labels = plt.yticks()
    plt.yticks(locs[1:-1],[DECarr2[int(i)] for i in locs[1:-1]],rotation=90)
    ax1.set_ylabel('Declination [J2000]')
    ax1.set_xlabel('Right Ascention [J2000]')
    plt.figtext(0.16,0.2,r'Image [Jy/beam] : 5-$>$4',color='r')
    plt.figtext(0.16,0.175,r'Green Contour : 2-$>$1',color='g')
    plt.figtext(0.16,0.15,r'Blue Contour : 8-$>$7',color='b')
    
    ax2 = f1.add_subplot(122)
    
    im1b = imshow(hdulist2[0].data[:,:,175].T,origin='image',vmin = 0.001, vmax = 0.05,cmap=cm.gist_heat)
    plt.colorbar(im1b,ticks=clevs1)
    im2b = contour(hdulist3[0].data[:,:,175].T,levels=clevs1,colors='b',linewidths=1.0)
    im3b = contour(hdulist1[0].data[:,:,175].T,levels=clevs1,colors='g',linewidths=1.0)
    
    axis([0.0,150.0,0.0,320.0])
    ax2.xaxis.set_major_locator(MaxNLocator(4))
    #ax2.yaxis.set_major_locator(MaxNLocator(4))
    locs,labels = plt.xticks()
    plt.xticks(locs,[str('%.1f'%VELarr2[int(i)]) for i in locs])
    plt.setp(ax2,yticks=[])
    ax2.set_xlabel(r'Velocity [km s$^{-1}$]')
    
    plt.figtext(0.53,0.2,r'PV Diagram [Jy/beam] : 5-$>$4',color='r')
    plt.figtext(0.53,0.175,r'Green Contour : 2-$>$1',color='g')
    plt.figtext(0.53,0.15,r'Blue Contour : 8-$>$7',color='b')
    
    plt.show()

if __name__=="__main__":
    fig11()
