#include <DFRobot2WD.h>

DFRobot2WD r2d2; // variable permettant d'acceder aux fonctions du robot

/******************************
*  Fonction d'initialisation
*******************************/
void setup()
{
  r2d2.initialise(); // initialisation des entrées/sorties du robot
  Serial.begin(9600);
}

/******************************
*  Fonction principale
*******************************/
void loop()
{
  float uBatt = r2d2.lireTensionBatterie();
  Serial.print("la tension de la batterie est de ");
  Serial.print(uBatt);
  Serial.println(" V");
  delay(500);
}
