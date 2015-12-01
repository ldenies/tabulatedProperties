{
    rho = thermo.rho();
    rho = max(rho, rhoMin[i]);
    rho = min(rho, rhoMax[i]);
    rho.relax();

    volScalarField rAU("rAU", 1.0/UEqn().A());
    surfaceScalarField rhorAUf("rhorAUf", fvc::interpolate(rho*rAU));

    volVectorField HbyA("HbyA", U);
    HbyA = rAU*UEqn().H();
    UEqn.clear();

    surfaceScalarField phiHbyA
    (
        "phiHbyA",
        (fvc::interpolate(rho*HbyA) & mesh.Sf())
    );

    fvOptions.makeRelative(fvc::interpolate(rho), phiHbyA);

    bool closedVolume = adjustPhi(phiHbyA, U, p);

    dimensionedScalar compressibility = fvc::domainIntegrate(psi);
    bool compressible = (compressibility.value() > SMALL);

    // Solve pressure
    for (int nonOrth=0; nonOrth<=nNonOrthCorr; nonOrth++)
    {
        fvScalarMatrix pEqn
        (
            fvm::laplacian(rhorAUf, p) == fvc::div(phiHbyA)
        );

        pEqn.setReference
        (
            pRefCell,
            compressible ? getRefCellValue(p, pRefCell) : pRefValue
        );

        pEqn.solve();

        if (nonOrth == nNonOrthCorr)
        {
            // Calculate the conservative fluxes
            phi = phiHbyA - pEqn.flux();

            p = max(p, pMin[i]);
            p = min(p, pMax[i]);
            
            // Explicitly relax pressure for momentum corrector
            p.relax();
            // Correct the momentum source with the pressure gradient flux
            // calculated from the relaxed pressure
            U = HbyA - rAU*fvc::grad(p);
            U.correctBoundaryConditions();
            fvOptions.correct(U);
        }
    }

    #include "continuityErrs.H"

    // For closed-volume cases adjust the pressure level
    // to obey overall mass continuity
    if (closedVolume && compressible)
    {
        p += (initialMass - fvc::domainIntegrate(thermo.rho()))
            /compressibility;
    }

    rho = thermo.rho();
    rho = max(rho, rhoMin[i]);
    rho = min(rho, rhoMax[i]);
    rho.relax();

    Info<< "Min/max rho:" << min(rho).value() << ' '
        << max(rho).value() << endl;
}
