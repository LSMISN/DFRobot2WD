#include <DFRobot2WD.h>

DFRobot2WD megatron; // variable permettant d'acceder aux fonctions du robot

/******************************
*  Fonction d'initialisation
*******************************/
void setup()
{
  megatron.initialise(); // initialisation des entrées/sorties du robot
  Serial.begin(9600);
}

/******************************
*  Fonction principale
*******************************/
void loop()
{
  uint16_t code = megatron.lireTelecommande();
  if(code != IR_NULL) Serial.println(code,HEX);
}
