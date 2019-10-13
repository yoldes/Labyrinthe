 //**********Library**********//

#include "Labyrinthe.h"

//**********Variables**********//

byte longueur,pomme;
byte serpent1[20]={100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100};
byte serpent2[20]={100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100};

//**********Setup**********//

void setup_snake(){
  randomSeed(analogRead(0));
  serpent1[0]=83;
  leds=CRGB(0,0,0);
  leds[serpent1[0]-1]=CRGB(150,0,0);
  FastLED.show();
}

//**********Loops**********//

void snake(){
  longueur+=1;
  pomme=random(1,93);
  Serial.println(pomme);
  leds[pomme-1]=CRGB(0,150,0);FastLED.show();
  while(serpent1[0]!=pomme){
    for(byte k=0;k<20;k++){serpent2[k]=serpent1[k];}
    face=numero_face(serpent1[0]);
    mvt=directions(face);
    serpent1[0]=mouvement();
    Serial.println(serpent1[0]);
    if(serpent1[0]==serpent2[1]){
      deplacement_snake_impossible(serpent1);
      Serial.println("non");
    }
    if(serpent1[0]==0){
      deplacement_snake_impossible(serpent1);
      Serial.println("non");
    }
    else{
      for(byte k=0;k<longueur;k++){serpent1[k+1]=serpent2[k];}
      deplacement_snake(serpent1,pomme);
      Serial.println("oui");
    }
  }
}
