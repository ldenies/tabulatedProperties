/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2012 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "tabulated.H"

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Specie>
inline Foam::tabulated<Specie>::tabulated(const Specie& sp)
:
    Specie(sp)
{}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Specie>
inline Foam::tabulated<Specie>::tabulated
(
    const word& name,
    const tabulated<Specie>& pg
)
:
    Specie(name, pg)
{}


template<class Specie>
inline Foam::autoPtr<Foam::tabulated<Specie> >
Foam::tabulated<Specie>::clone() const
{
    return autoPtr<tabulated<Specie> >(new tabulated<Specie>(*this));
}


template<class Specie>
inline Foam::autoPtr<Foam::tabulated<Specie> >
Foam::tabulated<Specie>::New(Istream& is)
{
    return autoPtr<tabulated<Specie> >(new tabulated<Specie>(is));
}


template<class Specie>
inline Foam::autoPtr<Foam::tabulated<Specie> > Foam::tabulated<Specie>::New
(
    const dictionary& dict
)
{
    return autoPtr<tabulated<Specie> >(new tabulated<Specie>(dict));
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Specie>
inline Foam::scalar Foam::tabulated<Specie>::rho(scalar p, scalar T) const
{
    return rhoTable_(p,T, false);
}


template<class Specie>
inline Foam::scalar Foam::tabulated<Specie>::psi(scalar p, scalar T) const
{
    return rhoTable_(p,T, false)/p;
}


template<class Specie>
inline Foam::scalar Foam::tabulated<Specie>::Z(scalar p, scalar T) const
{
    return p/(rhoTable_(p,T, false)*this->R()*T);
}


template<class Specie>
inline Foam::scalar Foam::tabulated<Specie>::cpMcv(scalar p, scalar T) const
{
    return cpMcvTable_(p,T, false);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Specie>
inline void Foam::tabulated<Specie>::operator+=(const tabulated<Specie>& pg)
{
    Specie::operator+=(pg);
}


template<class Specie>
inline void Foam::tabulated<Specie>::operator-=(const tabulated<Specie>& pg)
{
    Specie::operator-=(pg);
}


template<class Specie>
inline void Foam::tabulated<Specie>::operator*=(const scalar s)
{
    Specie::operator*=(s);
}




// ************************************************************************* //
