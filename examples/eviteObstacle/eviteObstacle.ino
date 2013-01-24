#include <DFRobot2WD.h>

DFRobot2WD monRobot; // variable permettant d'acceder aux fonctions du robot

/******************************
 *  Fonction d'initialisation
 *******************************/
void setup()
{
  monRobot.initialise(); // initialisation des entrées/sorties du robot
  monRobot.activeIRsensor(); // active le capteur IR & donne accès à la variable monRobot.monRobot.compteurIR
}

/******************************
 *  Fonction principale
 *******************************/
void loop()
{
  eviteObstacle(); // le robot ne fait que ça !
}

/********************************************
 *  Fonction permettant d'éviter les obstacles
 *   s'il n'y a pas d'obstacle
 *   le robot avance tout droit
 *********************************************/
void eviteObstacle()
{
  monRobot.resetCompteurIR(); // raz du compteur d'impulsions
  for(int i=0; i < 20; i++)// on envoie 20 impulsions à gauche
  {
    monRobot.pulseIRGauche();
    delayMicroseconds(600);
  }
  if(monRobot.lireCompteurIR() > 20) // si obstacle à gauche
  {// on manoeuvre pour eviter obstacle à gauche
    monRobot.controleMoteurs(ARRIERE,100,ARRIERE,100);
    delay(300);
    monRobot.controleMoteurs(ARRIERE,100,AVANT,100);
    delay(500);
  }
  else // SINON
  {
    monRobot.resetCompteurIR(); // raz du compteur d'impulsions
    for(int i = 0; i < 20; i++) // on envoie 20 impulsions à droite
    {
      monRobot.pulseIRDroite();
      delayMicroseconds(600);
    }
    if(monRobot.lireCompteurIR() > 20) // si obstacle a droite
    {  // on manoeuvre pour eviter obstacle à droite
      monRobot.controleMoteurs(ARRIERE,100,ARRIERE,100);
      delay(300);
      monRobot.controleMoteurs(AVANT,100,ARRIERE,100);
      delay(500);
    } // SINON on va tout droit
    else monRobot.controleMoteurs(AVANT,100,AVANT,100);
  }
}


