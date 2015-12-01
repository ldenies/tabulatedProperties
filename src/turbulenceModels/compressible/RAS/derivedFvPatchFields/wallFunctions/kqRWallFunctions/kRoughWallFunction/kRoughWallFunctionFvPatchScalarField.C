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

#include "kRoughWallFunctionFvPatchScalarField.H"
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

kRoughWallFunctionFvPatchScalarField::
kRoughWallFunctionFvPatchScalarField
(
    const fvPatch& p,
    const DimensionedField<scalar, volMesh>& iF
)
:
    fixedValueFvPatchScalarField(p, iF),
    roughnessHeight_(0.0),
    betaStar_(0.09)
{}


kRoughWallFunctionFvPatchScalarField::
kRoughWallFunctionFvPatchScalarField
(
    const kRoughWallFunctionFvPatchScalarField& ptf,
    const fvPatch& p,
    const DimensionedField<scalar, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
:
    fixedValueFvPatchScalarField(ptf, p, iF, mapper),
    roughnessHeight_(ptf.roughnessHeight_),
    betaStar_(ptf.betaStar_)
{}


kRoughWallFunctionFvPatchScalarField::
kRoughWallFunctionFvPatchScalarField
(
    const fvPatch& p,
    const DimensionedField<scalar, volMesh>& iF,
    const dictionary& dict
)
:
    fixedValueFvPatchScalarField(p, iF, dict),
    roughnessHeight_(dict.lookupOrDefault<scalar>("roughnessHeight", 0.0)),
    betaStar_(dict.lookupOrDefault<scalar>("betaStar", 0.09))    
{}


kRoughWallFunctionFvPatchScalarField::
kRoughWallFunctionFvPatchScalarField
(
    const kRoughWallFunctionFvPatchScalarField& nuGrad
)
:
    fixedValueFvPatchScalarField(nuGrad),
    roughnessHeight_(nuGrad.roughnessHeight_),
    betaStar_(nuGrad.betaStar_)
    
{}


kRoughWallFunctionFvPatchScalarField::
kRoughWallFunctionFvPatchScalarField
(
    const kRoughWallFunctionFvPatchScalarField& nuGrad,
    const DimensionedField<scalar, volMesh>& iF
)
:
    fixedValueFvPatchScalarField(nuGrad, iF),
    roughnessHeight_(nuGrad.roughnessHeight_),
    betaStar_(nuGrad.betaStar_)    
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void kRoughWallFunctionFvPatchScalarField::updateCoeffs()
{
    if (updated())
    {
        return;
    }

    const turbulenceModel& turbulence =
        db().lookupObject<turbulenceModel>("turbulenceModel");

    const label patchI = patch().index();
    
    const scalarField& rhow = turbulence.rho().boundaryField()[patchI];

    const tmp<volScalarField> tmu = turbulence.mu();
    const scalarField& muw = tmu().boundaryField()[patchI];

    //const tmp<volScalarField> tmut = turbulence.mut();
    //const volScalarField& mut = tmut();
    
    //const scalarField& mutw = mut.boundaryField()[patchI];

    const fvPatchVectorField& Uw = turbulence.U().boundaryField()[patchI];

    const scalarField magGradUw(mag(Uw.snGrad()));

	const scalarField fricVel = sqrt( muw * magGradUw / rhow );
	const scalarField nu = muw/rhow;
	const scalarField ks = roughnessHeight_*fricVel/nu;
		                              
    const scalarField kPlus = 1.0/sqrt(betaStar_) * tanh((log(ks/30.0)/log(8.0) + 0.5*(1.0 - tanh(ks/100.0)))*tanh(ks/75.0));
    const scalarField k = max(0.0,kPlus*sqr(fricVel));

	Info<< "Average ks+: " << average(ks) << endl;

    operator==(k);

    fixedValueFvPatchScalarField::updateCoeffs();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void kRoughWallFunctionFvPatchScalarField::write(Ostream& os) const
{
    fvPatchField<scalar>::write(os);
    os.writeKeyword("roughnessHeight") << roughnessHeight_ << token::END_STATEMENT << nl;    
    os.writeKeyword("betaStar") << betaStar_ << token::END_STATEMENT << nl;    
    writeEntry("value", os);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

makePatchTypeField
(
    fvPatchScalarField,
    kRoughWallFunctionFvPatchScalarField
);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace compressible
} // End namespace Foam

// ************************************************************************* //
