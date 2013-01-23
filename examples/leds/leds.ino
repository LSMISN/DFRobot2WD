#include <DFRobot2WD.h>

DFRobot2WD optimusPrime; // variable permettant d'acceder aux fonctions du robot

/******************************
*  Fonction d'initialisation
*******************************/
void setup()
{
  optimusPrime.initialise(); // initialisation des entrées/sorties du robot
}

/******************************
*  Fonction principale
*******************************/
void loop()
{
  optimusPrime.allumeLED(VERTE);
  delay(1000);
  optimusPrime.eteinsLED(VERTE);
  optimusPrime.allumeLED(ROUGE);
  delay(1000);
  optimusPrime.eteinsLED(ROUGE);
}
