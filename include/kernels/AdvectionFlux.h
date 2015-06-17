#ifndef ADVECTIONFLUX_H
#define ADVECTIONFLUX_H

#include "Kernel.h"

//Forward Declarations
class AdvectionFlux;

template<>
InputParameters validParams<AdvectionFlux>();

class AdvectionFlux : public Kernel
{
public:

  AdvectionFlux(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeQpResidual();

  // Advection flux
  VariableValue & _flux;

  // Vector
  RealVectorValue _n;
};

#endif // ADVECTIONFLUX_H