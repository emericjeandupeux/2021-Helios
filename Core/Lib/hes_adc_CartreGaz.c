#include "hes_adc_CartREGAZ.h"
#include <math.h>

float gain_SONOMETRE = 1;


float sensibilite_CO = 1;
float gain_CO = 1;


float sensibilite_H2S = 1;
float gain_H2S = 1;


float sensibilite_O2 = 1;
float gain_O2 = 1;


float sensibilite_EX = 1;
float gain_EX = 1;

float sensibilite_ADC = 1;

float sensibilite_SONOMETRE = 1;
float p0 = 1;

/*Fonction permettant de faire la conversion valeur ADC vers temperature*/
float adc_getTemperature(uint16_t value){
	float tension_capteur = sensibilite_ADC * value;
	return (tension_capteur - 0.425 )/(0.002); // en °C
}

/* Fonction permettant de faire la conversion valeur ADC vers niveau sonore*/
float adc_getNiveauSonore(uint16_t value){
	float tension_capteur = ((sensibilite_ADC * value) / gain_SONOMETRE) * 1000; // en mV
	float p = tension_capteur/sensibilite_SONOMETRE; // en uPa
	return 20*log10(p/p0); // en dB
}

float adc_getDioxigene(uint16_t value){
	float tension_capteur = (sensibilite_ADC * value) / gain_O2;
	return tension_capteur;
}

float adc_getMonoxyde(uint16_t value){
	float tension_capteur = (sensibilite_ADC * value) / gain_CO;
	return tension_capteur;
}

float adc_getSulfure(uint16_t value){
	float tension_capteur = (sensibilite_ADC * value) / gain_H2S;
	return tension_capteur;
}

/* Fonction permettant de faire la conversion valeur ADC vers niveau sonore*/
float adc_getExplosif(uint16_t value){
	float tension_capteur = (((sensibilite_ADC * value) - (2.85/2)) / gain_EX) * 1000; // en mV
	if ( tension_capteur < 0){
		tension_capteur = 0;
	}
	//return tension_capteur * sensibilite_EX; // en PPM
	return tension_capteur / sensibilite_EX; 
}

/*Fonction permettant d'initialiser la valeur des sensibilite et gain*/
void adc_Init(void){
	// affectation des variables
	sensibilite_ADC = 3.3 / pow(2,12);
	
	gain_SONOMETRE = 10;
	sensibilite_SONOMETRE = 0.01; //en V/upa dans le cas d'une sensiblite a  - 40dB on a 0,01V/upa
	sensibilite_SONOMETRE = sensibilite_SONOMETRE * 1000; // en mv/uPa
	p0 = 20; // en µPa
	
	//Monoxyde de carbone
	sensibilite_CO = 55* pow(10,-9);
	gain_CO = 82 * pow(10,4);
	
	//sulfure d'hydrogene 
	sensibilite_H2S = 50 * pow(10,-9);
	gain_H2S = 43 * pow(10,4);
	
	//explosif
	sensibilite_EX = 12 *pow(10,-3); // en mV/% de methane 
	sensibilite_EX = sensibilite_EX * 10000; // en mV/ppm
	gain_EX = 1;
	
	//Dioxygene
	sensibilite_O2 = 1;
	gain_O2 = 20;
	
	//sonometre
	p0 = 20; // 20µPa
	sensibilite_SONOMETRE = pow(10,-40/20); // sensiilite en V/Pa 0,01V/Pa soit 10mV/Pa
	sensibilite_SONOMETRE = sensibilite_SONOMETRE * pow(10,-6); // 0.01mV/µPA
}
