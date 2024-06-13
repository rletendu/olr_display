#include <FastLED.h>        //https://github.com/FastLED/FastLED
#include <LEDMatrix.h>      //https://github.com/Jorgen-VikingGod/LEDMatrix


#define DATA_PIN            13         // Sortie sur laquelle le Din de la matrice est connecté
#define COLOR_ORDER         GRB       // Type de code à envoyer pour les WS2812B
#define CHIPSET             WS2812B   // Type de LEDs du bandeau

// initial matrix layout (to get led strip index by x/y)
#define MATRIX_WIDTH        16
#define MATRIX_HEIGHT       16
#define MATRIX_TYPE         HORIZONTAL_ZIGZAG_MATRIX
#define MATRIX_SIZE         (MATRIX_WIDTH*MATRIX_HEIGHT)
#define NUMPIXELS           MATRIX_SIZE

cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;

#define pause 300


// https://gitlab.com/open-led-race/olr-arduino/-/blob/master/doc/OLR_Protocol_Serial.pdf
int carNumber = 0;
int toursComplets = 0;
int pourcentageTour = 0;


void processRx(String data);
void countDown() ;
void dispRaceInfo(int numeroVoiture, int toursComplets, int pourcentageTour) ;
void dispWinner(String data) ;


void setup()
{
  Serial.begin(9600);
  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds[0], leds.Size()).setCorrection(TypicalSMD5050);
  FastLED.setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(200);
  FastLED.clear(true);  // on éteint toutes les LEDs

  countDown();
  

  dispRaceInfo(1, 3, 75);
  dispRaceInfo(2, 3, 75);
  dispRaceInfo(3, 2, 50);
  dispRaceInfo(4, 4, 25);
  delay(2000);
  dispWinner("w1");
  /*
  leds.DrawFilledRectangle(0, 0, 15, 15, (CRGB::White));
  FastLED.show();
*/

}


void loop() {
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    Serial.print("\n");
    Serial.print(data);
    Serial.print("\n");
    if (data.startsWith("T")) {
      // Analyse des données sur les voitures et les tours
      processRx(data);
    } else if (data.startsWith("R4")) {
      // Compte à rebours avant la course
      countDown();
      // Serial.print("C_A_R\n");
    } else if (data.startsWith("w")) {
      // Course terminée, affichage du gagnant
      dispWinner(data);
      // Serial.print("WIN\n");
      // afficherGagnant(data);

    }
  }

}

void processRx(String data) {
  String donnees = "";
  donnees = data.substring(2);

  // Trouver l'index de 'p' dans la chaîne de caractères
  int indexp = donnees.indexOf("p");

  // Trouver l'index de 'M' dans la chaîne de caractères
  int indexM = donnees.indexOf("M");

  // Trouver l'index de la première virgule dans la chaîne de caractères
  int indexVirgule1 = donnees.indexOf(",");

  // Trouver l'index de la deuxième virgule dans la chaîne de caractères
  int indexVirgule2 = donnees.indexOf(",", indexVirgule1 + 1);

  // Extraire le numéro de voiture de la chaîne de caractères et le convertir en entier
  int numeroVoiture = donnees.substring(indexp + 1, indexM).toInt();

  // Extraire le nombre de tours complets de la chaîne de caractères et le convertir en entier
  int toursComplets = donnees.substring(indexM + 1, indexVirgule1).toInt();

  // Extraire le pourcentage du tour de la chaîne de caractères et le convertir en entier
  int pourcentageTour = donnees.substring(indexVirgule1 + 1, indexVirgule2).toInt();

   Serial.print("Voiture : ");
   Serial.print(numeroVoiture);
   Serial.print("\n");
   Serial.print("Tours effectués : ");
   Serial.print(toursComplets); 
   Serial.print("\n");
   Serial.print("Tour en cours : ");
   Serial.print(pourcentageTour);
   Serial.print("\n");


  dispRaceInfo(numeroVoiture, toursComplets, pourcentageTour);

}

void dispWinner(String data) {
  // Afficher le gagnant sur la matrice LED
  if (data.startsWith("w1")) {
    // Voiture 1 gagne (rouge)
    leds.DrawFilledRectangle(0, 0, 15, 15, (CRGB::Red));
  } else if (data.startsWith("w2")) {
    // Voiture 2 gagne (vert)
    leds.DrawFilledRectangle(0, 0, 15, 15, (CRGB::Green));
  } else if (data.startsWith("w3")) {
    // Voiture 3 gagne (bleu)
    leds.DrawFilledRectangle(0, 0, 15, 15, (CRGB::Blue));
  } else if (data.startsWith("w4")) {
    // Voiture 4 gagne (vert)
    leds.DrawFilledRectangle(0, 0, 15, 15, (CRGB::White));
  }
  FastLED.show();
  Serial.print(data);
  Serial.print("Le gagnant est : \n");

  delay(pause);

}

void countDown() {
  // 3
    leds.DrawFilledRectangle(0, 0, 15, 15, (CRGB::Gray));
    leds.DrawFilledRectangle(5, 12, 11, 4, (CRGB::Orange));
    leds.DrawLine(6, 13, 10, 13, (CRGB::Black));
    leds.DrawPixel(5, 12, (CRGB::Black));
    leds.DrawPixel(11, 12, (CRGB::Black));
    leds.DrawLine(4, 11, 4, 8, (CRGB::Black));
    leds.DrawLine(12, 11, 12, 3, (CRGB::Black));
    leds.DrawLine(5, 7, 6, 7, (CRGB::Black));
    leds.DrawLine(4, 6, 4, 3, (CRGB::Black));
    leds.DrawPixel(5, 2, (CRGB::Black));
    leds.DrawPixel(11, 2, (CRGB::Black));
    leds.DrawLine(6, 1, 10, 1, (CRGB::Black));
    leds.DrawFilledRectangle(5, 9, 6, 8, (CRGB::Maroon));
    leds.DrawFilledRectangle(7, 10, 7, 9, (CRGB::Maroon));
    leds.DrawPixel(8, 10, (CRGB::Maroon));
    leds.DrawPixel(5, 4, (CRGB::Maroon));
    leds.DrawLine(5, 3, 11, 3, (CRGB::Maroon));
    leds.DrawLine(6, 2, 10, 2, (CRGB::Maroon));
    leds.DrawLine(10, 8, 11, 8, (CRGB::Maroon));
    leds.DrawLine(7, 6, 8, 6, (CRGB::Maroon));
    FastLED.show();
    delay(2000);

  // 2
    leds.DrawFilledRectangle(0, 0, 15, 15, (CRGB::Gray));
    leds.DrawFilledRectangle(5, 12, 11, 4, (CRGB::Orange));
    leds.DrawLine(6, 13, 10, 13, (CRGB::Black));
    leds.DrawPixel(5, 12, (CRGB::Black));
    leds.DrawPixel(11, 12, (CRGB::Black));
    leds.DrawLine(4, 11, 4, 8, (CRGB::Black));
    leds.DrawLine(12, 11, 12, 2, (CRGB::Black));
    leds.DrawPixel(5, 7, (CRGB::Black));
    leds.DrawLine(4, 6, 4, 2, (CRGB::Black));
    leds.DrawLine(5, 1, 11, 1, (CRGB::Black));
    leds.DrawFilledRectangle(5, 9, 6, 8, (CRGB::Maroon));
    leds.DrawFilledRectangle(7, 10, 7, 9, (CRGB::Maroon));
    leds.DrawPixel(8, 10, (CRGB::Maroon));
    leds.DrawLine(5, 3, 11, 3, (CRGB::Maroon));
    leds.DrawFilledRectangle(5, 3, 11, 2, (CRGB::Maroon));
    leds.DrawLine(10, 7, 11, 7, (CRGB::Maroon));
    leds.DrawLine(9, 6, 11, 6, (CRGB::Maroon));
    FastLED.show();
    delay(2000);

  // 1
    leds.DrawFilledRectangle(0, 0, 15, 15, (CRGB::Gray));
    leds.DrawFilledRectangle(7, 12, 11, 4, (CRGB::Orange));
    leds.DrawLine(8, 13, 10, 13, (CRGB::Black));
    leds.DrawPixel(7, 12, (CRGB::Black));
    leds.DrawLine(11, 12, 11, 2, (CRGB::Black));
    leds.DrawLine(6, 11, 6, 8, (CRGB::Black));
    leds.DrawLine(8, 1, 10, 1, (CRGB::Black));
    leds.DrawLine(7, 7, 7, 2, (CRGB::Black));
    leds.DrawFilledRectangle(8, 3, 10, 2, (CRGB::Maroon));
    leds.DrawLine(7, 9, 7, 8, (CRGB::Maroon));
    FastLED.show();
    delay(2000);

  // Go !
    leds.DrawFilledRectangle(0, 0, 15, 15, (CRGB::Yellow));
    leds.DrawFilledRectangle(1, 11, 2, 3, (CRGB::Black));
    leds.DrawLine(2, 12, 5, 12, (CRGB::Black));
    leds.DrawLine(5, 11, 6, 11, (CRGB::Black));
    leds.DrawLine(2, 12, 5, 12, (CRGB::Black));
    leds.DrawLine(5, 11, 6, 11, (CRGB::Black));
    leds.DrawFilledRectangle(5, 6, 6, 3, (CRGB::Black));
    leds.DrawLine(3, 2, 4, 2, (CRGB::Black));
    leds.DrawPixel(6, 2, (CRGB::Black));
    leds.DrawPixel(4, 6, (CRGB::Black));

    leds.DrawFilledRectangle(8, 11, 9, 3, (CRGB::Black));
    leds.DrawFilledRectangle(11, 11, 12, 3, (CRGB::Black));
    leds.DrawLine(9, 12, 11, 12, (CRGB::Black));
    leds.DrawLine(9, 2, 11, 2, (CRGB::Black));

    leds.DrawLine(14, 12, 14, 4, (CRGB::Black));
    leds.DrawPixel(14, 2, (CRGB::Black));
    FastLED.show();
    delay(1000);
    FastLED.clear(true);
}

void dispRaceInfo(int carNumber, int lapsComplete, int lapProgress) {
  // Afficher les informations sur la matrice LED
  // Déterminer la couleur de la voiture en fonction du numéro
  // position y du rectangle représentant la voiture
  // 1 = Rouge, 2 = Vert, 3 = Bleu, 4 = Blanc
  CRGB color;      // Couleur du tour en cours
  CRGB color2;     // Couleur du nombre de tours finis
  int y=0;

  // Déterminer le nombre de LED à allumer en fonction du pourcentage du tour
  // on allume les 12 premières LED pour 100% du tour
  int n = map(lapProgress, 0, 100, 0, 12);
  Serial.print("n vaut : ");
  Serial.print(n);
  Serial.print("\n");

  switch (carNumber) {
    //  Red Car
    case 1:
      color = CRGB::DarkRed;
      color2 = CRGB::Red;
      y = 12;
      break;
    // Green Car
    case 2:
      color = CRGB::DarkGreen;
      color2 = CRGB::Green;
      y = 8;
      break;
    // Blue Car
    case 3:
      color = CRGB::DarkBlue;
      color2 = CRGB::Blue;
      y = 4;
      break;
    // White Car
    case 4:
      color = CRGB::Grey;
      color2 = CRGB::White;
      y = 0;
      break;

    default:
      color = CRGB::Black;
      break;
  }  

  // Au départ on reçoit p1M1,0,100
  // Quand on est dans le premier tour on reçoit p1
  
  // Si le pourcentage est à 0 et le nombre de tour à UN
  // on n'allume aucune LED pour cette voiture
  if ((lapProgress == 0 ) && (lapsComplete == 1)) {
    // Eteindre le rectangle complet
    leds.DrawFilledRectangle(0, y, 15, y+3, (CRGB::Black));
    Serial.print("Aucune LED ======================= \n");
    FastLED.show();
  }
  // Si le nombre de tours est à UN on n'affiche que la position dans ce tour
  if (lapsComplete == 1 && (lapProgress != 0)) {
    // Eteindre le rectangle complet
    leds.DrawFilledRectangle(0, y, 15, y+3, (CRGB::Black));
    // Allumer les LED correspondant au % de tour effectué
    leds.DrawFilledRectangle(0, y, n, y+3, color);
    Serial.print("Que la position dans le tour ==== \n");
    FastLED.show();
  }

  // Si le nombre de tours est supérieur à 1
  if (lapsComplete >1) {
    // Eteindre le rectangle complet de la voiture, y compris le nombre de tours
    leds.DrawFilledRectangle(0, y, 15, y+3, (CRGB::Black));
    // Allumer les LED correspondant au % de tour effectué
    leds.DrawFilledRectangle(0, y, n, y+3, color);
    // Allumer le nombre de LEDs correspondant au nombre de tours complets
    leds.DrawFilledRectangle(12, y, 10 + lapsComplete, y+3, color2);
    Serial.print("Position + Nombre de tours ===== \n");
    FastLED.show();
  }
}
