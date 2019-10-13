int TONE_PIN=5;

void son_selection(){
  tone(TONE_PIN,600,20);
  delay(20);}

void son_validation(){
  tone(TONE_PIN,600,20);
  delay(20);
  tone(TONE_PIN,800,20);
  delay(20);
}

void son_win(){
  tone(TONE_PIN,800,100);
  delay(100);
  tone(TONE_PIN,1000,100);
  delay(100);
  tone(TONE_PIN,1200,100);
  delay(100);
  tone(TONE_PIN,1600,200);
  delay(250);
  tone(TONE_PIN,1200,100);
  delay(100);
  tone(TONE_PIN,1600,200);
  delay(250);
}
