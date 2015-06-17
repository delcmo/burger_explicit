#include "AdvectionFlux.h"

template<>
InputParameters validParams<AdvectionFlux>()
{
  InputParameters params = validParams<Kernel>();

  // Coupled variable
  params.addRequiredCoupledVar("flux", "advection flux of the hyperbolic scalar equation");

  return params;
}

AdvectionFlux::AdvectionFlux(const std::string & name, InputParameters parameters)
  :Kernel(name, parameters),
    // Coupled variable
    _flux(coupledValueOld("flux"))
{
  // Set the vector _n in the constructor
  if (_mesh.dimension()==1)
  {
    _n(0)=1.; _n(1)=0.; _n(2)=0.;
  }
  else if (_mesh.dimension()==2)
  {
    _n(0)=1.; _n(1)=1.; _n(2)=0.;
  }
  else
  {
    _n(0)=1.; _n(1)=1.; _n(2)=1.;
  }
}

Real
AdvectionFlux::computeQpResidual()
{
  return -_flux[_qp]*_n*_grad_test[_i][_qp];
}