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

#ifndef FLUX_H
#define FLUX_H

#include "AuxKernel.h"

class Flux;

template<>
InputParameters validParams<Flux>();

class Flux : public AuxKernel
{
public:

  Flux(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeValue();

  // Coupled variable
  VariableValue & _var;
};

#endif // FLUX_H
