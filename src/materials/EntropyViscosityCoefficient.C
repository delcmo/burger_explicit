#include "EntropyViscosityCoefficient.h"

template<>
InputParameters validParams<EntropyViscosityCoefficient>()
{
  InputParameters params = validParams<Material>();

  // Parameters
  params.addParam<bool>("is_first_order", false, "if true, use the first-order viscosity coefficient");
  params.addParam<Real>("Ce", 1., "coefficient for high-order viscosity coefficient");
  params.addParam<Real>("Cmax", 0.5, "coefficient for first-order viscosity coefficient");
  // Coupled variable
  params.addRequiredCoupledVar("u", "variable we are solving for");
  // Coupled aux variables
  params.addRequiredCoupledVar("entropy", "entropy function");
  params.addRequiredCoupledVar("F", "entropy flux");

  return params;
}

EntropyViscosityCoefficient::EntropyViscosityCoefficient(const std::string & name, InputParameters parameters) :
    Material(name, parameters),
    // Parameters
    _is_first_order(getParam<bool>("is_first_order")),
    _Ce(getParam<Real>("Ce")),
    _Cmax(getParam<Real>("Cmax")),
    // Coupled variables
    _u(coupledValue("u")),
    // Coupled aux variables: entropy
    _E(coupledValue("entropy")),
    _E_old(coupledValueOld("entropy")),
    _E_older(coupledValueOlder("entropy")),
    // Coupled aux variables: entropy flux
    _F_grad(coupledGradient("F")),
    // Materials
    _kappa_old(declarePropertyOld<Real>("kappa")),
    _kappa(declareProperty<Real>("kappa")),
    _kappa_max(declareProperty<Real>("kappa_max"))
{
}

EntropyViscosityCoefficient::~EntropyViscosityCoefficient()
{}

void
EntropyViscosityCoefficient::initQpStatefulProperties()
{
  // Cell size
  Real h_cell = std::pow(_current_elem->volume(),1./_mesh.dimension());

  // Set value for the material
  _kappa[_qp] = _Cmax*h_cell;
}

void
EntropyViscosityCoefficient::computeQpProperties()
{
  // Cell size
  Real h_cell = std::pow(_current_elem->volume(),1./_mesh.dimension());

  // First-order viscosity coefficient
  _kappa_max[_qp] = _Cmax*h_cell*std::fabs(_u[_qp]);

  // Weights for BDF2
  Real w0 = _t_step > 1 ? (2.*_dt+_dt_old)/(_dt*(_dt+_dt_old)) : 1. / _dt;
  Real w1 = _t_step > 1 ? -(_dt+_dt_old)/(_dt*_dt_old) : -1. / _dt;
  Real w2 = _t_step > 1 ? _dt/(_dt_old*(_dt+_dt_old)) : 0.;
  
  // Entropy residual
  Real residual = w0*_E[_qp]+w1*_E_old[_qp]+w2*_E_older[_qp];
  residual += _F_grad[_qp](0);
  
  // Normalization parameter
  Real norm = 1.;

  // High-order viscosity coefficient
  Real kappa = _t_step == 1 ? _kappa_max[_qp] : _Ce*h_cell*h_cell*std::fabs(residual/norm);

  // Return value of the viscosity coefficient
  _kappa[_qp] = _is_first_order ? _kappa_max[_qp] : std::min(kappa, _kappa_max[_qp]);
}