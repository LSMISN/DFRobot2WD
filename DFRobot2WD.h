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
/** commande vitesse moteur droit sur D6 */ 
#define EN1 6
/** commande direction moteur droit sur D7*/ 
#define IN1 7
/** commande vitesse moteur gauche sur D5*/ 
#define EN2 5
/** commande vitesse moteur gauche sur D4*/ 
#define IN2 4
/** sélection marche avant */ 
#define AVANT 1
/** sélection marche arrière */ 
#define ARRIERE 0
/** récepteur infra-rouge connecté sur D8 */ 
#define RECEPTEUR_IR  8
/** émetteur infra-rouge dgauche connecté sur D9 */ 
#define L_IR 9
/** émetteur infra-rouge droite connecté sur D10 */ 
#define R_IR 10
/** buzzer connecté sur D11 */ 
#define BUZZER 11
/** led rouge connecté sur D12 */ 
#define LED_ROUGE 12//red led io pin
/** led rouge connecté sur D13 */ 
#define LED_VERTE 13
/** LDR connecté sur A4 */ 
#define LDR 4
/** boutons poussoirs S1, S2, S3 connectés sur A5 (pont diviseur de tension) */ 
#define TOUCHES 5 // A5 recoit les touches S1, S2, S3
/**
 * 
 * \brief couleurs des LED
 *
 *	Le DFRobot2WD miniQ possède 2 LEDs commandables, une rouge, une verte
 * 	valeurs à passer à la fonction allumeLED()
 *	exemple : 	monRobot.allumeLED(ROUGE);
 */
enum {
	ROUGE, /** < pour allumer la led rouge*/
	VERTE  /** < pour allumer la led verte*/
};

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
  float lireCapteurLigne(int numeroCapteurDeLigneIR);
  //private:
};
#endif