#include <FastLED.h>        //https://github.com/FastLED/FastLED
#include <LEDMatrix.h>      //https://github.com/Jorgen-VikingGod/LEDMatrix
#include "images.h"

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

#define CRGB_CAR1 (CRGB::Red)
#define CRGB_CAR2 (CRGB::Blue)
#define CRGB_CAR3 (CRGB::Green)
#define CRGB_CAR4 (CRGB::White)

#define CRGB_DARK_CAR1 (CRGB::DarkRed)
#define CRGB_DARK_CAR2 (CRGB::DarkBlue)
#define CRGB_DARK_CAR3 (CRGB::DarkGreen)
#define CRGB_DARK_CAR4 (CRGB::Grey)

#define NB_CARS 4

typedef struct{
    uint8_t car;
    uint8_t lapProgress;
    uint8_t lapsComplete;
    uint16_t overallProgress;
}car_position_t;

uint8_t ranking[4]={1,2,3,4};
car_position_t cars_position[NB_CARS];

// https://gitlab.com/open-led-race/olr-arduino/-/blob/master/doc/OLR_Protocol_Serial.pdf
void countDown() ;
void dispWinner(String data) ;
void dispImage(const uint8_t *img);
void dispRaceInfo();


void setup()
{
  Serial.begin(BAUD);
  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds[0], leds.Size()).setCorrection(TypicalSMD5050);
  FastLED.setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(255);
  FastLED.clear(true);  
  dispImage(logo);delay(100);
}

int compareByProgress(const void* a, const void* b) {
    car_position_t *carA = (car_position_t*)a;
    car_position_t *carB = (car_position_t*)b;
    return (carB->overallProgress - carA->overallProgress);
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
      cars_position[carNumber-1].lapsComplete = data.substring(indexM + 1, indexComma1).toInt();
      cars_position[carNumber-1].lapProgress = data.substring(indexComma1 + 1, indexComma2).toInt();
      cars_position[carNumber-1].car = carNumber;
      cars_position[carNumber-1].overallProgress = 100*cars_position[carNumber-1].lapsComplete + cars_position[carNumber-1].lapProgress;
      if (carNumber==NB_CARS) { // Update Race information only when all player positions received (fastled update require critical blocking code section... )
        for(uint8_t i=0;i<NB_CARS;i++) {
          Serial.print(cars_position[i].car);
        }
        Serial.println();
        qsort(cars_position, NB_CARS, sizeof(car_position_t), compareByProgress);
        for(uint8_t i=0;i<NB_CARS;i++) {
          Serial.print(cars_position[i].car);
        }
        Serial.println();
        dispRaceInfo();
      }
    } else if (data.startsWith("R4")) {
      countDown();
    } else if (data.startsWith("w")) {    
      Serial.println(data);
      dispWinner(data);
   }
  }
}

void dispWinner(String data) {
  CRGB color;

  if (data.startsWith("w1")) {
    color = CRGB_CAR1;
  } else if (data.startsWith("w2")) {
    color = CRGB_CAR2;
  } else if (data.startsWith("w3")) {
    color = CRGB_CAR3;
  } else if (data.startsWith("w4")) {
    color = CRGB_CAR4;
  }

  for (int y = 0; y < 5; y++) {
    dispImage(arrival);
    delay(500);
    leds.DrawFilledRectangle(0, 0, 15, 15, color);
    FastLED.show();
    delay(500);
  }
  leds.DrawFilledRectangle(0, 0, 15, 15, color);
  FastLED.show();
}

void countDown() {
  dispImage(three);
  delay(2000);
  dispImage(two);
  delay(2000);
  dispImage(one);
  delay(2000);
  dispImage(go);
  delay(1000);
  FastLED.clear(true);
}

void dispImage(const uint8_t *img)
{
  for (int y = 0; y < MATRIX_HEIGHT; y++) {
    for (int x = 0; x < MATRIX_WIDTH; x++) {
        uint16_t p = y*MATRIX_HEIGHT+x;
        CRGB v;
        v.raw[0] = pgm_read_byte_near(img+3*p);  //Red
        v.raw[1] = pgm_read_byte_near(img+3*p+1);//Green
        v.raw[2] = pgm_read_byte_near(img+3*p+2);//Blue
        leds.DrawPixel(x,MATRIX_HEIGHT-y-1,v);
    }
  }
  FastLED.show();
}

void dispRaceInfo() {
  int lapsComplete;
  int lapProgress;
  for(int i=0;i<NB_CARS;i++) 
  {
    lapsComplete = cars_position[i].lapsComplete;
    lapProgress = cars_position[i].lapProgress;
    uint8_t carNumber = cars_position[i].car;
    CRGB color_progress;   
    CRGB color_complete;
    int y=0;

    int n = map(lapProgress, 0, 100, 0, 12);
    y = 16-4*(i+1);
    
    switch (carNumber) {
      case 1:
        color_progress = CRGB_DARK_CAR1;
        color_complete = CRGB_CAR1;
        break;
      case 2:
        color_progress = CRGB_DARK_CAR2;
        color_complete = CRGB_CAR2;
        break;
      case 3:
        color_progress = CRGB_DARK_CAR3;
        color_complete = CRGB_CAR3;
        break;
      case 4:
        color_progress = CRGB_DARK_CAR4;
        color_complete = CRGB_CAR4;
        break;

      default:
        color_progress = CRGB::Black;
        break;
    }  
    if ((lapProgress == 0 ) && (lapsComplete == 1)) {
      leds.DrawFilledRectangle(0, y, 15, y+3, (CRGB::Black));
    } else if (lapsComplete == 1 && (lapProgress != 0)) {
      leds.DrawFilledRectangle(0, y, 15, y+3, (CRGB::Black));
      leds.DrawFilledRectangle(0, y, n, y+3, color_progress);
    } else if (lapsComplete >1) {
      leds.DrawFilledRectangle(0, y, 15, y+3, (CRGB::Black));
      leds.DrawFilledRectangle(0, y, n, y+3, color_progress);
      leds.DrawFilledRectangle(12, y, 10 + lapsComplete, y+3, color_complete);
    }
  }
  FastLED.show();
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