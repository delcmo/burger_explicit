#include "TimeStepCFL.h"

template<>
InputParameters validParams<TimeStepCFL>()
{
  InputParameters params = validParams<ElementPostprocessor>();

  // Coupled variables
  params.addRequiredCoupledVar("u", "variable solved for");
  // Parameter
  params.addParam<Real>("cfl", 0.8, "CFL number to supply by the user");

  return params;
}

TimeStepCFL::TimeStepCFL(const std::string & name, InputParameters parameters) :
    ElementPostprocessor(name, parameters),
    // Coupled variable
    _u(coupledValue("u")),
    // Viscous coefficient
    _kappa(getMaterialProperty<Real>("kappa")),
    // Parameters
    _cfl(getParam<Real>("cfl")),
    _value(0.)
{
}

TimeStepCFL::~TimeStepCFL()
{
}

void
TimeStepCFL::initialize()
{
  _value = std::numeric_limits<Real>::max();
}

void
TimeStepCFL::execute()
{
  // Compute cell size
  Real h_cell = std::pow(_current_elem->volume(), 1./_mesh.dimension());

  // Loop over quadrature points
  for (unsigned qp = 0; qp < _qrule->n_points(); ++qp)
  {
    // Compute local max eigenvalue
    Real dt_hyp = _cfl * h_cell / std::fabs(_u[qp]);
    Real dt_diff = 2. * _cfl * h_cell * h_cell / _kappa[qp];
    Real dt = std::min(dt_hyp, dt_diff);

    // Compute the local time step
    _value = std::min(_value, dt);
  }
}

Real
TimeStepCFL::getValue()
{
  _communicator.min(_value);
  return _value;
}

void
TimeStepCFL::threadJoin(const UserObject & uo)
{
  const TimeStepCFL & pps = dynamic_cast<const TimeStepCFL &>(uo);
  _value = std::min(_value, pps._value);
}