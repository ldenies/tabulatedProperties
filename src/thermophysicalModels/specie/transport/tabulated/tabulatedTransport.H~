/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2013 OpenFOAM Foundation
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

Class
    Foam::tabulatedTransport

Description
    Constant properties Transport package.
    Templated into a given thermodynamics package (needed for thermal
    conductivity).

SourceFiles
    tabulatedTransportI.H
    tabulatedTransport.C

\*---------------------------------------------------------------------------*/

#ifndef tabulatedTransport_H
#define tabulatedTransport_H

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
#include "interpolation2DTable.H"
namespace Foam
{

// Forward declaration of friend functions and operators

template<class Thermo> class tabulatedTransport;

template<class Thermo>
Ostream& operator<<
(
    Ostream&,
    const tabulatedTransport<Thermo>&
);


/*---------------------------------------------------------------------------*\
                           Class tabulatedTransport Declaration
\*---------------------------------------------------------------------------*/

template<class Thermo>
class tabulatedTransport
:
    public Thermo
{
    // Private data

        //- Constant dynamic viscosity [Pa.s]
        interpolation2DTable<scalar> muTable_;

        //- Reciprocal Prandtl Number []
        interpolation2DTable<scalar> kappaTable_;


    // Private Member Functions

        //- Construct from components
        inline tabulatedTransport
        (
            const Thermo& t,
            const scalar mu,
            const scalar Pr
        );


public:

    // Constructors

        //- Construct as named copy
        inline tabulatedTransport(const word&, const tabulatedTransport&);

        //- Construct from Istream
        tabulatedTransport(Istream&);

        //- Construct from dictionary
        tabulatedTransport(const dictionary& dict);

        //- Construct and return a clone
        inline autoPtr<tabulatedTransport> clone() const;

        // Selector from Istream
        inline static autoPtr<tabulatedTransport> New(Istream& is);

        // Selector from dictionary
        inline static autoPtr<tabulatedTransport> New(const dictionary& dict);


    // Member functions

        //- Return the instantiated type name
        static word typeName()
        {
            return "tabulated<" + Thermo::typeName() + '>';
        }

        //- Dynamic viscosity [kg/ms]
        inline scalar mu(const scalar p, const scalar T) const;

        //- Thermal conductivity [W/mK]
        inline scalar kappa(const scalar p, const scalar T) const;

        //- Thermal diffusivity of enthalpy [kg/ms]
        inline scalar alphah(const scalar p, const scalar T) const;

        // Species diffusivity
        //inline scalar D(const scalar p, const scalar T) const;

        //- Write to Ostream
        void write(Ostream& os) const;


    // Ostream Operator

        friend Ostream& operator<< <Thermo>
        (
            Ostream&,
            const tabulatedTransport&
        );
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "tabulatedTransportI.H"

#ifdef NoRepository
#   include "tabulatedTransport.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
