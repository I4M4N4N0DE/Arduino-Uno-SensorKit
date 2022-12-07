/* --------------------PROGRAM PRO SEEEDKIT, ukázka chodu--------------------
 * Program sloužící k pochopení základů programování
 * komentáře jsou vždy texty začínající s //
 * Program doporučuji pro správné pochopení číst posloupně, 
 * a to podle částí (PRVNÍ - SEDMÁ) - jsou PROMÍCHANÉ!!!
 * INTERKATIVNÍ ČÁSTI PROGRAMU JSOU OKOMENTOVÁNY ZAČÁTKEM "HRAJ SI"
 * Napsal René Valenta, 12/2022
 */

//--------------PRVNÍ ČÁST--------------//
// nahrání knihoven funkcí 
// knihovna SensorKit pro OLED displej
#include <Arduino_SensorKit.h>

// deklarace (vytvoření) proměnné buttonpin s číslem 4

// nejčastější proměnné do začátku jsou: int, float, String, bool
// int = přirozené číslo, float = nepřirozené číslo (desetinné)
// String = text, bool = True/False (pravda/nepravda)
// jedná se o číslo digitálního vstupu tlačítka,
// které uložíme do paměti pod název "buttonpin"
int buttonpin = 4;

// to samé pro LED diodu
int ledpin = 6;

// to samé pro bzučák
int buzzerpin = 5;

// deklarace proměnných frekvencí bzučáku pod názvy not
int NOTE_G3 = 196;
int NOTE_A3 = 220;
int NOTE_B3 = 247;
int NOTE_C4 = 262;

// deklarace posloupnosti tónů
int melodie[] = {
   NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// deklarace posloupnosti trvání tónů (vteřiny)
int trvaniMelodie[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

//--------------DRUHÁ ČÁST--------------//
// funkce setup()
// funkce začínají vždy jako "void" (tzn. funkce) a poté její název zakončen uzavřenou závorkou
// každá funkce je ohraničena kroucenou závorkou (od názvu až po její konec)
// tím se rozlišují jednotlivé části programu (procesy)
// tato funkce nastavuje všechny komunikace, moduly a vstupy/výstupy
void setup() {

  // zahájení sériové komunikace s OLED displejem
  Oled.begin();

  // nastavení naklopení displeje
  Oled.setFlipMode(true);

  // nastavení tlačítka (digitálního pinu) jako vstupu
  // vstup je nastaven jako PULLUP, tudíž pro Arduino: nestisklý = HIGH, stisklý = LOW
  // použita je zde naše proměnná buttonpin, jinak by zde bylo číslo 4
  pinMode(buttonpin, INPUT_PULLUP);

  // to samé pro LED diodu, OUTPUT = výstup
  pinMode(ledpin, OUTPUT);
}

//--------------SEDMÁ ČÁST--------------//
// funkce melodik()
// opět běží smyčka while (true), a to kvůli stálé
// kontrole stavu tlačítka - kdyby nebyla ve smyčce,
// ihned by zapomněla jeho stav a vůbec by se nespustila
void melodik() {

while (true) {

  // pokud bude stav tlačítka stisklý, provede úkon co zadáme
  if (digitalRead(buttonpin) == HIGH) {

      // cyklus FOR
      // cyklus FOR je odlišný od cyklu WHILE tím, že u něj známe přesné parametry
      // víme totiž na jaké hodnotě začne, na jaké skončí a jak bude posloupně postupovat
      // (zda bude inkrementovat (zvyšovat hodnotu), nebo dekrementovat (snižovat hodnotu)
      // zde zavádíme začátek na deklarované proměnné ton = 0,
      // druhý zápis určuje konec cyklu (jakmile bude ton = 8),
      // poslední zápis ton++ říká, že inkrementujeme
      for (int ton = 0; ton < 8; ton++) {

        // ihned pod cyklem for je v závorce vše, co pro každý prvek dané posloupnosti udělá
        // zavede pro každý prvek proměnnou dobatonu, což 1000 děleno (/) prvkem ton v seznamu trvaniMelodie[]
        int dobatonu = 1000 / trvaniMelodie[ton];
        
        // výsledek vynásobí 1.30, a to uloží pod proměnnou spozdeni (čas mezi tóny)
        int spozdeni = dobatonu * 1.30;

        // metodou tone() pošle do výstupu buzzerpin tón ze seznamu tónů, který potrvá určitou dobu
        // tato doba je brána ze seznamu trvaniMelodie[]
        tone(buzzerpin, melodie[ton], trvaniMelodie);

        // vyčká konkrétní prodlevu
        delay(spozdeni);

        // vypne výstup na buzzerpin
        noTone(buzzerpin);
      }
      if (digitalRead(buttonpin) == LOW) {
        // HRAJ SI - zde zadej obsah jaký chceš (dej pozor, maximum znaků pro řádek je 16)
        oledInteractive("Peter Podoba");
      }
  }
}
}

//--------------ŠESTÁ ČÁST--------------//
// funkce LEDshow
// spouštící cyklus zjišťující stav tlačítka 
// a obsahující blikající sekvenci
void LEDshow() {

  // cyklus while (true) znamená, že se opakuje donekonečna,
  // pokud není přerušen
  while (true) {

    // pokud bude stav tlačítka stisklý, provede úkon co zadáme
    if (digitalRead(buttonpin) == HIGH) {

        // pošle na výstup LED diody HIGH (tj. logická 1, +5V)
        digitalWrite(ledpin, HIGH);

        // vyčká půl vteřiny
        delay(500);

        // pošle na výstup LOW (tj. logická 0, vypne napájení)
        digitalWrite(ledpin, LOW);
        delay(500);
        digitalWrite(ledpin, HIGH);
        delay(500);
        digitalWrite(ledpin, LOW);
        delay(500);
        digitalWrite(ledpin, HIGH);
        delay(500);
        digitalWrite(ledpin, LOW);
        delay(500);
        digitalWrite(ledpin, HIGH);
        delay(500);
        digitalWrite(ledpin, LOW);
        delay(500);

        Oled.clearDisplay();
        Oled.setFont(u8x8_font_chroma48medium8_r);
        Oled.setCursor(0,2);
        Oled.println("Stiskni knoflik");
        Oled.setCursor(0,3);
        Oled.println("pro melodii,");
        Oled.setCursor(0,4);
        Oled.println("nebo resetuj.");
        delay(1000);
        
        // zde již nepotřebujeme přerušovat cyklus, nýbrž jen spustit funkce
        // proto zde nemáme switch/case, ale jednoduchou podmínku if = pokud
        // pokud bude stav tlačítka stisklý, provede úkon co zadáme
        if (digitalRead(buttonpin) == LOW) {

          // spustí melodickou funkci
          melodik();
        }
  }
  }
}

//--------------ČTVRTÁ ČÁST--------------//
// funkce oledIntroduction
// funkce spouštící primitivní úvod
void oledIntroduction() {

  // nastavení fontu písma
  Oled.setFont(u8x8_font_chroma48medium8_r);

  // nastavení kurzoru textu (osa x-počáteční znak v řádku,osa y-řádek)
  // počet znaků na řádku je 16, počet řádků je 8, číslovaných logicky - tedy 0-7
  Oled.setCursor(0,0);

  // vytištění textu (musíme hlídat počet znaků)
  Oled.println("Ahoj :-)");

  // vyčká 2 sekundy (2000 milisekund)
  delay(2000);

  // dál pokračujeme stejně, pouze měníme řádky
  // a tiskneme nové texty
  Oled.setCursor(0,1);
  Oled.println("Vitej v ukazce");
  Oled.setCursor(0,2);
  Oled.println("SensorKitu.");
  delay(3000);
  Oled.setCursor(0,3);
  Oled.println("Displej vypise");
  Oled.setCursor(0,4);
  Oled.println("text, ktery");
  Oled.setCursor(0,5);
  Oled.println("mu zadas.");
  delay(4000);
  Oled.clearDisplay();
  Oled.setCursor(0,2);
  Oled.println("Stiskni knoflik");
  Oled.setCursor(0,3);
  Oled.println("pro tisk:");
}

//--------------PÁTÁ ČÁST--------------//
// HRAJ SI - funkce oledInteractive
// v závorce funkce máme deklarovanou textovou proměnnou content
// tato proměnná je parametr funkce, což je libovolná proměnná,
// kterou použijeme v dané funkci jak chceme, a poté
// když funkci spustíme kdekoliv jinde, do její závorky
// napíšeme obsah, který bude tato proměnná mít
// tím funkce provede svůj úkon s daty, které jí předložíme
void oledInteractive(String content) {

  // cyklus while (true) znamená, že se opakuje donekonečna,
  // pokud není přerušen
  while (true) {

    // pokud bude stav tlačítka stisklý, provede úkon co zadáme
    if (digitalRead(buttonpin) == HIGH) {
      
        // smaže obsah
        Oled.clearDisplay();
        Oled.setFont(u8x8_font_chroma48medium8_r);
        Oled.setCursor(0,0);
        Oled.println(content);
        delay(1000);
        Oled.setCursor(0,1);
        Oled.println(content);
        delay(1000);
        Oled.setCursor(0,2);
        Oled.println(content);
        delay(1000);
        Oled.setCursor(0,3);
        Oled.println(content);
        delay(1000);
        Oled.setCursor(0,4);
        Oled.println(content);
        delay(1000);
        Oled.setCursor(0,5);
        Oled.println(content);
        delay(1000);
        Oled.setCursor(0,6);
        Oled.println(content);
        delay(1000);
        Oled.setCursor(0,7);
        Oled.println(content);
        delay(1000);
        Oled.clearDisplay();
        Oled.setCursor(0,0);
        Oled.println("Stiskni knoflik");
        Oled.setCursor(0,1);
        Oled.println("pro LEDku.");
        Oled.setCursor(0,2);
        Oled.println("Restartujes");
        Oled.setCursor(0,3);
        Oled.println("zlutym knoflem");
        Oled.setCursor(0,4);
        Oled.println("u portu.");
        if (digitalRead(buttonpin) == LOW) {
           // pokud bude stisknuto, zapne LEDshow
           LEDshow();
        }
      }
  }
}

//--------------TŘETÍ ČÁST--------------//
// počáteční funkce loop(), která se vžsy jako první spustí
// po zapnutí Arduina, načtení proměnných a spuštění funkce setup()
// zde nám po spuštění jednou spustí úvodní funkci,
// a poté pokračuje interaktivní, která běží až do vypnutí
void loop() {
  oledIntroduction();

  // HRAJ SI - zde zadej obsah jaký chceš (dej pozor, maximum znaků pro řádek je 16)
  oledInteractive("Peter Podoba");
}
