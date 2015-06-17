#include "ArtificialDissipation.h"

template<>
InputParameters validParams<ArtificialDissipation>()
{
  InputParameters params = validParams<Kernel>();

  return params;
}

ArtificialDissipation::ArtificialDissipation(const std::string & name, InputParameters parameters)
  :Kernel(name, parameters),
    _kappa(getMaterialPropertyOld<Real>("kappa"))
{
}

Real
ArtificialDissipation::computeQpResidual()
{
  return _kappa[_qp]*_grad_u[_qp]*_grad_test[_i][_qp];
}