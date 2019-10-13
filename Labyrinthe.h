 //**********Library**********//

#include "LED_s.h"

//**********Variables**********//                                           // Définit les variables utiles qui ne sont pas importées de "LED_s.h"

bool gagner;  
byte face=5,last_face;

//**********Setup**********//

void setup_game1(){                                                         // Initialisation du jeu, affichage des cases de départ et d'arrivée
  if(niveau==0){start_point=88;end_point=100;}
  if(niveau==1){start_point=89;end_point=88;}
  if(niveau==2){start_point=92;end_point=85;}
  if(niveau==3){start_point=88;end_point=82;}
  if(niveau==4){start_point=83;end_point=91;}
  if(niveau==5){start_point=86;end_point=81;}
  leds=CRGB(0,0,0);
  leds[start_point-1]=CRGB(150,20,20);
  leds[end_point-1]=CRGB(20,150,20);
  if(charger!=2){point=start_point;}
  else{leds[point-1]=CRGB(20,20,150);}
  FastLED.show();
}

//**********Loops**********//

byte numero_face(byte point){                                               // Fonction retournant le numéro de la face sur laquelle se trouve le point
  return((point-1)/16);
}

byte mouvement(){                                                           // Lit le numéro du point dans l'EEPROM en fonction du mouvement effectué
  if(mvt==8){point=readAddress(92*4*niveau+4*(last_point-1));}              //
  if(mvt==2){point=readAddress(92*4*niveau+4*(last_point-1)+1);}            //      Pour le patron du cube déplié, les directions haut, bas, gauche, droite sont les mêmes pour toutes les faces (cf patron des solutions)
  if(mvt==4){point=readAddress(92*4*niveau+4*(last_point-1)+2);}            //                  Les positions haut, bas, gauche, droite correspondent respectivement aux chiffres 8,2,4,6 sur un pavé numérique
  if(mvt==6){point=readAddress(92*4*niveau+4*(last_point-1)+3);}            //
  if(mvt==0){point=0;}
  return(point);
}

void game1(){                                                               // Procédure pour un déplacement du jeu "labyrinthe" et "libre"
  delay(350);
  last_face=face;
  face=numero_face(point);                                                  // Lance la procédure "numero_face" ( Labyrinthe.h - Ligne 29 )
  if(face!=last_face){delay(450);}                                          // En cas de changement de face, délai de 450ms pour permettre de tourner le cube  
  mvt=directions(face);                                                     // Lance la procédure "directions" ( gyro.h - Ligne 41 )
  last_point=point;
  point=mouvement();                                                        // Lance la procédure "mouvement" ( Labyrinthe.h - Ligne 33 )
  if(point==0){                                                             // Si le mouvement est impossible
    point=last_point;                                                       
    deplacement_impossible_led(point);                                      // Lance la procédure "deplacement_impossible_led" ( LEDs.h - Ligne 70 )
  }
  else{deplacement_led(last_point,point);}                                  // Lance la procédure "deplacement_led" ( LEDs.h - Ligne 63 )
  if(point==end_point){gagner=1;}
  Serial.println(point);
  writeAddress(6002,point);                                                 // Sauvegarde dans l'EEPROM le numéro du point
}
