#ifndef ENTROPYVISCOSITYCOEFFICIENT_H
#define ENTROPYVISCOSITYCOEFFICIENT_H

#include "Material.h"

class EntropyViscosityCoefficient;

template<>
InputParameters validParams<EntropyViscosityCoefficient>();

/**
 * Computes dissipative fluxes for entropy viscosity method
 */
class EntropyViscosityCoefficient : public Material
{
public:
  EntropyViscosityCoefficient(const std::string & name, InputParameters parameters);
  virtual ~EntropyViscosityCoefficient();

protected:
  virtual void initQpStatefulProperties();  
  virtual void computeQpProperties();

  // Parameters
  bool _is_first_order;
  Real _Ce;
  Real _Cmax;

  // Coupled variables
  VariableValue & _u;

  // Coupled aux variables: entropy
  VariableValue & _E;
  VariableValue & _E_old;
  VariableValue & _E_older;

  // Coupled aux variables: entropy flux
  VariableGradient & _F_grad;

  // material to compute
  MaterialProperty<Real> & _kappa_old;
  MaterialProperty<Real> & _kappa;
  MaterialProperty<Real> & _kappa_max;
};

#endif /* ENTROPYVISCOSITYCOEFFICIENT_H */
