//**********Library**********//

#include <Wire.h>

//**********Variables**********//                                                                    // Définit les variables utiles.

byte mvt,btp2,BTP2_PIN=4;
long gyroX, gyroY, gyroZ;
float rotX, rotY, rotZ,X,Y,Z,seuilX=140,seuilY=140,seuilZ=140;

//**********Setup**********//

void gyro_setup(){                                                                                   // Initialise le gyroscope 
  Wire.begin();
  Wire.beginTransmission(0b1101000);                                                                 // Démarre la transimission avec le MPU (puce sur laquelle il y a le gyroscope)
  Wire.write(0x1B);                                                                                  // S'adresse au gyroscope
  Wire.write(0x00000000);                                                                            // Paramètre l'échelle totale du gyroscope, +/- 250deg/sec
  Wire.endTransmission();                                                                            // Termine la transimission avec le MPU
}

//**********Loops**********//

void gyro(){                                                                                         // Lecture des accélérations angulaires retournées par le gyroscope
  Wire.beginTransmission(0b1101000); 
  Wire.write(0x43);                                                                                  // Démarrage de la lecture de l'accélération angulaire
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6);                                                                     // Récéption des données
  while(Wire.available()<6);
  gyroX=Wire.read()<<8|Wire.read();                                                                  // Enregistre les deux premiers bytes dans gyroX
  gyroY=Wire.read()<<8|Wire.read();                                                                  // Enregistre les deux bytes du milieu dans gyroY
  gyroZ=Wire.read()<<8|Wire.read();                                                                  // Enregistre les deux derniers bytes dans gyroZ
  X=gyroX/131.0;
  Y=gyroY/131.0; 
  Z=gyroZ/131.0;
}

byte directions(byte face){                                                                          // Procédure qui retourne 8, 2, 4 ou 6 en fonction du mouvement et de la face sur laquelle se trouve le point
  X=0;Y=0;Z=0;
  while((X>-seuilX)&&(X<seuilX)&&(Y>-seuilY)&&(Y<seuilY)&&(Z>-seuilZ)&&(Z<seuilZ)&&(btp2!=1)){       // Tant qu'aucune accélération angulaire ne dépasse un seuil propre à chacun ou que le bouton est levé
    rotX=0;rotY=0;rotZ=0;
    for(byte k=0;k<=10;k++){                                                                         // Moyenne de dix valeurs
      gyro();
      rotX=rotX+X;rotY=rotY+Y;rotZ=rotZ+Z;
    }
    X=rotX/10;Y=rotY/10;Z=rotZ/10;
    if(btp2!=1){btp2=digitalRead(BTP2_PIN);}
    Serial.print(X);Serial.print("  ");Serial.print(Y);Serial.print("  ");Serial.println(Z);
  }
  Serial.print(X);Serial.print("  ");Serial.print(Y);Serial.print("  ");Serial.println(Z);
                                                                                                     // D'après le patron, on associe haut, bas, gauche, droite aux axes X,Y et Z du gyroscope
  if(face==0){      
    if(abs(X)>seuilX){return(0);}
    if(Y>seuilY){return(4);}
    if(Y<-seuilY){return(6);}
    if(Z>seuilZ){return(2);}
    if(Z<-seuilZ){return(8);}
  }
  if(face==1){
    if(abs(Y)>seuilY){return(0);}
    if(X>seuilX){return(6);}
    if(X<-seuilX){return(4);}
    if(Z>seuilZ){return(2);}
    if(Z<-seuilZ){return(8);}
  }
  if(face==2){
    if(abs(X)>seuilX){return(0);}
    if(Y>seuilY){return(6);}
    if(Y<-seuilY){return(4);}
    if(Z>seuilZ){return(2);}
    if(Z<-seuilZ){return(8);}
  }
  if(face==3){
    if(abs(Z)>seuilZ){return(0);}
    if(X>seuilX){return(4);}
    if(X<-seuilX){return(6);}
    if(Y>seuilY){return(8);}
    if(Y<-seuilY){return(2);}
  }
  if(face==4){
    if(abs(Y)>seuilY){return(0);}
    if(Z>seuilZ){return(2);}
    if(Z<-seuilZ){return(8);}
    if(X>seuilX){return(4);}
    if(X<-seuilX){return(6);}
  }
  if(face==5){
    if(X>seuilX){return(4);}
    if(X<-seuilX){return(6);}
    if(abs(Z)>seuilZ){return(0);}
    if(Y>seuilY){return(2);}
    if(Y<-seuilY){return(8);}
  }
}
