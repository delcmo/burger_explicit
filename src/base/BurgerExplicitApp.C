#include "BurgerExplicitApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"

template<>
InputParameters validParams<BurgerExplicitApp>()
{
  InputParameters params = validParams<MooseApp>();

  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  return params;
}

BurgerExplicitApp::BurgerExplicitApp(const std::string & name, InputParameters parameters) :
    MooseApp(name, parameters)
{
  srand(processor_id());

  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  BurgerExplicitApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  BurgerExplicitApp::associateSyntax(_syntax, _action_factory);
}

BurgerExplicitApp::~BurgerExplicitApp()
{
}

extern "C" void BurgerExplicitApp__registerApps() { BurgerExplicitApp::registerApps(); }
void
BurgerExplicitApp::registerApps()
{
  registerApp(BurgerExplicitApp);
}

void
BurgerExplicitApp::registerObjects(Factory & factory)
{
}

void
BurgerExplicitApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
}
