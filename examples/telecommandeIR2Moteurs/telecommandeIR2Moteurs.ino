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
       megatron.controleMoteurs(AVANT,100,AVANT,100);
       break;
    case IR_VOLUMEMOINS: //volume-
       megatron.controleMoteurs(ARRIERE,100,ARRIERE,100);
       break;
    case IR_FLECHEGAUCHE: // fleche gauche
      megatron.controleMoteurs(AVANT,100,ARRIERE,100);
      break;
    case IR_FLECHEDROITE: // fleche droite
      megatron.controleMoteurs(ARRIERE,100,AVANT,100);
      break;
    case IR_NULL:
      megatron.controleMoteurs(AVANT,0,AVANT,0);
  }
}
