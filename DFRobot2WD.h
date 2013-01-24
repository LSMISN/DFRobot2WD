/**
 * \file DFRobot2WD.h
 * \brief Programme de tests.
 * \author o.eloi, Lycee Sud Medoc
 * \version 0.1
 * \date 9 janvier 2013
 *
 * Bibliothèque de fonctions pour le robot DFRobot 2WD miniQ
 *
 */

#ifndef _DFRobot2WD_h_
#define _DFRobot2WD_h_

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define EN1 6//pin for run the right motor 
#define IN1 7//pin for control right motor direction
#define EN2 5//pin for run the left motor 
#define IN2 4//pin for control left motor direction

#define AVANT 1//go forward
#define ARRIERE 0//go back

#define RECEPTEUR_IR  8//IR receiver pin
#define L_IR 9//left IR LED transmitter pin
#define R_IR 10//right IR LED transmitter pin
#define BUZZER 11//the buzzer pin
#define LED_ROUGE 12//red led io pin
#define LED_VERTE 13//green led io pin
#define Vr   5//reference voltage
#define LDR 4 // A4 recoit la moyenne des tensions LDR
#define TOUCHES 5 // A5 recoit les touches S1, S2, S3

enum {ROUGE, VERTE};

class DFRobot2WD
{
  public:
  
  
  DFRobot2WD(); // constructeur
  ~DFRobot2WD(); // destructeur
  void controleMoteurs(uint8_t,uint8_t,uint8_t,uint8_t);
  void initialise(void);
  void pulseIRGauche(void);//left ir transmitter sends 40kHZ pulse
  void pulseIRDroite(void);//right ir transmitter sends 40kHZ pulse
  void bip(uint8_t,uint8_t);
  uint8_t lireBoutons(void); // fait une lecture des 3 touches et renvoie laquelle est appuyée
  void allumeLED(uint8_t);
  void eteinsLED(uint8_t);
  float lireLDR(void);
  void activeIRsensor(void); // active la fonction d'interruption associée à la capture des impulsions IR, qui les compte
  void resetCompteurIR(void); // remise à zero du compteur d'impulsions IR
  uint8_t lireCompteurIR(void); // renvoi le nombre d'impulsions reçues comptées depuis la remise à zero du compteur
  // void activeEncodeurs(void);
  // uint16_t lireEncodeurG(void);
  // uint16_t lireEncodeurD(void);
  // float lireFreqRG(void);
  // float lireFreqRD(void);
  uint16_t lireCapteurLigne(int numeroCapteurDeLigneIR);
  //private:
};

// class MsTimer2
// {
	// unsigned long msecs;
	// void (*func)();
	// extern volatile unsigned long count;
	// extern volatile char overflowing;
	// extern volatile unsigned int tcnt2;
	
	// void set(unsigned long ms, void (*f)());
	// void start();
	// void stop();
	// void _overflow();
// }
#endif