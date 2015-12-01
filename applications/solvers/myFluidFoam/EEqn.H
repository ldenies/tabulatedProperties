{
    volScalarField& he = thermo.he();
    volScalarField& T = thermo.T();

    fvScalarMatrix EEqn
    (
        fvm::div(phi, he)
      + (
            he.name() == "e"
          ? fvc::div(phi, volScalarField("Ekp", 0.5*magSqr(U) + p/rho))
          : fvc::div(phi, volScalarField("K", 0.5*magSqr(U)))
        )
      - fvm::laplacian(turbulence->alphaEff(), he)
      + fvc::laplacian(turbulence->alphaEff(), he)
      - fvc::laplacian(turbulence->kappaEff(), T)
      + fvc::div(turbulence->devRhoReff() & U)
     ==
        fvOptions(rho, he)
    );

    EEqn.relax();

    fvOptions.constrain(EEqn);

    EEqn.solve();

    fvOptions.correct(he);

    thermo.correct();

    
}
