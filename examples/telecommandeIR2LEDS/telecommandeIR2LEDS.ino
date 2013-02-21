#include <DFRobot2WD.h>

DFRobot2WD megatron; // variable permettant d'acceder aux fonctions du robot

/******************************
*  Fonction d'initialisation
*******************************/
void setup()
{
  megatron.initialise(); // initialisation des entrées/sorties du robot
}

/******************************
*  Fonction principale
*******************************/
void loop()
{
  int code = megatron.lireTelecommande();
  switch(code)
  {
    case IR_VOLUMEPLUS: //volume+
       megatron.allumeLED(ROUGE);
       megatron.eteinsLED(VERTE);
       break;
    case IR_VOLUMEMOINS: //volume-
       megatron.allumeLED(VERTE);
       megatron.eteinsLED(ROUGE);
       break;
    case IR_FLECHEGAUCHE: // fleche gauche
      megatron.allumeLED(ROUGE);
      megatron.allumeLED(VERTE);
      break;
    case IR_FLECHEDROITE: // fleche droite
      megatron.eteinsLED(VERTE);
      megatron.eteinsLED(ROUGE);
      break;
  }
}
