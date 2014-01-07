int ligne[5];
  
#include <DFRobot2WD.h>

DFRobot2WD r2d2; // variable permettant d'acceder aux fonctions du robot

void setup()
{
  r2d2.initialise();
  Serial.begin(9600);
  //r2d2.controleMoteurs(AVANT,22,AVANT,22);
}

void loop()
{
  for(int i=0 ; i<=4; i++)ligne[i]= r2d2.lireCapteurLigne(i);
  Serial.print(ligne[0]);
  Serial.print(", ");
  Serial.print(ligne[1]);
  Serial.print(", ");
  Serial.print(ligne[2]);
  Serial.print(", ");
  Serial.print(ligne[3]);
  Serial.print(", ");
  Serial.println(ligne[4]);
  delay(300);
  
}
