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

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class equationOfState>
inline Foam::tabulatedThermo<equationOfState>::tabulatedThermo
(
    const equationOfState& st,
    const interpolation2DTable<scalar> cpTable,
    const interpolation2DTable<scalar> hTable
)
:
    equationOfState(st),
    cpTable_(cpTable),
    hTable_(hTable)
{}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class equationOfState>
inline Foam::tabulatedThermo<equationOfState>::tabulatedThermo
(
    const word& name,
    const tabulatedThermo& ct
)
:
    equationOfState(name, ct),
    cpTable_(ct.cpTable_),
    hTable_(ct.hTable_)
{}


template<class equationOfState>
inline Foam::autoPtr<Foam::tabulatedThermo<equationOfState> >
Foam::tabulatedThermo<equationOfState>::clone() const
{
    return autoPtr<tabulatedThermo<equationOfState> >
    (
        new tabulatedThermo<equationOfState>(*this)
    );
}


template<class equationOfState>
inline Foam::autoPtr<Foam::tabulatedThermo<equationOfState> >
Foam::tabulatedThermo<equationOfState>::New(Istream& is)
{
    return autoPtr<tabulatedThermo<equationOfState> >
    (
        new tabulatedThermo<equationOfState>(is)
    );
}


template<class equationOfState>
inline Foam::autoPtr<Foam::tabulatedThermo<equationOfState> >
Foam::tabulatedThermo<equationOfState>::New(const dictionary& dict)
{
    return autoPtr<tabulatedThermo<equationOfState> >
    (
        new tabulatedThermo<equationOfState>(dict)
    );
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class EquationOfState>
inline Foam::scalar Foam::tabulatedThermo<EquationOfState>::limit
(
    const scalar T
) const
{
    return T;
}


template<class equationOfState>
inline Foam::scalar Foam::tabulatedThermo<equationOfState>::cp
(
    const scalar p,
    const scalar T
) const
{
    return cpTable_(p,T)*this->W();
}

template<class equationOfState>
inline Foam::scalar Foam::tabulatedThermo<equationOfState>::ha
(
    const scalar p, const scalar T
) const
{
    return hTable_(p,T)*this->W();
}


template<class equationOfState>
inline Foam::scalar Foam::tabulatedThermo<equationOfState>::hs
(
    const scalar p, const scalar T
) const
{
    return hTable_(p,T)*this->W();
}

template<class equationOfState>
inline Foam::scalar Foam::tabulatedThermo<equationOfState>::hc() const
{
    return 0;
}



template<class equationOfState>
inline Foam::scalar Foam::tabulatedThermo<equationOfState>::s
(
    const scalar p, const scalar T
) const
{
    notImplemented
    (
        "scalar tabulatedThermo<equationOfState>::"
        "s(const scalar p, const scalar T) const"
    );
    return T;
}



