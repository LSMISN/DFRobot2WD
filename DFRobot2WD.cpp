/**
 * \file DFRobot2WD.cpp
 * \brief bibliotheque arduino pour le robot DFRobot2WD miniQ
 * \author o.e, Lycee Sud Medoc
 * \version 0.1
 * \date 9 janvier 2013
 *
 * Implementation de la bibliotheque de fonctions pour le robot DFRobot 2WD miniQ
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

DFRobot2WD::DFRobot2WD(void)
/**
 * \brief constructeur d'un objet de la classe DFRobot2WD
 *
 *	permet de créer une variable associée au robot
 *	exemple : DFRobot2WD terminator;
 *
 */
{
}

DFRobot2WD::~DFRobot2WD(void)
/**
 * \brief destructeur d'un objet de la classe DFRobot2WD
 *	non utilisée dans le programme
 */
{
}

void DFRobot2WD::initialise(void)
/**
 * \brief initialise les entrées / sorties matérielles du DFRobot2WD
 *
 *	L'appel à cette fonction est nécessaire pour pouvoir commander le robot
 *	et accèder aux capteurs.
 *	on la placera dans la fonction setup() du programme principal
 *	exemple:
 *			void setup()
 *			{
 *				terminator.initialise();
 *			}
 */
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

void DFRobot2WD::controleMoteurs(uint8_t M1_DIR,uint8_t M1_EN,uint8_t M2_DIR,uint8_t M2_EN)
/**
 * \brief permet de régler la vitesse, et le sens de rotation des 2 moteurs du robot
 *
 * \param M1_DIR : sens de rotation moteur gauche
 * \param M1_EN : entier pris entre 0 et 255 représentant la vitesse de la roue gauche
 * \param M2_DIR : sens de rotation moteur droit
 * \param M2_EN : entier pris entre 0 et 255 représentant la vitesse de la roue droite
 *
 *	On controle la rotation des 2 roues
 *	exemple : terminator.controleMoteurs(AVANT, 100, ARRIERE, 100); // le robot tourne sur lui-même dans le sens horaire.
 *
 */
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

void DFRobot2WD::pulseIRGauche(void)
/**
 * \brief la LED infraRouge gauche émet 24 impulsions infrarouges.
 *	les LED infrarouges rentre dans le processus de détection d'obstacles placés face au robot
 *	exemple : 
 *				terminator.pulseIRGauche(); // on envoie une salve
 *				if(terminator.lireCompteurIR() > 20) // si le nombre d'impulsion reçu est supérieur à 20
 *					// alors c'est qu'il y a un obstacle à gauche
 */
{
	  
  for(int i=0;i<24;i++)
  {
    digitalWrite(L_IR,LOW);
    delayMicroseconds(8);
    digitalWrite(L_IR,HIGH);
    delayMicroseconds(8);
  }
 }

 void DFRobot2WD::pulseIRDroite(void)
 /**
 * \brief la LED infraRouge droite émet 24 impulsions infrarouges.
 *	les LED infrarouges rentre dans le processus de détection d'obstacles placés face au robot
 *	exemple : 
 *				terminator.pulseIRDroite(); // on envoie une salve
 *				if(terminator.lireCompteurIR() > 20) // si le nombre d'impulsion reçu est supérieur à 20
 *					// alors c'est qu'il y a un obstacle à droite
 */
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

void DFRobot2WD::bip(uint8_t nbreBip, uint8_t tempo)
/**
 * \brief la LED infraRouge gauche emet 24 impulsions infrarouges.
 *
 * \param nbreBip : règle la durée du bip
 * \param tempo : règle la tonalité du bip
 *
 *	Changer les 2 valeurs pour avoir différents types de tonalités
 *	exemple : terminator.bip(10,80);
 */
{
	for(int i=0;i<nbreBip;i++)
    {
      digitalWrite(BUZZER,HIGH);
      delay(tempo);
      digitalWrite(BUZZER,LOW);
      delay(tempo);
    }
}

float DFRobot2WD::lireLDR(void)
/**
 * \brief la LED infraRouge gauche emet 24 impulsions infrarouges.
 * \return un réel (float) image de la luminosité captée par l'avant du robot
 *	On peut se servir de la LDR pour suivre ou chercher (ou fuir) une source lumineuse.
 *  exemple : float lumiereAmbiante = terminator.lireLDR();
 */
{
	float lecture = analogRead(LDR);
	return lecture;
}

uint8_t DFRobot2WD::lireBoutons(void)
/**
 * \brief renvoie lequel des boutons est appuyé
 * \return 0: aucune touche		1: touche1(Key1) appuyée	2: touche1(Key2) appuyée	3: touche1(Key3) appuyée
 *	L'appel à cette fonction permet de savoir à un instant donné si un des boutons poussoirs est appuyée
 *	exemple : int idTouche  = terminator.lireBoutons // la variable idTouche contient alors le numéro de la touche appuyée.
 */
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

 void DFRobot2WD::allumeLED(uint8_t couleurLed)
 /**
 * \brief allume une des 2 LEDS (verte ou rouge)
 *
 * \param couleurLed prend ROUGE ou VERTE
 *	exemple : 
 * 				terminator.allumeLED(ROUGE);
 * 				terminator.allumeLED(VERTE);
 */
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

void DFRobot2WD::eteinsLED(uint8_t couleurLed)
 /**
 * \brief eteins une des 2 LEDS (verte ou rouge)
 *
 * \param couleurLed prend ROUGE ou VERTE
 *	exemple : 
 * 				terminator.eteinsLED(ROUGE);
 * 				terminator.eteinsLED(VERTE);
 */
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

void DFRobot2WD::activeIRsensor(void)
/**
 * \brief active le capteur infraRouge à l'avant du robot, enclenche le processus de comptage des impulsions captées.
 *	L'appel à cette fonction est nécessaire en cas d'utilisation du récepteur infrarouge (ce dernier étant géré par interruption)
 *  L'appel à cette fonction permet d'accéder au compteur d'impulsions infrarouges reçues sur le récepteur.
 *	exemple:
 *				terminator.activeIRsensor();
 *				int nombreImpulsionsRecus = terminator.lireCompteurIR();
 */
{
  PCICR = 0X01; // active les interruptions sur changement pour les broches PCINT[7:0]
  PCMSK0 = 0X01;// valide que l'entrée PCINT0 (celle du capteur IR)
  sei(); //active les interruptions
}

void DFRobot2WD::resetCompteurIR(void)
/**
 * \brief remise à zéro du compteur d'impulsions captées sur le capteur infrarouge.
 *	Il est nécessaire d'avoir activé le capteur infrarouge à l'aide de la fonction activeIRsensor pour utiliser cette fonction.
 *
 *	exemple : terminator.resetCompteurIR();
 */
{
	compteurIR = 0;
}

uint8_t DFRobot2WD::lireCompteurIR(void)
/**
 * \brief donne la valeur du compteur d'impulsions captées sur le capteur infrarouge.
 * \return un octet représentant le nombre d'impulsions infrarouge reçues
 *	Il est nécessaire d'avoir activé le capteur infrarouge à l'aide de la fonction activeIRsensor pour utiliser cette fonction.
 *
 *	exemple:
 *				terminator.activeIRsensor();
 *				int nombreImpulsionsRecus = terminator.lireCompteurIR();
 */
{
	return compteurIR;
}

float DFRobot2WD::lireCapteurLigne(int numeroCapteurDeLigneIR)
/**
 * \brief lit les capteurs de ligne IR connectés sur les entrées analogiques 0 à 3. 
 * \param numeroCapteurDeLigneIR : numéro d'un des 4 capteurs IR de ligne de 0 à 3
 * \return la tension lue par le image de la source IR réfléchie sous forme d'un float.
 *
 *	Il y a 4 capteurs à réflexion infrarouge sous l'avan du robot.
 * 	Cette fonction permet de lire la valeur de la tension du capteur qui proportionnelle à la lumière réfléchie sur le sol.
 *	En colorant le sol (ligne noir sur fond blanc par exemple), on peut détecter le chemin à suivre.
 * 	Exemple :
 *				float couleurSol = terminator.lireCapteurLigne(0); // stocke dans la variable une valeur image de la couleur (sombre ou claire) du sol
 *
 */
{
	if((numeroCapteurDeLigneIR >= 0) && (numeroCapteurDeLigneIR <= 3))
		return (analogRead(numeroCapteurDeLigneIR)*5)/1024;
}
ISR(PCINT0_vect)// interruption capteur IR
{
  compteurIR++;
}
// /**
 // * \fn void activeEncodeurs(void)
 // * \brief active la lecture des encodeurs présents sur les roues gauches et droites, enclenche le processus de comptage des impulsions captées.
 // */
// void DFRobot2WD::activeEncodeurs(void)
// {
	// masquer l'interruption sur INT0
	// masquer l'interruption sur INT1
	// activer le timer2 (va servir à déterminer la vitesse de rotation)
	// le faire déborder toutes les 500ms
	// activer les interruptions
	
// }
// /**
 // * \fn uint16_t lireEncodeurG(void)
 // * \brief donne la valeur du compteur d'impulsions captées sur la roue gauche.
  // * \return un entier sur 16bits représentant le nombre d'impulsions comptabilisées sur la roue gauche
 // */
// uint16_t DFRobot2WD::lireEncodeurG(void)
// {
	// return compteurRG;
// }
// /**
 // * \fn uint16_t lireEncodeurD(void)
 // * \brief donne la valeur du compteur d'impulsions captées sur la roue droite
 // * \return un entier sur 16bits représentant le nombre d'impulsions comptabilisées sur la roue droite.
 // */
// uint16_t DFRobot2WD::lireEncodeurD(void)
// {
	// return compteurRD;
// }
// /**
 // * \fn float lireFreqRG(void)
 // * \brief donne la fréquence de rotation de la roue gauche en tour/min
  // \return un réel(float) indiquant la fréquence de rotation de la roue gauche en tour/min
 // */
// float DFRobot2WD::lireFreqRG(void)
// {}
// /**
 // * \fn float lireFreqRD(void)
 // * \brief donne la fréquence de rotation de la roue droite en tour/min
  // \return un réel(float) indiquant la fréquence de rotation de la roue droite en tour/min
 // */
// float DFRobot2WD::lireFreqRD(void)
// {}

// ISR(INT0_vect)// interruption encodeur gauche
// {
  // compteurRG++; // on incrémente le compteur de la roue gauche
// }

// ISR(INT1_vect)// interruption encodeur droite
// {
  // compteurRD++;// on incrémente le compteur de la roue droite
// }