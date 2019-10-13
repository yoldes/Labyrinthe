
// ATTENTION! : Ne pas confondre la sélection, l'élement sur lequel se situe le curseur, et la validation, le fait d'appuyer sur le bouton "ok".

//**********Library**********//

#include "EEPROM.h"
#include <Adafruit_SH1106.h>

//**********Definitions**********//
 
#define OLED_RESET 4                                                                    // Créé l'objet "Display" correpondant à notre écran 
Adafruit_SH1106 Display(OLED_RESET); 

//**********Variables**********//                                                       // Définit les variables utiles qui ne sont pas importées de "EEPROM.h"

bool ok1,ok2;
byte btp1,BTP1_PIN=3,son=1,numero_jeu=1,niveau=1,charger=1,point;

//**********Setup**********//

void screen_setup(){                                                                    // Initialise l'écran
  Display.begin(SH1106_SWITCHCAPVCC , 0x3C);                                            // Indique quel écran est lié à l'objet "Display"
  Display.clearDisplay();                                                               // Efface l'écran ( permet d'annuler l'animation Adafruit par défaut )
  Display.setTextSize(2);                                                               //
  Display.setTextColor(WHITE,BLACK);                                                    //      Affiche "Welcome" au centre 
  Display.setCursor(20,20);                                                             //            de l'écran
  Display.print("Welcome");                                                             //
  Display.display();                                                                    //
  pinMode(BTP2_PIN,INPUT);                                                              // Définit le pin 3 de l'Arduino comme entrée correspondant au bouton 2
  pinMode(BTP1_PIN,INPUT);                                                              // Définit le pin 4 de l'Arduino comme entrée correspondant au bouton 1
}

//**********Loops**********//

void select_jeu(){                                                                      // Permet à l'utilisateur de sélectionner le numéro du jeu
  btp2=0;                                                                               // Définit le bouton 2 comme étant levé
  while(btp2!=1){                                                                       // Tant que le bouton 2 n'a pas été appuyé (bouton de validation)
    if(numero_jeu==1){                                                                  // Si le jeu égal 1 on affiche une première fenêtre de selection de 3 jeux (car on ne peut pas en afficher plus)
      Display.clearDisplay();Display.setTextSize(1);
      Display.setTextColor(WHITE,BLACK);                                      
      Display.setCursor(10,5);Display.print("Liste des jeux :");  
      Display.setCursor(10,20);Display.print("Libre");  Display.setCursor(10,35);
      Display.print("Labyrinthe");  Display.setCursor(10,50);Display.print("Snake");  
      Display.display();
      while((numero_jeu!=4)&&(btp2!=1)){                                                // Tant que le jeu ne dépasse pas 3, ou que la sélection n'est pas validée
                                                                                        // Le curseur "<" change de position en fonction du jeu sélectionné 
        if(numero_jeu==1){                                                             
          Display.setCursor(50,20);Display.print("<"); Display.setCursor(75,35);
          Display.print(" ");Display.setCursor(50,50);Display.print(" ");}
        if(numero_jeu==2){
          Display.setCursor(50,20);Display.print(" "); Display.setCursor(75,35);
          Display.print("<");Display.setCursor(50,50);Display.print(" ");}
        if(numero_jeu==3){
          Display.setCursor(50,20);Display.print(" "); Display.setCursor(75,35);
          Display.print(" ");Display.setCursor(50,50);Display.print("<");}
        Display.display();
        btp1=digitalRead(BTP1_PIN);                                                     // Lit l'état du bouton 1, le range dans la variable btp1
        btp2=digitalRead(BTP2_PIN);
        while((btp1!=1)&&(btp2!=1)){                                                    // Attend que l'un des deux boutons soit appuyé
          btp1=digitalRead(BTP1_PIN);
          btp2=digitalRead(BTP2_PIN);}
        if(btp1==1){numero_jeu+=1;}                                                     // Si le bouton appuyé est celui de sélection, la valeur du jeu augmente de un
        delay(200);}}
    if(numero_jeu==4){                                                                  // Si le jeu égal 4 on affiche une deuxième fenêtre de selection des jeux restants
      Display.clearDisplay();Display.setTextSize(1);
      Display.setTextColor(WHITE,BLACK);                                      
      Display.setCursor(10,5);Display.print("Liste des jeux :");  
      Display.setCursor(10,20);Display.print("Lumos");
      Display.setCursor(10,35);Display.print("Retour");  
      Display.display();
      while((numero_jeu!=1)&&(btp2!=1)){
        if(numero_jeu==4){
          Display.setCursor(50,20);Display.print("<");
          Display.setCursor(50,35);Display.print(" ");}
        if(numero_jeu==5){                                                              // La sélection du jeu 5 engendre le retour au menu précédent
          Display.setCursor(50,35);Display.print("<");
          Display.setCursor(50,20);Display.print(" ");}
        Display.display();
        btp1=digitalRead(BTP1_PIN);
        btp2=digitalRead(BTP2_PIN);
        while((btp1!=1)&&(btp2!=1)){
          btp1=digitalRead(BTP1_PIN);
          btp2=digitalRead(BTP2_PIN);}
        if(btp1==1){numero_jeu+=1;if(numero_jeu==6){numero_jeu=1;}}                     // Si le numéro du jeu atteint la valeur 6, on lui donne la valeur 1 permettant de repasser à la première page du menu
        delay(200);}}}}

void select_niveau(){                                                                   // Même fonctionnement que la procédure "select_niveau"
  btp2=0;
  while(btp2!=1){
    if(niveau==1){
      Display.clearDisplay();Display.setTextSize(1);Display.setTextColor(WHITE,BLACK);                                     
      Display.setCursor(10,5);Display.print("Liste des niveaux :");  
      Display.setCursor(10,20);Display.print("Niveau 1");Display.setCursor(10,35);
      Display.print("Niveau 2"); Display.setCursor(10,50);Display.print("Niveau 3");
      Display.display();
      while((niveau!=4)&&(btp2!=1)){
        if (niveau==1){
          Display.setCursor(60,20);Display.print("<");Display.setCursor(60,35);
          Display.print(" ");Display.setCursor(60,50);Display.print(" ");}
        if (niveau==2){
          Display.setCursor(60,35);Display.print("<");Display.setCursor(60,20);
          Display.print(" ");Display.setCursor(60,50);Display.print(" ");}
        if (niveau==3){
          Display.setCursor(60,50);Display.print("<");Display.setCursor(60,20);
          Display.print(" ");Display.setCursor(60,35);Display.print(" ");}
        Display.display();
        btp1=digitalRead(BTP1_PIN);
        btp2=digitalRead(BTP2_PIN);
        while((btp1!=1)&&(btp2!=1)){
          btp1=digitalRead(BTP1_PIN);
          btp2=digitalRead(BTP2_PIN);}
        if(btp1==1){niveau+=1;}
        delay(200);}}
    if(niveau==4){
      Display.clearDisplay();Display.setTextSize(1);
      Display.setTextColor(WHITE,BLACK);                                     
      Display.setCursor(10,5);Display.print("Liste des niveaux :");
      Display.setCursor(10,20);Display.print("Niveau 4");Display.setCursor(10,35);
      Display.print("Niveau 5"); Display.setCursor(10,50);Display.print("Retour");
      Display.display();
      while((niveau!=1)&&(btp2!=1)){
        if (niveau==4){
          Display.setCursor(60,20);Display.print("<");Display.setCursor(60,35);
          Display.print(" ");Display.setCursor(55,50);Display.print(" ");}
        if (niveau==5){
          Display.setCursor(60,35);Display.print("<");Display.setCursor(60,20);
          Display.print(" ");Display.setCursor(55,50);Display.print(" ");}
        if (niveau==6){                                                                 // La sélection du niveau 6 engendre le retour au menu précédent 
          Display.setCursor(55,50);Display.print("<"); Display.setCursor(60,20);
          Display.print(" ");Display.setCursor(60,35);Display.print(" ");} 
        Display.display();
        btp1=digitalRead(BTP1_PIN);
        btp2=digitalRead(BTP2_PIN);
        while((btp1!=1)&&(btp2!=1)){
          btp1=digitalRead(BTP1_PIN);
          btp2=digitalRead(BTP2_PIN);}
        if(btp1==1){niveau+=1;if(niveau==7){niveau=1;}}
        delay(200);}}}}

void nouvelle_partie(){                                                                 // Permet de choisir le numéro du jeu et le niveau d'une nouvelle partie
  niveau=6;                                                                             // Définit niveau égal à 6
  while(niveau==6){                                                                     // Exécute en boucle tant que le niveau est égal à 6 (permet de relancer la sélection des jeux si le niveau précédement sélectionné est 6)
    numero_jeu=1;niveau=1;
    select_jeu();                                                                       // Lance la procédure "select_jeu" ( BTP_Screen.h - Ligne 35 )
    if(numero_jeu==2){
      delay(200);
      select_niveau();}                                                                 // Lance la procédure "select_niveau" ( BTP_Screen.h - Ligne 87 )
    if(numero_jeu==5){ok1=false;}                                                       // "ok1" est la condition de sortie d'une boucle while dans la procédure "sélection" ( BTP_Screen.h - Ligne 189 )
    delay(200);}}

void charger_partie(){                                                                  // Charge la dernière partie en cours
  numero_jeu=readAddress(6000);                                                         // Prend la dernière valeur de "numéro_jeu" enregistrée dans l'EEPROM (car l'Arduino ne permet pas la sauvegarde)
  niveau=readAddress(6001);                                                             // Idem pour niveau
  point=readAddress(6002);                                                              // Idem pour point (correspond au numéro de la case où est le joueur sur le cube)
  if(numero_jeu==0){                                                                    // Si la dernière partie a été gagnée ou que c'est la première fois que le cube est allumé
    Display.clearDisplay();Display.setTextSize(1);                                      // Affiche "Pas de partie sauvegardee" au centre de l'écran
    Display.setCursor(22,22);Display.print("Pas de partie        sauvegardee");
    Display.display();
    delay(1000);
    nouvelle_partie();}}                                                                // Lance automatiquement le menu "nouvelle partie" ( BTP_Screen.h - Ligne 140 )

void parametres(){                                                                      // Permet de régler les paramètres du jeu (même structure que "select_jeu" ou "select_niveau")
  Display.clearDisplay();Display.setTextSize(1);Display.setTextColor(WHITE,BLACK);                                         
  Display.setCursor(10,5);Display.print("Parametres :");  
  Display.setCursor(10,20);Display.print("Son On");
  Display.setCursor(10,35);Display.print("Son Off");  
  Display.display();
  while(not ok2){                                                                       // Tant que le bouton "ok" n'est pas appuyé
    if (son==1){
      Display.setCursor(60,20);Display.print("<");
      Display.setCursor(60,35);Display.print(" ");}
    if (son==2){
      Display.setCursor(60,35);Display.print("<");
      Display.setCursor(60,20);Display.print(" ");}
    Display.display();
    btp1=digitalRead(BTP1_PIN);
    btp2=digitalRead(BTP2_PIN);
    while((btp1!=1)&&(btp2!=1)){
      btp1=digitalRead(BTP1_PIN);
      btp2=digitalRead(BTP2_PIN);}
    if(btp1==1){
      son+=1;
      if(son==3){son=1;}}
    if(btp2==1){ok2=true;}
    delay(200);}
  ok1=false;
  charger=1;}

void selection(){                                                                       // Permet de choisir entre "nouvelle partie", "charger partie" ou "paramètres" (même structure que "select_jeu" ou "select_niveau")
  ok1=false;
  while(not ok1){
    ok1=true;ok2=false;
    Display.clearDisplay();Display.setTextSize(1);Display.setTextColor(WHITE,BLACK);
    Display.setCursor(10,5);Display.print("Menu :");  
    Display.setCursor(10,20);Display.print("Nouvelle partie");Display.setCursor(10,35);
    Display.print("Charger partie");Display.setCursor(10,50);Display.print("Parametres");  
    Display.display();
    while(not ok2){
      if(charger==1){
        Display.setCursor(105,20);Display.print("<"); Display.setCursor(105,35);
        Display.print(" ");Display.setCursor(105,50);Display.print(" ");}
      if(charger==2){
        Display.setCursor(105,35);Display.print("<"); Display.setCursor(105,20);
        Display.print(" ");Display.setCursor(105,50);Display.print(" ");}
      if(charger==3){
        Display.setCursor(105,35);Display.print(" "); Display.setCursor(105,20);
        Display.print(" ");Display.setCursor(105,50);Display.print("<");}
      Display.display();
      btp1=digitalRead(BTP1_PIN);
      btp2=digitalRead(BTP2_PIN);
      while((btp1!=1)&&(btp2!=1)){
        btp1=digitalRead(BTP1_PIN);
        btp2=digitalRead(BTP2_PIN);}
      if(btp1==1){charger+=1;if(charger==4){charger=1;}}
      if(btp2==1){ok2=true;}
      delay(200);}
    ok2=false;
    if(charger==1){nouvelle_partie();}                                                  // Lance la procédure "nouvelle_partie" ( BTP_Screen.h - Ligne 140 )
    if(charger==2){charger_partie();}                                                   // Lance la procédure "charger_partie" ( BTP_Screen.h - Ligne 151 )
    if(charger==3){parametres();}}btp2=0;}                                              // Lance la procédure "paramètres" ( BTP_Screen.h - Ligne 162 )
