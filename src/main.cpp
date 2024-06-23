#include <FastLED.h>        //https://github.com/FastLED/FastLED
#include <LEDMatrix.h>      //https://github.com/Jorgen-VikingGod/LEDMatrix


#define DATA_PIN            13         
#define COLOR_ORDER         GRB
#define CHIPSET             WS2812B

#define BAUD                115200
#define MATRIX_WIDTH        16
#define MATRIX_HEIGHT       16
#define MATRIX_TYPE         HORIZONTAL_ZIGZAG_MATRIX
#define MATRIX_SIZE         (MATRIX_WIDTH*MATRIX_HEIGHT)
#define NUMPIXELS           MATRIX_SIZE

cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;

#define pause 300


#define CRGB_CAR1 (CRGB::Red)
#define CRGB_CAR2 (CRGB::Green)
#define CRGB_CAR3 (CRGB::Blue)
#define CRGB_CAR4 (CRGB::White)

#define CRGB_DARK_CAR1 (CRGB::DarkRed)
#define CRGB_DARK_CAR2 (CRGB::DarkGreen)
#define CRGB_DARK_CAR3 (CRGB::DarkBlue)
#define CRGB_DARK_CAR4 (CRGB::Grey)


uint8_t ranking[4]={1,2,3,4};



const uint8_t logo[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xEE,0x21,0x24,0xEE,0x22,0x23,0xEE,0x22,0x23,0xEE,0x22,0x23,
0xEE,0x22,0x23,0xEF,0x22,0x23,0xEE,0x22,0x23,0xF0,0x24,0x24,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xEE,0x22,0x22,0xEE,0x22,0x23,0xFD,0x22,0x23,0xFA,0x20,0x21,0xF2,0x23,0x24,0xEE,0x22,0x23,
0xEE,0x22,0x23,0xF3,0x23,0x24,0xFF,0x22,0x23,0xEE,0x1F,0x20,0xFF,0x7F,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xEE,0x23,0x23,0xEE,0x23,0x24,0xFF,0x25,0x26,0xF1,0x16,0x17,0xED,0x15,0x16,0xEE,0x1D,0x1E,0xEE,0x23,0x24,
0xEE,0x23,0x24,0xEE,0x1E,0x1F,0xEE,0x14,0x15,0xFF,0x19,0x1A,0xED,0x21,0x21,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xED,0x24,0x24,0xED,0x22,0x23,0xFF,0x24,0x26,0xEC,0x09,0x0A,0xF6,0x8A,0x8B,0xFC,0xD2,0xD2,0xEE,0x1B,0x1C,0xEE,0x1B,0x1C,
0xEE,0x1D,0x1E,0xED,0x13,0x14,0xFA,0xC0,0xC0,0xFE,0x98,0x99,0xFE,0x0E,0x0F,0xEE,0x1D,0x1D,0x00,0x00,0x00,0x00,0x00,0x00,
0xEE,0x23,0x23,0xFF,0x25,0x26,0xED,0x13,0x14,0xF1,0x4D,0x4E,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF7,0x90,0x90,0xEC,0x05,0x06,
0xEC,0x0E,0x0F,0xF6,0x88,0x88,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x4C,0x4C,0xEC,0x0A,0x0B,0x00,0x00,0x00,0x00,0x00,0x00,
0xF2,0x23,0x24,0xEF,0x1A,0x1B,0xEC,0x11,0x12,0xFD,0xE6,0xE6,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xEF,0x30,0x31,
0xEF,0x2C,0x2D,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xDD,0xDD,0xFF,0x17,0x18,0xEC,0x13,0x13,0x00,0x00,0x00,
0xF1,0x21,0x22,0xEE,0x1A,0x1B,0xED,0x15,0x16,0xF6,0x8C,0x8D,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFB,0xCA,0xCA,
0xEC,0x09,0x0A,0xFB,0xD0,0xD0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x88,0x89,0xEC,0x08,0x09,0xF5,0x1D,0x1D,
0xEC,0x08,0x09,0xF4,0x74,0x75,0xFB,0xD0,0xD0,0xEC,0x03,0x04,0xFC,0xD7,0xD7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xF3,0x66,0x67,0xEE,0x23,0x24,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFD,0x37,0x38,0xEB,0x0C,0x0D,
0xEF,0x30,0x31,0xFE,0xF7,0xF7,0xFF,0xFF,0xFF,0xF3,0x63,0x64,0xEF,0x34,0x35,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFD,0xFD,0xED,0x10,0x11,0xF6,0x83,0x84,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFB,0xC0,0xC0,0xF8,0x0C,0x0E,
0xFF,0xD6,0xD6,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xED,0x14,0x15,0xF7,0x94,0x94,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xF9,0xB4,0xB4,0xEC,0x0A,0x0B,0xFD,0xE0,0xE0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFA,0x78,0x79,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xEB,0xEB,0xEE,0x1A,0x1B,0xED,0x15,0x16,0xFE,0xED,0xED,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xEF,0x27,0x28,0xF1,0x45,0x46,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF9,0xF9,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF1,0x45,0x46,0xED,0x11,0x12,0xEC,0x0B,0x0C,0xF3,0x5C,0x5D,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xF8,0x9E,0x9F,0xED,0x0F,0x10,0xEC,0x05,0x06,0xF8,0xAA,0xAA,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x90,0x91,0xEC,0x06,0x07,0xEE,0x22,0x23,0xEE,0x1F,0x20,0xEC,0x0A,0x0B,0xFA,0xBA,0xBA,
0xFD,0xE6,0xE6,0xED,0x18,0x19,0xEE,0x1A,0x1B,0xED,0x17,0x18,0xEE,0x22,0x23,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x00,0x00,0x00,0xF8,0x98,0x98,0xEE,0x20,0x21,0xFF,0x23,0x24,0xF2,0x23,0x24,0xEE,0x23,0x24,0xEE,0x1E,0x1F,0xEE,0x1F,0x20,
0xEE,0x23,0x24,0xED,0x1B,0x1C,0xEE,0x23,0x24,0xF2,0x23,0x24,0xFF,0x16,0x17,0xF3,0x67,0x68,0xFF,0xFF,0xFF,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xE5,0x00,0x00,0xEF,0x23,0x25,0xFD,0x24,0x25,0xFA,0x24,0x25,0xF2,0x23,0x24,0xEE,0x1D,0x1E,
0xED,0x1B,0x1C,0xF2,0x23,0x24,0xFB,0x24,0x25,0xFC,0x24,0x25,0xEE,0x24,0x25,0xE6,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xEF,0x24,0x24,0xEE,0x22,0x23,0xEE,0x21,0x23,0xEF,0x22,0x23,
0xEE,0x22,0x23,0xEE,0x22,0x23,0xEF,0x21,0x23,0xED,0x20,0x24,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};



// https://gitlab.com/open-led-race/olr-arduino/-/blob/master/doc/OLR_Protocol_Serial.pdf
void countDown() ;
void dispRaceInfo(int numeroVoiture, int toursComplets, int pourcentageTour) ;
void dispWinner(String data) ;



void setup()
{
  Serial.begin(BAUD);
  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds[0], leds.Size()).setCorrection(TypicalSMD5050);
  FastLED.setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(200);
  FastLED.clear(true);  
  //countDown();
  dispWinner("w1");
  dispWinner("w2");
  dispWinner("w3");
  FastLED.clear(true);  
/*
  // Draw the logo
  for (int y = 0; y < MATRIX_HEIGHT; y++) {
    for (int x = 0; x < MATRIX_WIDTH; x++) {
        uint16_t p = y*MATRIX_HEIGHT+x;
        CRGB v;
        v.raw[0] = logo[3*p];
        v.raw[1] = logo[3*p+1];
        v.raw[2] = logo[3*p+2];
        leds.DrawPixel(x,y,v);
    }
  }
  FastLED.show();
  */
}

void loop() {
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    if (data.startsWith("p")) { // p2M1,58,100
/*
      int indexp = data.indexOf("p");
      int indexM = data.indexOf("M");
      int indexComma1 = data.indexOf(",");

*/
#define indexp 0
#define indexM  2
#define indexComma1 4
      int indexComma2 = data.indexOf(",", indexComma1 + 1);
      int carNumber = data.substring(indexp + 1, indexM).toInt();
      int lapsComplete = data.substring(indexM + 1, indexComma1).toInt();
      int lapProgress = data.substring(indexComma1 + 1, indexComma2).toInt();
      dispRaceInfo(carNumber, lapsComplete, lapProgress);
    } else if (data.startsWith("R4")) {
      countDown();
    } else if (data.startsWith("w")) {    
      dispWinner(data);
   }
  }
}



void dispWinner(String data) {
  if (data.startsWith("w1")) {
    leds.DrawFilledRectangle(0, 0, 15, 15, CRGB_CAR1);
  } else if (data.startsWith("w2")) {
    leds.DrawFilledRectangle(0, 0, 15, 15, CRGB_CAR2);
  } else if (data.startsWith("w3")) {
    leds.DrawFilledRectangle(0, 0, 15, 15, CRGB_CAR3);
  } else if (data.startsWith("w4")) {
    leds.DrawFilledRectangle(0, 0, 15, 15, CRGB_CAR4);
  }
  FastLED.show();
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
  CRGB color;      // Couleur du tour en cours
  CRGB color2;     // Couleur du nombre de tours finis
  int y=0;

  int n = map(lapProgress, 0, 100, 0, 12);

  switch (carNumber) {
    case 1:
      color = CRGB_DARK_CAR1;
      color2 = CRGB_CAR1;
      y = 12;
      break;
    case 2:
      color = CRGB_DARK_CAR2;
      color2 = CRGB_CAR2;
      y = 8;
      break;
    case 3:
      color = CRGB_DARK_CAR3;
      color2 = CRGB_CAR3;
      y = 4;
      break;
    case 4:
      color = CRGB_DARK_CAR4;
      color2 = CRGB_CAR4;
      y = 0;
      break;

    default:
      color = CRGB::Black;
      break;
  }  
  if ((lapProgress == 0 ) && (lapsComplete == 1)) {
    leds.DrawFilledRectangle(0, y, 15, y+3, (CRGB::Black));
    FastLED.show();
  } else
  if (lapsComplete == 1 && (lapProgress != 0)) {
    leds.DrawFilledRectangle(0, y, 15, y+3, (CRGB::Black));
    leds.DrawFilledRectangle(0, y, n, y+3, color);
    FastLED.show();
  } else
  if (lapsComplete >1) {
    leds.DrawFilledRectangle(0, y, 15, y+3, (CRGB::Black));
    leds.DrawFilledRectangle(0, y, n, y+3, color);
    leds.DrawFilledRectangle(12, y, 10 + lapsComplete, y+3, color2);
    FastLED.show();
  }
}





/*
R8
R4
R5
p1M1,0,100
p2M1,0,100
p1M1,3,100
p2M1,3,100
p1M1,41,100
p2M1,33,100
p1M1,84,100
p2M1,58,100
p1M2,14,100
p2M1,84,100
p1M2,31,100
p2M2,13,100
p1M2,49,100
p2M2,37,100
p1M2,75,100
p2M2,64,100
p1M3,3,100
p2M3,10,100
p1M3,29,100
p2M3,51,100
p1M3,55,100
p2M3,88,100
p1M3,77,100
p2M4,21,100
p1M3,97,100
p2M4,60,100
p1M4,37,100
p2M4,98,100
p1M4,64,100
p2M5,33,100
p1M4,84,100
p2M5,64,100
p1M5,12,100
p2M5,90,100
p3M5,90,100
p4M2,75,100
w2
R8
R4
p2M5,33,100
p1M4,84,100
p3M5,64,100
p4M2,75,100

*/