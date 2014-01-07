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
/** tension batterie connectée sur A6 par un pont diviseur de rapport 2/3*/ 
#define TENSION_BATTERIE 6
/** code de la télécommande IR pour aucune réception */
#define IR_NULL 0xFF00
/** code de la télécommande IR pour la fleche gauche */
#define IR_FLECHEGAUCHE 0xFB04
/** code de la télécommande IR pour la fleche droite */
#define IR_FLECHEDROITE 0xF906
/** code de la télécommande IR pour vol+ */
#define IR_VOLUMEPLUS 0xFE01
/** code de la télécommande IR pour func/stop */
#define IR_STOP 0xFD02
/** code de la télécommande IR pour lecture/pause */
#define IR_PAUSE 0xFA05
/** code de la télécommande IR pour la fleche vers le bas */
#define IR_FLECHEBAS 0xF708
/** code de la télécommande IR pour vol- */
#define IR_VOLUMEMOINS 0xF609
/** code de la télécommande IR pour la fleche vers le haut */
#define IR_FLECHEHAUT 0xF05A
/** code de la télécommande IR pour la touche 0 */
#define IR_ZERO 0xF30C
/** code de la télécommande IR pour la touche EQ */
#define IR_EQ 0xF20D
/** code de la télécommande IR pour touche ST/REPT */
#define IR_REPT 0xF10E
/** code de la télécommande IR pour la touche 1 */
#define IR_UN 0xEF10
/** code de la télécommande IR pour la touche 2 */
#define IR_DEUX 0xEE11
/** code de la télécommande IR pour la touche 3 */
#define IR_TROIS 0xED12
/** code de la télécommande IR pour la touche 4 */
#define IR_QUATRE 0xEB14
/** code de la télécommande IR pour la touche 5 */
#define IR_CINQ 0xEA15
/** code de la télécommande IR pour la touche 6 */
#define IR_SIX 0xE916
/** code de la télécommande IR pour la touche 7 */
#define IR_SEPT 0xE718
/** code de la télécommande IR pour la touche 8 */
#define IR_HUIT 0xE619
/** code de la télécommande IR pour la touche 9 */
#define IR_NEUF	0xE51A
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
  int lireCapteurLigne(int numeroCapteurDeLigneIR);
  uint16_t lireTelecommande(void);
  float lireTensionBatterie(void);
  
  private:

  char logic_value();
  void pulse_deal();
  void remote_decode(void);
  void timer1_init(void); // nécessaire pour le décodage de la télécommande IR
  };
#endif