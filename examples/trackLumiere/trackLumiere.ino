#include <DFRobot2WD.h>

DFRobot2WD bishop; // variable permettant d'acceder aux fonctions du robot

#define SEUIL 0.5

void setup()
{
  bishop.initialise();
}

void loop()
{
  do{}while(bishop.lireBoutons() != 1); // on attend l'appui sur S0
  // on allume la led rouge pour indiquer la phase de calibrage
  bishop.allumeLED(ROUGE);
  bishop.bip(100,2);
  delay(1000); // on attend 1s le temps de dégager la main
  // on effectue 100 mesures d'éclairage de référence : pointer les LDR avec une LED.
  float eclairageMoyen = 0;
  for(int i = 0 ; i < 100 ; i++)
  {
    eclairageMoyen = eclairageMoyen  + bishop.lireLDR();
  }
  eclairageMoyen = eclairageMoyen / 100;
  // on allume la led verte et on eteind la led rouge pour indiquer que le calibrage est terminé
  bishop.eteinsLED(ROUGE);
  bishop.allumeLED(VERTE);
  bishop.bip(300,1);
  do{}while(bishop.lireBoutons() != 2); // on attend l'appui sur S1
  bishop.eteinsLED(VERTE);
  // on tracke la lumiere !
  while(1)
  {
    float eclairageActuel = bishop.lireLDR();
    if(eclairageActuel < (eclairageMoyen - SEUIL))
      bishop.controleMoteurs(AVANT,100, ARRIERE,100);// tourne a gauche
      else
        if(eclairageActuel > (eclairageMoyen + SEUIL))
          bishop.controleMoteurs(ARRIERE,100,AVANT,100);//tourne a droite
          else
            bishop.controleMoteurs(AVANT,0,AVANT,0); //ARRET
  }
}

