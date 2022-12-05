/* --------------------PROGRAM PRO SEEEDKIT, OLED displej--------------------
 * Program sloužící k pochopení základů programování
 * INTERKATIVNÍ ČÁSTI PROGRAMU JSOU OKOMENTOVÁNY ZAČÁTKEM "HRAJ SI"
 * Napsal René Valenta, 12/2022
 */

// nahrání knihovny funkcí (v tomto případě Arduino SensorKit)
#include <Arduino_SensorKit.h>

// deklarace (vytvoření) proměnné buttonpin s číslem 4

// nejčastější proměnné do začátku jsou: int, float, String, bool
// int = přirozené číslo, float = nepřirozené číslo (desetinné)
// String = text, bool = True/False (pravda/nepravda)
// jedná se o číslo digitálního vstupu tlačítka,
// které uložíme do paměti pod název "buttonpin"
int buttonpin = 4;

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
}

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
  Oled.println("displeje OLED.");
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

    // switch znamená "přepínač", který vyhodnocuje stavy
    // zde vyhodnocuje stav digitalRead(buttonpin), neboli
    // stav tlačítka (HIGH/LOW - nestisklé/stisklé)
    switch (digitalRead(buttonpin)) {

      // pokud bude nestisklé (HIGH), provede
      // to, co jsme funkci napsali (tiskne zadaný parametr)
      case HIGH:
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
        Oled.println("pro opakovani:");
        
      // pokud bude stisknuto, přeruší chod a začne znovu
      // (samostatný příkaz break restartuje cyklus)
      case LOW:
        break;
    }
  }
}

// počáteční funkce loop(), která se jako první spustí
// po zapnutí Arduina, načtení proměnných a spuštění funkce setup()
// zde nám po spuštění jednou spustí úvodní funkci,
// a poté pokračuje interaktivní, která běží až do vypnutí
void loop() {
  oledIntroduction();

  // HRAJ SI - zde zadej obsah jaký chceš (dej pozor, maximum znaků pro řádek je 16)
  oledInteractive("Tvuj text");
}
