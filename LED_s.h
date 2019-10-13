//**********Library**********//

#include "BTP_Screen.h"
#include <FastLED.h>

//**********Definitions**********//

#define LED_PIN 2                                                                                   // Définit le pin 2 comme le pin de communication avec les LEDs
#define NUM_LEDS 92                                                                                 // Définit le nombre de LEDs (92)
#define COLOR_ORDER GRB
#define FRAMES_PER_SECOND  120

//**********Noms**********//

CRGBArray<NUM_LEDS> leds;                                                                           // Définit "leds" la liste des 92 LEDs ordonnées

//**********Variables**********//                                                                   // Définit les variables utiles qui ne sont pas importées de "BTP_Screen.h"

byte start_point,end_point,last_point,anim;
byte vitesse=2,seuil_luminosite=60,lum_max=150;
byte couronnes[92]={81,82,83,84,85,86,87,88,89,90,91,92,
                  4,5,12,13,20,21,28,29,36,37,44,45,77,78,79,80,
                  3,6,11,14,19,22,27,30,35,38,43,46,76,75,74,73,
                  2,7,10,15,18,23,26,31,34,39,42,47,69,70,71,72,
                  1,8,9,16,17,24,25,32,33,40,41,48,68,67,66,65,
                  49,50,51,52,53,60,61,62,63,64,57,56,
                  54,55,59,58};

//**********Loops**********//

void led_vague(int i){                                                                              // Allume les LEDs couronne par couronne d'une couleur différente, en différé, la luminosité d'une couronne suivant une loi gaussienne
  if((i>=0)&&(i<lum_max)){for(byte k=0;k<12;k++){leds[couronnes[k]-1]=CRGB(i,1.2*i,0);}}//jaune
  if((i>=lum_max)&&(i<(2*lum_max))){for(byte k=0;k<12;k++){leds[couronnes[k]-1]=CRGB(2*lum_max-vitesse-i,2*lum_max-vitesse-i,0);}}//jaune
  if((i>=seuil_luminosite)&&(i<lum_max+seuil_luminosite)){for(byte k=0;k<16;k++){leds[couronnes[k+12]-1]=CRGB((i-seuil_luminosite)/4,i-seuil_luminosite,0);}}//orange
  if((i>=(lum_max+seuil_luminosite))&&(i<(2*lum_max+seuil_luminosite))){for(byte k=0;k<16;k++){leds[couronnes[k+12]-1]=CRGB((2*lum_max-vitesse-i+seuil_luminosite)/4,2*lum_max-vitesse-i+seuil_luminosite,0);}}//orange
  if((i>=2*seuil_luminosite)&&(i<lum_max+2*seuil_luminosite)){for(byte k=0;k<16;k++){leds[couronnes[k+28]-1]=CRGB(0,i-2*seuil_luminosite,(i-2*seuil_luminosite)/4);}}//rose
  if((i>=(lum_max+2*seuil_luminosite))&&(i<(2*lum_max+2*seuil_luminosite))){for(byte k=0;k<16;k++){leds[couronnes[k+28]-1]=CRGB(0,2*lum_max-vitesse-i+2*seuil_luminosite,(2*lum_max-vitesse-i+2*seuil_luminosite)/4);}}//rose
  if((i>=3*seuil_luminosite)&&(i<lum_max+3*seuil_luminosite)){for(byte k=0;k<16;k++){leds[couronnes[k+44]-1]=CRGB(0,i-3*seuil_luminosite,(i-3*seuil_luminosite)/1.2);}}//violet
  if((i>=(lum_max+3*seuil_luminosite))&&(i<(2*lum_max+3*seuil_luminosite))){for(byte k=0;k<16;k++){leds[couronnes[k+44]-1]=CRGB(0,2*lum_max-vitesse-i+3*seuil_luminosite,(2*lum_max-vitesse-i+3*seuil_luminosite)/1.2);}}//violet
  if((i>=4*seuil_luminosite)&&(i<lum_max+4*seuil_luminosite)){for(byte k=0;k<16;k++){leds[couronnes[k+60]-1]=CRGB((i-4*seuil_luminosite)/4,(i-4*seuil_luminosite)/4,i-4*seuil_luminosite);}}//bleu ciel
  if((i>=(lum_max+4*seuil_luminosite))&&(i<(2*lum_max+4*seuil_luminosite))){for(byte k=0;k<16;k++){leds[couronnes[k+60]-1]=CRGB((2*lum_max-vitesse-i+4*seuil_luminosite)/4,(2*lum_max-vitesse-i+4*seuil_luminosite)/4,2*lum_max-vitesse-i+4*seuil_luminosite);}}//bleu ciel
  if((i>=5*seuil_luminosite)&&(i<lum_max+5*seuil_luminosite)){for(byte k=0;k<12;k++){leds[couronnes[k+76]-1]=CRGB(i-5*seuil_luminosite,0,(i-5*seuil_luminosite)/2);}}//vert-cyan
  if((i>=(lum_max+5*seuil_luminosite))&&(i<(2*lum_max+5*seuil_luminosite))){for(byte k=0;k<12;k++){leds[couronnes[k+76]-1]=CRGB(2*lum_max-vitesse-i+5*seuil_luminosite,0,(2*lum_max-vitesse-i+5*seuil_luminosite)/2);}}//vert-cyan
  if((i>=6*seuil_luminosite)&&(i<150+6*seuil_luminosite)){for(byte k=0;k<4;k++){leds[couronnes[k+88]-1]=CRGB(i-6*seuil_luminosite,0,(i-6*seuil_luminosite)/10);}}//vert
  if((i>=(lum_max+6*seuil_luminosite))&&(i<(2*lum_max+6*seuil_luminosite))){for(byte k=0;k<4;k++){leds[couronnes[k+88]-1]=CRGB(2*lum_max-vitesse-i+6*seuil_luminosite,0,(2*lum_max-vitesse-i+6*seuil_luminosite)/10);}}//vert
  FastLED.show();
}

void led_win(byte count){                                                                          // Effectue la vague de LED's dans les deux sens, "count" fois d'affilées
  for(byte k=0;k<=count;k++){
    for(int i=0;i<2*lum_max+6*seuil_luminosite;i+=vitesse){led_vague(i);}
    for(int i=2*lum_max+6*seuil_luminosite;i>-vitesse;i-=vitesse){led_vague(i);}
  }
}

void led_loose(byte count){                                                                       // Les LEDs effectuent une respiration rouge
  for(byte k=0;k<=count;k++){
    for(int i=0;i<lum_max;i+=1){leds=CRGB(0,i,0);}
    for(int i=lum_max;i>-1;i-=1){leds=CRGB(0,i,0);}
  }
}

void deplacement_led(byte last_point,byte point){                                                 // La LED allumée passe de "last_point" à "point"
  if(last_point!=start_point){
    leds[last_point-1]=CRGB(0,0,0);}
  leds[point-1]=CRGB(20,20,150);
  FastLED.show();
}

void deplacement_impossible_led(byte point){                                                      // La LED allumée passe au rouge 400 ms et redevient bleue
  leds[point-1]=CRGB(10,150,10);
  FastLED.show();
  delay(400);
  leds[point-1]=CRGB(20,20,150);
  leds[start_point-1]=CRGB(150,20,20);
  FastLED.show();
}

void deplacement_snake_impossible(byte serpent[20]){                                              // Le serpent s'allume en rouge pendant 400 ms et puis redevient vert
  for(byte i=0;i<20;i++){
    leds[serpent[i]-1]=CRGB(10,150,10);}
  FastLED.show();
  delay(400);
  for(byte i=0;i<20;i++){
    leds[serpent[i]-1]=CRGB(150,0,0);}
  FastLED.show();
}

void deplacement_snake(byte serpent[20],byte pomme){                                              //  Le serpent avance dans la direction choisie
  leds=CRGB(0,0,0);
  leds[pomme-1]=CRGB(0,150,0);
  for(byte i=0;i<20;i++){
    leds[serpent[i]-1]=CRGB(150,0,0);}
  FastLED.show();
}

void lumos(){                                                                                     // Suite d'animations lumineuses
  btp2=0;
  anim=1;
  while(btp2!=1){                                                                                 // Tant que le bouton 2 n'a pas été appuyé (bouton de validation)
    btp1=digitalRead(BTP1_PIN);
    btp2=digitalRead(BTP2_PIN);
    leds=CRGB(0,0,0);
    while((btp1!=1)&&(btp2!=1)){                                                                  // Tant qu'aucun des deux boutons n'est appuyé
      if(anim==1){                                                                                // Animation 1
        for(int i=0;i<2*lum_max+6*seuil_luminosite;i+=vitesse){
          led_vague(i);
          if((btp1!=1)&&(btp2!=1)){btp1=digitalRead(BTP1_PIN);btp2=digitalRead(BTP2_PIN);}}
        for(int i=2*lum_max+6*seuil_luminosite;i>-vitesse;i-=vitesse){
          led_vague(i);
          if((btp1!=1)&&(btp2!=1)){btp1=digitalRead(BTP1_PIN);btp2=digitalRead(BTP2_PIN);}}}
      if(anim==2){                                                                                // Animation 2
        delay(500);
        for(int i=0;i<65;i+=1){leds=CRGB(i,i/2,i);FastLED.show();
          if((btp1!=1)&&(btp2!=1)){btp1=digitalRead(BTP1_PIN);btp2=digitalRead(BTP2_PIN);}
          delay(10);}
        for(int i=65;i>-1;i-=1){leds=CRGB(i,i/2,i);FastLED.show();
          if((btp1!=1)&&(btp2!=1)){btp1=digitalRead(BTP1_PIN);btp2=digitalRead(BTP2_PIN);}
          delay(10);}}}
    anim+=1;
    delay(1000);
    if(anim==3){anim=1;}}}
 
//**********Setup**********//

void led_setup(){                                                                                 // Initialise les LEDs
  FastLED.addLeds<WS2811,LED_PIN,COLOR_ORDER>(leds, NUM_LEDS);                                    // Indique quel contrôleur I²C est utilisé
  for(int i=0;i<2*lum_max+6*seuil_luminosite;i+=vitesse){                                         // Animation Lumineuse
    led_vague(i);
  }
}
