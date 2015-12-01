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

#include "roughWallSAFvPatchScalarField.H"
#include "roughSpalartAllmaras.H"
#include "compressible/turbulenceModel/turbulenceModel.H"
#include "fvPatchFieldMapper.H"
#include "addToRunTimeSelectionTable.H"
#include "wallDist.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace compressible
{

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

roughWallSAFvPatchScalarField::
roughWallSAFvPatchScalarField
(
    const fvPatch& p,
    const DimensionedField<scalar, volMesh>& iF
)
:
    fixedValueFvPatchScalarField(p, iF),
    roughnessHeight_(10e-6)
{}


roughWallSAFvPatchScalarField::
roughWallSAFvPatchScalarField
(
    const roughWallSAFvPatchScalarField& ptf,
    const fvPatch& p,
    const DimensionedField<scalar, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
:
    fixedValueFvPatchScalarField(ptf, p, iF, mapper),
    roughnessHeight_(ptf.roughnessHeight_)
{}


roughWallSAFvPatchScalarField::
roughWallSAFvPatchScalarField
(
    const fvPatch& p,
    const DimensionedField<scalar, volMesh>& iF,
    const dictionary& dict
)
:
    fixedValueFvPatchScalarField(p, iF, dict),
    roughnessHeight_(dict.lookupOrDefault<scalar>("roughnessHeight", 10e-6))
{}


roughWallSAFvPatchScalarField::
roughWallSAFvPatchScalarField
(
    const roughWallSAFvPatchScalarField& nuGrad
)
:
    fixedValueFvPatchScalarField(nuGrad),
    roughnessHeight_(nuGrad.roughnessHeight_)
{}


roughWallSAFvPatchScalarField::
roughWallSAFvPatchScalarField
(
    const roughWallSAFvPatchScalarField& nuGrad,
    const DimensionedField<scalar, volMesh>& iF
)
:
    fixedValueFvPatchScalarField(nuGrad, iF),
    roughnessHeight_(nuGrad.roughnessHeight_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void roughWallSAFvPatchScalarField::updateCoeffs()
{
    if (updated())
    {
        return;
    }

    const turbulenceModel& turbulence =
        db().lookupObject<turbulenceModel>("turbulenceModel");

    const label patchI = patch().index();
    const scalarField d = turbulence.y()[patchI] + 0.03*roughnessHeight_;
    
    const scalarField internalValue = this->patchInternalField();
     
    operator==(internalValue*0.03*roughnessHeight_/d);

    fixedValueFvPatchScalarField::updateCoeffs();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void roughWallSAFvPatchScalarField::write(Ostream& os) const
{
    fvPatchField<scalar>::write(os);
    os.writeKeyword("roughnessHeight") << roughnessHeight_ << token::END_STATEMENT << nl;    
    writeEntry("value", os);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

makePatchTypeField
(
    fvPatchScalarField,
    roughWallSAFvPatchScalarField
);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace compressible
} // End namespace Foam

// ************************************************************************* //
