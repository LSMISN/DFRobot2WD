#include <DFRobot2WD.h>

DFRobot2WD R2D2; // variable permettant d'acceder aux fonctions du robot

/******************************
*  Fonction d'initialisation
*******************************/
void setup()
{
  R2D2.initialise(); // initialisation des entrées/sorties du robot
}

/******************************
*  Fonction principale
*******************************/
void loop()
{
  int valeur;
  do
  valeur = R2D2.lireBoutons();
  while(valeur == 0);
  
  if(valeur == 1)
  {
    R2D2.bip(80,1);
    R2D2.allumeLED(ROUGE);
  }
  else
    if(valeur == 2)
    {
      R2D2.bip(100,2);
      R2D2.allumeLED(VERTE);
    }
    else
      if(valeur == 3)
      {
        R2D2.bip(100,3);
        R2D2.eteinsLED(ROUGE);
        R2D2.eteinsLED(VERTE);
    }
}
