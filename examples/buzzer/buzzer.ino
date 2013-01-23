#include <DFRobot2WD.h>

DFRobot2WD terminator; // variable permettant d'acceder aux fonctions du robot

void setup()
{
  terminator.initialise();
}

void loop()
{
  terminator.bip(80,1); // 80 bips à une fréquence
  terminator.bip(100,2); // 100 bips à une autre
}
