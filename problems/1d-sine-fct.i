[GlobalParams]
  implicit = false
  lumping = true
[]

[Mesh]
  type = GeneratedMesh
  dim = 1
  xmin = 0.
  xmax = 1.
  nx = 200
[]

[Functions]
  [./ic_func]
    axis = 0
    type = PiecewiseLinear
    x = '0  0.5  0.50001 1'
    y = '10 10   0.5     0.5'
  [../]
[]

[Variables]
  [./u]
    family = LAGRANGE
    order = FIRST
    [./InitialCondition]
      type = FunctionIC
      function = ic_func
    [../]
  [../]
[]

[Kernels]
  [./Time]
    type = TimeDerivative
    variable = u
    implicit = true    
  [../]

  [./AdvectionFlux]
    type = AdvectionFlux
    variable = u
    flux = flux
  [../]

  [./ArtDiff]
    type = ArtificialDissipation
    variable = u
  [../]
[]

[AuxVariables]
  [./flux]
    family = LAGRANGE
    order = FIRST
  [../]

  [./entropy_aux]
    family = LAGRANGE
    order = FIRST
  [../]

  [./F_aux]
    family = LAGRANGE
    order = FIRST
  [../]

  [./kappa_aux]
    family = MONOMIAL
    order = CONSTANT
  [../]

  [./kappa_max_aux]
    family = MONOMIAL
    order = CONSTANT
  [../]
[]

[AuxKernels]
  [./flux_ak]
    type = Flux
    variable = flux
    var = u
  [../]

  [./entropy_ak]
    type = ConstantAux
    variable = entropy_aux
    value = 0.
  [../]

  [./F_ak]
    type = ConstantAux
    variable = entropy_aux
    value = 0.
  [../]

  [./kappa_ak]
    type = MaterialRealAux
    variable = kappa_aux
    property = kappa
  [../]

  [./kappa_max_ak]
    type = MaterialRealAux
    variable = kappa_max_aux
    property = kappa_max
  [../]
[]

[Materials]
  [./EntropyViscosityCoeff]
    type = EntropyViscosityCoefficient
    block = 0
    is_first_order = true
    Ce = 1.
    u = u
    entropy = entropy_aux
    F = F_aux
  [../]
[]

[BCs]
  [./u_bc_left]
    type = DirichletBC
    variable = u
    boundary = left
    value = 10.
  [../]

  [./h_bc_right]
    type = DirichletBC
    variable = u
    boundary = right
    value = 0.5
  [../]
[]

[Postprocessors]
  [./dt]
    type = TimeStepCFL
    u = u
    cfl = 0.2
    outputs = none
  [../]
[]

[Executioner]
  type = Transient
  scheme = 'implicit-euler' # 'rk-2'

  dt = 1.e-2
  
  [./TimeStepper]
    type = PostprocessorDT
    postprocessor = dt
    dt = 1.e-5
  [../]

  nl_rel_tol = 1e-12
  nl_abs_tol = 1e-6
  nl_max_its = 10

  end_time = 8.e-2
#  num_steps = 1

  [./Quadrature]
    type = GAUSS
    order = SECOND
  [../]

[]

[Outputs]
  output_initial = true
  exodus = true
  print_linear_residuals = false
  print_perf_log = true
  interval = 1
[]