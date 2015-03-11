#ifndef BURGER_EXPLICITAPP_H
#define BURGER_EXPLICITAPP_H

#include "MooseApp.h"

class BurgerExplicitApp;

template<>
InputParameters validParams<BurgerExplicitApp>();

class BurgerExplicitApp : public MooseApp
{
public:
  BurgerExplicitApp(const std::string & name, InputParameters parameters);
  virtual ~BurgerExplicitApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
};

#endif /* BURGER_EXPLICITAPP_H */
