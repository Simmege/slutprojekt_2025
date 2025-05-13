/*
Fil:slutprojekt_maltavla_2025
Författare: Simon Erlén(Cesar)
Datum: 2025-05-13

Beskrivning: Detta program tar in en analog signal från två ljussensorer(light dependent resistor) och skriver om den till ett värde mellan 0 och 100.
Detta görs i funktionerna intervall1, respektive intervall2. 
Värdet mellan 0 till 100 åker sedan in i resultat-funktionen som ger än olika mycket poäng beroende på hur stark träffen (med laserpistolen) är. Det sista som händer är en timer som kör funktionen
startaOm, som skriver ut hur mycket poäng man fick, eller att ens skott tar slut, och även då startas programmet om. 



*/ 
#include "U8glib.h"
// biblioteket till skärmen inkluderas
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);// objekt ill oled-skärmen skapas



const int ldrPort1 = A0;
const int ldrPort2 = A1;
const int knappPort = 7;
const int bytesTid = 5000;

int poang = 0;

int antalSkott = 3;
// globala variabler skapas

void setup() {
  pinMode(ldrPort1, INPUT);
  pinMode(ldrPort2, INPUT);
  pinMode(knappPort, INPUT);
  // deklaration av analoga och digitala portar på arduinot

  u8g.setFont(u8g_font_unifont);
  // inställning av typsnitt till skärmen
}

void loop() {
  resultat();
}

/*
Lagrar den analoga signalen från ldrPort1(ljussensorn) i den lokala variablen ldrStatus1
och skriver om den til ett värde mellan 100 och 0.
Retunerar det omskrivna värdet.
*/
int intervall1() {
  int ldrStatus1 = analogRead(ldrPort1);
  return map(ldrStatus1, 0, 1023, 100, 0); 
}
/
*Lagrar den analoga signalen från ldrPort1(ljussensorn) i den lokala variablen ldrStatus1
och skriver om den til ett värde mellan 100 och 0.
Retunerar det omskrivna värdet.
*/
int intervall2() {
  int ldrStatus2 = analogRead(ldrPort2);
  return map(ldrStatus2, 0, 1023, 100, 0);
}
/*
Skriver om värdet man får från intervallfuntionerna till poäng som beror på hur stark träff man får med pistolen på ljussensorn.
Håller också koll på hur många skott som man har kvar, och ser till när programmet ska startas om. 
*/
int resultat() {
  int skottTid = millis();//deklarerar en lokal variabel som lagrar antalet millesekunder det har gått sedan koden kördes

  oledWrite(String(poang));// gör om varianblen poang till en sträng och skriver sedan ut den till oled-skärmen
  if (antalSkott != 0) {
    if (intervall1() > 90) {
      poang = poang + 100;
      antalSkott--;
      oledWrite(String(poang));

    } else if (intervall1() >= 50) {
      poang = poang + 50;
      antalSkott--;
      oledWrite(String(poang));
    } else if (intervall1() >= 20) {
      poang = poang + 10;
      antalSkott--;
      oledWrite(String(poang));
    }
    if (intervall2() > 90) {
      poang = poang + 100;
      antalSkott--;
      oledWrite(String(poang));

    } else if (intervall2() >= 50) {
      poang = poang + 50;
      antalSkott--;
      oledWrite(String(poang));
    } else if (intervall2() >= 20) {
      poang = poang + 10;
      antalSkott--;
      oledWrite(String(poang));
    }
  }else{
    oledWrite("Du fick" + String (poang) + "poang");
    delay(bytesTid);
    int poang = 0;
    
  }if(skottTid > 10000){
    startaOm();
  }
}
/*
Skriver ut en sträng på en oled-skärm
Argument: String text, strängen som skrivs ut

*/
void oledWrite(String text) {

  u8g.firstPage(); // rensar skärmen

  do {

    u8g.drawStr(0, 36, text.c_str());//skriver ut strängen

  } while (u8g.nextPage());
}
/*
Skapar en fördröjning i programmet och startar sedan om det
*/
void startaOm(){
  oledWrite("Tiden är ute");
  delay(2000);
  oledWrite("Totalpoang:" + String(poang));
  delay(2000);
  asm volatile (" jmp 0"); // Kör koden från början igen
}

