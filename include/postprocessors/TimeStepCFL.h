#ifndef TIMESTEPCFL_H
#define TIMESTEPCFL_H

#include "ElementPostprocessor.h"

class TimeStepCFL;

template<>
InputParameters validParams<TimeStepCFL>();

/**
 * The inviscid time step stability limit:
 *
 * h_e \over {|\vec u| + c}
 */
class TimeStepCFL : public ElementPostprocessor
{
public:
  TimeStepCFL(const std::string & name, InputParameters parameters);
  virtual ~TimeStepCFL();

  virtual void initialize();
  virtual void execute();
  virtual Real getValue();
  virtual void threadJoin(const UserObject & uo);

protected:

  // Coupled variables
  VariableValue & _u;

  // Materials
  const MaterialProperty<Real> & _kappa;

  // Parameter
  Real _cfl;
  Real _value;
};


#endif // TIMESTEPCFL_H
