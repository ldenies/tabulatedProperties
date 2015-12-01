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

#include "omegaRoughWallFunctionFvPatchScalarField.H"
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

omegaRoughWallFunctionFvPatchScalarField::
omegaRoughWallFunctionFvPatchScalarField
(
    const fvPatch& p,
    const DimensionedField<scalar, volMesh>& iF
)
:
    fixedValueFvPatchScalarField(p, iF),
    roughnessHeight_(0),
    betaStar_(0.09)
{}


omegaRoughWallFunctionFvPatchScalarField::
omegaRoughWallFunctionFvPatchScalarField
(
    const omegaRoughWallFunctionFvPatchScalarField& ptf,
    const fvPatch& p,
    const DimensionedField<scalar, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
:
    fixedValueFvPatchScalarField(ptf, p, iF, mapper),
    roughnessHeight_(ptf.roughnessHeight_),
    betaStar_(ptf.betaStar_)
{}


omegaRoughWallFunctionFvPatchScalarField::
omegaRoughWallFunctionFvPatchScalarField
(
    const fvPatch& p,
    const DimensionedField<scalar, volMesh>& iF,
    const dictionary& dict
)
:
    fixedValueFvPatchScalarField(p, iF, dict),
    roughnessHeight_(dict.lookupOrDefault<scalar>("roughnessHeight", 0)),
    betaStar_(dict.lookupOrDefault<scalar>("betaStar", 0.09))    
{}


omegaRoughWallFunctionFvPatchScalarField::
omegaRoughWallFunctionFvPatchScalarField
(
    const omegaRoughWallFunctionFvPatchScalarField& nuGrad
)
:
    fixedValueFvPatchScalarField(nuGrad),
    roughnessHeight_(nuGrad.roughnessHeight_),
    betaStar_(nuGrad.betaStar_)
    
{}


omegaRoughWallFunctionFvPatchScalarField::
omegaRoughWallFunctionFvPatchScalarField
(
    const omegaRoughWallFunctionFvPatchScalarField& nuGrad,
    const DimensionedField<scalar, volMesh>& iF
)
:
    fixedValueFvPatchScalarField(nuGrad, iF),
    roughnessHeight_(nuGrad.roughnessHeight_),
    betaStar_(nuGrad.betaStar_)    
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void omegaRoughWallFunctionFvPatchScalarField::updateCoeffs()
{
    if (updated())
    {
        return;
    }

    const turbulenceModel& turbulence =
        db().lookupObject<turbulenceModel>("turbulenceModel");

    const label patchI = patch().index();
    
    const scalarField d = turbulence.y()[patchI] + 0.03*roughnessHeight_;
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
		                              
    const scalarField omegaPlus = 400000.0/pow(ks,4.0) / (tanh(10000.0/(3.0*pow(ks,3.0)))) + 70/ks*(1-exp(-ks/300));
    const scalarField omega = omegaPlus*sqr(fricVel)/nu;
	 
    operator==(omega);

    fixedValueFvPatchScalarField::updateCoeffs();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void omegaRoughWallFunctionFvPatchScalarField::write(Ostream& os) const
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
    omegaRoughWallFunctionFvPatchScalarField
);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace compressible
} // End namespace Foam

// ************************************************************************* //
