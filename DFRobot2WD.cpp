/**
 * \file DFRobot2WD.cpp
 * \brief Programme de tests.
 * \author o.eloi, Lycee Sud Medoc
 * \version 0.1
 * \date 9 janvier 2013
 *
 * Impl�mentation de la biblioth�que de fonctions pour le robot DFRobot 2WD miniQ
 *
 */

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include <avr/io.h>
 #include "WProgram.h"
#endif
#include "DFRobot2WD.h"

static volatile uint16_t compteurIR; // le compteur d'impulsions IR
// static volatile uint16_t compteurRG; // le compteur d'impulsions encodeur roue gauche
// static volatile uint16_t compteurRG; // le compteur d'impulsions encodeur roue droite

/**
 * \fn DFRobot2WD(void)
 * \brief constructeur d'un objet de la classe DFRobot2WD
 *
 * \param aucun
 * \return aucun
 */
DFRobot2WD::DFRobot2WD(void)
{
}
/**
 * \fn ~DFRobot2WD(void)
 * \brief destructeur d'un objet de la classe DFRobot2WD
 *
 * \param aucun
 * \return aucun
 */
DFRobot2WD::~DFRobot2WD(void)
{
}
/**
 * \fn void initialise(void)
 * \brief initialise les entr�es / sorties mat�rielles du DFRobot2WD
 *
 * \param aucun
 * \return aucun
 */
void DFRobot2WD::initialise(void)
{
	for(int i = 4 ; i <= 7; i++) pinMode(i,OUTPUT);
	pinMode(L_IR,OUTPUT);//init the left transmitter pin
	pinMode(R_IR,OUTPUT);//init the right transmitter pin
	pinMode(RECEPTEUR_IR,INPUT);//init the ir receiver pin
	pinMode(BUZZER,OUTPUT);//init buzzer
	pinMode(LED_ROUGE,OUTPUT);//init red led
	pinMode(LED_VERTE,OUTPUT);//init green led
	digitalWrite(R_IR,HIGH);
	digitalWrite(L_IR,HIGH);
}
/**
 * \fn void controleMoteurs(uint8_t M1_DIR,uint8_t M1_EN,uint8_t M2_DIR,uint8_t M2_EN)
 * \brief permet de r�gler la vitesse, et le sens de rotation des 2 moteurs du robot
 *
 * \param M1_DIR, M2_DIR : sens de rotation moteurs gauche & droit (prend la AVANT ou ARRIERE) M1_EN, M2_EN : entier pris entre 0 et 255 repr�sentant la vitesse roue gauche (resp. roue droite)
 * \return aucun
 */
void DFRobot2WD::controleMoteurs(uint8_t M1_DIR,uint8_t M1_EN,uint8_t M2_DIR,uint8_t M2_EN)
{
//////////M1////////////////////////
  if(M1_DIR==AVANT)//M1 motor direction
    digitalWrite(IN1,AVANT);//AVANTard
  else
    digitalWrite(IN1,ARRIERE);//ARRIERE
  if(M1_EN==0)
    analogWrite(EN1,LOW);//stop
  else
    analogWrite(EN1,M1_EN);//set speed

  ///////////M2//////////////////////
  if(M2_DIR==AVANT)
    digitalWrite(IN2,AVANT);
  else
    digitalWrite(IN2,ARRIERE);
  if(M2_EN==0)
    analogWrite(EN2,LOW);
  else
    analogWrite(EN2,M2_EN);
	}
/**
 * \fn void pulseIRGauche(void)
 * \brief la LED infraRouge gauche emet 24 impulsions infrarouges.
 *
 * \param aucun
 * \return aucun
 */
void DFRobot2WD::pulseIRGauche(void)
{
	  
  for(int i=0;i<24;i++)
  {
    digitalWrite(L_IR,LOW);
    delayMicroseconds(8);
    digitalWrite(L_IR,HIGH);
    delayMicroseconds(8);
  }
 }
 /**
 * \fn void pulseIRDroite(void)
 * \brief la LED infraRouge droite emet 24 impulsions infrarouges.
 *
 * \param aucun
 * \return aucun
 */
 void DFRobot2WD::pulseIRDroite(void)
 {
  int i;
  for(i=0;i<24;i++)
  {
    digitalWrite(R_IR,LOW);
    delayMicroseconds(8);
    digitalWrite(R_IR,HIGH);
    delayMicroseconds(8);
  }
}
/**
 * \fn void bip(uint8_t nbreBip, uint8_t tempo)
 * \brief la LED infraRouge gauche emet 24 impulsions infrarouges.
 *
 * \param nbreBip : r�gle la dur�e du bip	tempo : r�gle la tonalit� du bip
 * \return aucun
 */
void DFRobot2WD::bip(uint8_t nbreBip, uint8_t tempo)
{
	for(int i=0;i<nbreBip;i++)
    {
      digitalWrite(BUZZER,HIGH);
      delay(tempo);
      digitalWrite(BUZZER,LOW);
      delay(tempo);
    }
}
/**
 * \fn float lireLDR(void)
 * \brief la LED infraRouge gauche emet 24 impulsions infrarouges.
 *
 * \param aucun
 * \return un r�el (float) image de la luminosit� capt�e par l'avant du robot
 */
float DFRobot2WD::lireLDR(void)
{
	float lecture = analogRead(LDR);
	return lecture;
}
/**
 * \fn uint8_t lireBoutons(void)
 * \brief renvoie lequel des boutons est appuy�
 *
 * \param aucun
 * \return 0: aucune touche		1: touche1(Key1) appuy�e	2: touche1(Key2) appuy�e	3: touche1(Key3) appuy�e
 */
uint8_t DFRobot2WD::lireBoutons(void)
{
	float data = analogRead(TOUCHES);
	data = ((data*5.0)/1024.0);
	if(data>4.50&&data<6.00) return 0;// no input
    else
		if(data>=0.00&&data<0.50)//press button1
		{
			delay(180);//remove noise
			if(data>=0.00&&data<0.50)//confirm the button pressed
			return 1;
		}
		else 
			if(data>=0.50&&data<1.5)
			{
				delay(180);
				if(data>=0.50&&data<1.5)
				return 2;
			}
			else 
				if(data>=1.5&&data<2.5)
				{
					delay(180);
					if(data>=1.5&&data<2.5)
					return 3;
				}
 }
 /**
 * \fn void allumeLED(uint8_t couleurLed)
 * \brief allume une des 2 LEDS (verte ou rouge)
 *
 * \param couleurLed prend ROUGE ou VERTE
 * \return aucun
 */
 void DFRobot2WD::allumeLED(uint8_t couleurLed)
 {
	switch(couleurLed)
	{
		case ROUGE:
			digitalWrite(LED_ROUGE, HIGH);
			break;
		case VERTE:
			digitalWrite(LED_VERTE, HIGH);
			break;
	}
}
/**
 * \fn void eteinsLED(uint8_t couleurLed)
 * \brief eteins une des 2 LEDS (verte ou rouge)
 *
 * \param couleurLed prend ROUGE ou VERTE
 * \return aucun
 */
void DFRobot2WD::eteinsLED(uint8_t couleurLed)
 {
	switch(couleurLed)
	{
		case ROUGE:
			digitalWrite(LED_ROUGE, LOW);
			break;
		case VERTE:
			digitalWrite(LED_VERTE, LOW);
			break;
	}
}
/**
 * \fn void activeIRsensor(void)
 * \brief active le capteur infraRouge � l'avant du robot, enclenche le processus de comptage des impulsions capt�es.
 *
 * \param aucun
 * \return aucun
 */
void DFRobot2WD::activeIRsensor(void)
{
  PCICR = 0X01; // active les interruptions sur changement pour les broches PCINT[7:0]
  PCMSK0 = 0X01;// valide que l'entr�e PCINT0 (celle du capteur IR)
  sei(); //active les interruptions
}
/**
 * \fn void resetCompteurIR(void)
 * \brief remise � z�ro du compteur d'impulsions capt�es sur le capteur infrarouge.
 *
 * \param aucun
 * \return aucun
 */
void DFRobot2WD::resetCompteurIR(void)
{
	compteurIR = 0;
}
/**
 * \fn uint8_t lireCompteurIR(void)
 * \brief donne la valeur du compteur d'impulsions capt�es sur le capteur infrarouge.
 *
 * \param aucun
 * \return un octet repr�sentant le nombre d'impulsions infrarouge re�ues
 */
uint8_t DFRobot2WD::lireCompteurIR(void)
{
	return compteurIR;
}

/**
 * \fn void lireCapteurLigne(int numeroCapteurDeLigneIR)
 * \brief lit les capteurs de ligne IR connect�s sur les entr�es analogiques 0 � 3. Les valeurs sont stock�es dans le tableau ligneIR[].
 *
 * \param num�ro d'un des 4 capteurs IR de ligne de 0 � 3
 * \return la valeur lue par le capteur de ligne IR sous forme d'un entier 16bits 
 */
uint16_t DFRobot2WD::lireCapteurLigne(int numeroCapteurDeLigneIR)
{
	if((numeroCapteurDeLigneIR >= 0) && (numeroCapteurDeLigneIR <= 3))
		return analogRead(numeroCapteurDeLigneIR);
}
ISR(PCINT0_vect)// interruption capteur IR
{
  compteurIR++;
}
// /**
 // * \fn void activeEncodeurs(void)
 // * \brief active la lecture des encodeurs pr�sents sur les roues gauches et droites, enclenche le processus de comptage des impulsions capt�es.
 // *
 // * \param aucun
 // * \return aucun
 // */
// void DFRobot2WD::activeEncodeurs(void)
// {
	// masquer l'interruption sur INT0
	// masquer l'interruption sur INT1
	// activer le timer2 (va servir � d�terminer la vitesse de rotation)
	// le faire d�border toutes les 500ms
	// activer les interruption
	
// }
// /**
 // * \fn uint16_t lireEncodeurG(void)
 // * \brief donne la valeur du compteur d'impulsions capt�es sur la roue gauche.
 // *
 // * \param aucun
 // * \return un entier sur 16bits repr�sentant le nombre d'impulsions comptabilis�es sur la roue gauche
 // */
// uint16_t DFRobot2WD::lireEncodeurG(void)
// {
	// return compteurRG;
// }
// /**
 // * \fn uint16_t lireEncodeurD(void)
 // * \brief donne la valeur du compteur d'impulsions capt�es sur la roue droite
 // *
 // * \param aucun
 // * \return un entier sur 16bits repr�sentant le nombre d'impulsions comptabilis�es sur la roue droite.
 // */
// uint16_t DFRobot2WD::lireEncodeurD(void)
// {
	// return compteurRD;
// }
// /**
 // * \fn float lireFreqRG(void)
 // * \brief donne la fr�quence de rotation de la roue gauche en tour/min
 // *
 // * \param aucun
  // \return un r�el(float) indiquant la fr�quence de rotation de la roue gauche en tour/min
 // */
// float DFRobot2WD::lireFreqRG(void)
// {}
// /**
 // * \fn float lireFreqRD(void)
 // * \brief donne la fr�quence de rotation de la roue droite en tour/min
 // *
 // * \param aucun
  // \return un r�el(float) indiquant la fr�quence de rotation de la roue droite en tour/min
 // */
// float DFRobot2WD::lireFreqRD(void)
// {}

// ISR(INT0_vect)// interruption encodeur gauche
// {
  // compteurRG++; // on incr�mente le compteur de la roue gauche
// }

// ISR(INT1_vect)// interruption encodeur droite
// {
  // compteurRD++;// on incr�mente le compteur de la roue droite
// }