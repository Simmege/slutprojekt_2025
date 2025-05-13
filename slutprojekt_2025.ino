/*Fil:slutprojekt_maltavla_2025
Författare: Simon Erlén
Datum: 2025-05-13

Brskrivning: Detta programm aktiverar en laserstråle och en liten högtalare varje gång en knapp trycks ned. 
Det håller också koll på och skriver ut hur många skott som har avfyrats(lasern ska fungera en pisol) 
*/

#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);// objekt ill oled-skärmen skapas


const int knappPort = 3;
const int laserPort = 4;
const int skjutTid = 250;
const int ljudPort = 5;
const int bytTid = 3000;
int toner[] = { 22050, 22050, 10000, 15000, 9000, 4000, 2000, 1000, 500, 200, 30 };
int skott = 3;

// globala variabler skapas

void setup() {
  pinMode(knappPort, INPUT);
  pinMode(laserPort, OUTPUT);
  pinMode(ljudPort, OUTPUT);
  //deklaration av digitala portar på arduinot
  u8g.setFont(u8g_font_unifont);
}// inställning av typsnitt till skärmen

void loop() {
  skjut();
  antalSkott();



 
}
/*
Räknar antal skott som har avfyrats och sriver ut det på oled-skärmen
*/
void antalSkott(){
 if (skott == 3) {
    oledWrite("Du har 3 skott", "kvar");
  } else if (skott == 2) {
    oledWrite("Du har 2 skott", "kvar");
  } else if (skott == 1) {
    oledWrite("Du har 1 skott", "kvar");
  } else if (skott == 0) {
    oledWrite("Nasta persons", "tur");
    delay(bytTid);
    skott=3;
  }
}

/*
Avfyrar lasern och spelar upp ljudet till högtalaren i fall knappen trycks ner.
*/
void skjut() {
  if (digitalRead(knappPort)) {
    digitalWrite(laserPort, HIGH);
    delay(skjutTid);
    digitalWrite(laserPort, LOW);
    
    skott -= 1;
    for (int i = 0; i < 10; i++) {// en loop som spelar upp alla noter i listan som kallas noter
      tone(5, toner[i]);
      delay(20);
    }
    while (digitalRead(knappPort)) {}
  } else {
    noTone(5);//Inget spelas i högtalaren
  }
}





/*Skriver ut två strängar på oledskärmen på olika höjder.
Argument1: Srting text1, den övre strängen som skrivs ut
Argument2: String text2, den undre strängen som skrivs ut
*/
void oledWrite(String text1, String text2) {

  u8g.firstPage();//Rensar sjärmen

  do {

    u8g.drawStr(0, 20, text1.c_str());//Skriver ut den första strängen
    u8g.drawStr(0, 36, text2.c_str());//Skriver ut den andra strängen

  } while (u8g.nextPage());
}
