# tabulatedProperties

By Luka Denies
Delft University of Technology (MSc student)

OpenFOAM addition to use tabulated properties for thermophysical properties
Implemented:
- equationOfState (rho, psi, Z, cpMcv)
- thermo (cp, ha, hs)
- transport (mu, kappa, alphah)

Requires a table in pressure and temperature for:
- density (rho)
- specific heat (cp)
- specific heat difference (cpMcv)
- enthalpy (h)
- viscosity (mu)
- thermal conductivity (kappa)
These should be located in the constant directory

Two tutorial cases are located in the run directory:
- "pizzarelli" shows a numerical validation 
    (described in Sec. 5.1 of the MSc thesis by Luka Denies)
- "MTP_TC24" shows an experimental validation 
    (described in Sec. 5.3 of the MSc thesis by Luka Denies)

