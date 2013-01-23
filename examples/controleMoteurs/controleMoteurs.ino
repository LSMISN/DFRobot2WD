#include <DFRobot2WD.h>

DFRobot2WD wall_E; // variable permettant d'acceder aux fonctions du robot
int compteur; // variable pour compter les impulsions IR reçues

/******************************
*  Fonction d'initialisation
*******************************/
void setup()
{
  wall_E.initialise(); // initialisation des entrées/sorties du robot
}

void loop()
{
  wall_E.controleMoteurs(AVANT,100,AVANT,100); // en avant wall-E
  delay(500); // temporisation de 500ms
  wall_E.controleMoteurs(AVANT,0,AVANT,0); // stop wall-E
  delay(500); // temporisation de 500ms
  wall_E.controleMoteurs(ARRIERE,150,ARRIERE,150); // en arriere wall-E
  delay(500); // temporisation de 500ms
  wall_E.controleMoteurs(ARRIERE,0,ARRIERE,0); // stop wall-E
  delay(500); // temporisation de 500ms
}
