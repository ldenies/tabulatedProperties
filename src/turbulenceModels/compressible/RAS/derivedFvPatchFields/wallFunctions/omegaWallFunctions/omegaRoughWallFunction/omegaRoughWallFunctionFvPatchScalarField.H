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

Class
    Foam::compressible::omegaRoughWallFunctionFvPatchScalarField

Group
    grpCmpWallFunctions

Description
    This boundary condition provides a wall function constraint on turbulence
    specific dissipation, omega.  The values are computed using:

    Model described by Eq.(25) of:
    \verbatim
        Aupoix, B., 2014,
        "Roughness Corrections for the k–ω Shear Stress Transport Model: Status and Proposals"
        Journal of Fluids Engineering 137:2, p. 021202
    \endverbatim

    \heading Patch usage

    \table
        Property     	| Description             | Required    | Default value
        betaStar     	| model coefficient       | no          | 0.09
		roughnessHeight	| equivalent sand grain	  | no			| 0
    \endtable

    Example of the boundary condition specification:
    \verbatim
    myPatch
    {
        type            compressible::omegaRoughWallFunction;
    }
    \endverbatim

SourceFiles
    omegaRoughWallFunctionFvPatchScalarField.C
\*---------------------------------------------------------------------------*/

#ifndef compressibleMutRoughWallFunctionFvPatchScalarField_H
#define compressibleMutRoughWallFunctionFvPatchScalarField_H

#include "fixedValueFvPatchFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace compressible
{

/*---------------------------------------------------------------------------*\
           Class omegaRoughWallFunctionFvPatchScalarField Declaration
\*---------------------------------------------------------------------------*/

class omegaRoughWallFunctionFvPatchScalarField
:
    public fixedValueFvPatchScalarField
{
protected:

    // Protected data
	
	//- Equivalent sand grain roughness
    scalar roughnessHeight_;
    
	//- Beta star coefficient
	scalar betaStar_;


public:

    //- Runtime type information
    TypeName("omegaRoughWallFunction");


    // Constructors

        //- Construct from patch and internal field
        omegaRoughWallFunctionFvPatchScalarField
        (
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&
        );

        //- Construct from patch, internal field and dictionary
        omegaRoughWallFunctionFvPatchScalarField
        (
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&,
            const dictionary&
        );

        //- Construct by mapping given
        //  omegaRoughWallFunctionFvPatchScalarField
        //  onto a new patch
        omegaRoughWallFunctionFvPatchScalarField
        (
            const omegaRoughWallFunctionFvPatchScalarField&,
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&,
            const fvPatchFieldMapper&
        );

        //- Construct as copy
        omegaRoughWallFunctionFvPatchScalarField
        (
            const omegaRoughWallFunctionFvPatchScalarField&
        );

        //- Construct and return a clone
        virtual tmp<fvPatchScalarField> clone() const
        {
            return tmp<fvPatchScalarField>
            (
                new omegaRoughWallFunctionFvPatchScalarField(*this)
            );
        }

        //- Construct as copy setting internal field reference
        omegaRoughWallFunctionFvPatchScalarField
        (
            const omegaRoughWallFunctionFvPatchScalarField&,
            const DimensionedField<scalar, volMesh>&
        );

        //- Construct and return a clone setting internal field reference
        virtual tmp<fvPatchScalarField> clone
        (
            const DimensionedField<scalar, volMesh>& iF
        ) const
        {
            return tmp<fvPatchScalarField>
            (
                new omegaRoughWallFunctionFvPatchScalarField(*this, iF)
            );
        }


    // Member functions

        // Evaluation functions

            //- Update the coefficients associated with the patch field
            virtual void updateCoeffs();


        // I-O

            //- Write
            virtual void write(Ostream&) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace compressible
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
