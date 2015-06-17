/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/
/**
This function computes the density of the fluid.
**/
#include "Flux.h"

template<>
InputParameters validParams<Flux>()
{
  InputParameters params = validParams<AuxKernel>();
  
  // Coupled variable
  params.addRequiredCoupledVar("var", "variable used to compute the flux");

  return params;
}

Flux::Flux(const std::string & name, InputParameters parameters) :
    AuxKernel(name, parameters),
    // Coupled variable
    _var(coupledValue("var"))
{}

Real
Flux::computeValue()
{
  return 0.5*_var[_qp]*_var[_qp];
}
