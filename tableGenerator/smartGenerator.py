# -*- coding: utf-8 -*-
"""
Created on Thu Jun  4 14:41:38 2015

@author: luka
"""

# -*- coding: utf-8 -*-
"""
Created on Fri May  8 10:12:23 2015

@author: luka
"""

from thermoClass import thermo
import numpy as np
import matplotlib.pyplot as plt

meth = thermo()

drho = 0.25

T0 = 100
TMax = 1500

p0 = 120e5
pMax = 160e5

Ts = []
ps = []
pRange = []

rho = []
mu = []
kappa = []
cp = []
h = []
cpMcv = []

M = meth.M

rhoCur = 453
i = 0
j = 0

p = p0
T = T0
while p<pMax:
    pRange.append(p)
    TRange = []
    T = T0
    rho.append([0])
    cp.append([0])
    mu.append([0])
    kappa.append([0])
    cpMcv.append([0])
    h.append([0])    
    rho[i][0] = rhoCur = meth.eqState(p,T)
    cpCur = meth.cp(rhoCur,T)
    cp[i][0] = cpCur
    mu[i][0] = meth.viscosity(rhoCur,T)
    kappa[i][0] = meth.conductivity(rhoCur,T)
    cpMcv[i][0] = cpCur-meth.cv(rhoCur,T)
    h[i][0] = meth.h(rhoCur,T)
    TRange.append(T)
    while T<TMax:
        j += 1
        dT = drho/(meth.drhodp(rhoCur,T)*meth.dpdt(rhoCur,T))
        T += dT
        rhoCur = meth.eqState(p,T)
        rho[i].append(rhoCur)
        cpCur = meth.cp(rhoCur,T)
        cp[i].append(cpCur)
        mu[i].append(meth.viscosity(rhoCur,T))
        kappa[i].append(meth.conductivity(rhoCur,T))
        cpMcv[i].append((cpCur-meth.cv(rhoCur,T))*meth.M)
        h[i].append(meth.h(rhoCur,T))
        TRange.append(T)
    i += 1
    ps.append([p]*len(TRange))    
    rhoPseudoCrit = meth.eqState(p,meth.Tcrit)
    dp = drho/meth.drhodp(rhoPseudoCrit,meth.Tcrit)
    p += dp
    print p
    Ts.append(TRange)
print "Calculations done, now writing"

muFile = open("mu","w")
muFile.write("( \n")

for i,p in enumerate(pRange):
    muFile.write("(" + str(p) + "\n(\n")
    sList = ["\t(" + str(Ts[i][j]) + " " + str(mu[i][j]) + ")\n" for j in range(len(Ts[i]))]
    muFile.write(" ".join(sList))
    muFile.write(") ) \n")    
muFile.write(");")
muFile.close()

rhoFile = open("rho","w")
rhoFile.write("( \n")

for i,p in enumerate(pRange):
    rhoFile.write("(" + str(p) + "\n(\n")
    sList = ["\t(" + str(Ts[i][j]) + " " + str(rho[i][j]) + ")\n" for j in range(len(Ts[i]))]
    rhoFile.write(" ".join(sList))
    rhoFile.write(") ) \n")    
rhoFile.write(");")
rhoFile.close()

cpFile = open("cp","w")
cpFile.write("( \n")

for i,p in enumerate(pRange):
    cpFile.write("(" + str(p) + "\n(\n")
    sList = ["\t(" + str(Ts[i][j]) + " " + str(cp[i][j]) + ")\n" for j in range(len(Ts[i]))]
    cpFile.write(" ".join(sList))
    cpFile.write(") ) \n")    
cpFile.write(");")
cpFile.close()

kappaFile = open("kappa","w")
kappaFile.write("( \n")

for i,p in enumerate(pRange):
    kappaFile.write("(" + str(p) + "\n(\n")
    sList = ["\t(" + str(Ts[i][j]) + " " + str(kappa[i][j]) + ")\n" for j in range(len(Ts[i]))]
    kappaFile.write(" ".join(sList))
    kappaFile.write(") ) \n")    
kappaFile.write(");")
kappaFile.close()

cpMcvFile = open("cpMcv","w")
cpMcvFile.write("( \n")

for i,p in enumerate(pRange):
    cpMcvFile.write("(" + str(p) + "\n(\n")
    sList = ["\t(" + str(Ts[i][j]) + " " + str(cpMcv[i][j]) + ")\n" for j in range(len(Ts[i]))]
    cpMcvFile.write(" ".join(sList))
    cpMcvFile.write(") ) \n")    
cpMcvFile.write(");")
cpMcvFile.close()

hFile = open("h","w")
hFile.write("( \n")

for i,p in enumerate(pRange):
    hFile.write("(" + str(p) + "\n(\n")
    sList = ["\t(" + str(Ts[i][j]) + " " + str(h[i][j]) + ")\n" for j in range(len(Ts[i]))]
    hFile.write(" ".join(sList))
    hFile.write(") ) \n")    
hFile.write(");")
hFile.close()