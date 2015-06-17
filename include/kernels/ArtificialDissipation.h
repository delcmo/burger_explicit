#ifndef ARTIFICIALDISSIPATION_H
#define ARTIFICIALDISSIPATION_H

#include "Kernel.h"

//Forward Declarations
class ArtificialDissipation;

template<>
InputParameters validParams<ArtificialDissipation>();

class ArtificialDissipation : public Kernel
{
public:

  ArtificialDissipation(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeQpResidual();

  // Viscous coefficient
  MaterialProperty<Real> & _kappa;

};

#endif // ARTIFICIALDISSIPATION_H