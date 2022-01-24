
#include <FastLED.h>

//#include "hsv.h"


#define NUM_LEDS  27
#define LED_PIN   6

CRGB leds[NUM_LEDS];

uint8_t colorIndex[NUM_LEDS];


// Gradient palette "bhw1_03_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_03.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 16 bytes of program space.

DEFINE_GRADIENT_PALETTE( greenblue_gp ) {
    0,   0,  0,  0,
  137,  11,125,33,
  191,  40,219,45,
  255, 255,255,255};

DEFINE_GRADIENT_PALETTE( burningred_gp ) {
    0,   0,  0,  0,
  137,  110,0,0,
  191,  2550,0,0,
  255, 255,255,0};
  


/*    0,   0,  0,  0,
  137,  11,112,153,
  191,  40,219,105,
  255, 255,255,255};*/

// Gradient palette "bhw1_sunset3_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_sunset3.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE( bhw1_sunset3_gp ) {
    0, 227,237, 222,
   33, 186, 67,  1,
   71, 163, 21,  1,
   81, 157, 13,  1,
  188,  39, 21, 18,
  234,  12,  7,  4,
  255,  12,  7,  4};


DEFINE_GRADIENT_PALETTE( bhw1_03_gp ) { 
  0,   9, 45, 87,
  158,  34, 98, 112,
  227, 0, 255, 255,
  255, 255,  255, 255
};
 
DEFINE_GRADIENT_PALETTE( browngreen_gp ) { 
    0,    6,  255,    0,     //green
   71,    0,  255,  153,     //bluegreen
  122,  200,  200,  200,     //gray
  181,  110,   61,    6,     //brown
  255,    6,  255,    0      //green
};

DEFINE_GRADIENT_PALETTE( full_gp ) { 
    0, 255,   0,   0,
   42, 255, 255,   0,    
   84,   0, 255,   0,    
  126,   0, 255, 255,   
  168,   0,   0, 255,
  210, 255,   0, 255,
  255, 255,   0,   0,
};

// CRGBPalette16 greenblue = RainbowColors_p;
CRGBPalette16 greenblue = full_gp;
CRGBPalette16 orangePink = browngreen_gp;
CRGBPalette16 Fire = burningred_gp;


int strip_prog = 1;
int incomingByte = 0; 


void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  delay(2000); 
  //while (!Serial); //delay for Leonardo
  FastLED.addLeds<WS2811, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(255);

  //Fill the colorIndex array with random numbers
  for (int i = 0; i < NUM_LEDS; i++) {
    colorIndex[i] = random8();
  }
}

void loop() {

  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    // say what you got:
    //Serial.print("I received: ");
    //Serial.println(incomingByte, DEC);
    if (incomingByte == 49) //Loading
        strip_prog=0;
    if (incomingByte == 50) //Puls Green
        strip_prog=1;
    if (incomingByte ==51) //Minus RED
        strip_prog=2;
    
  }
  
  /*//Get IR Signal
  if (myReceiver.getResults()) {
    myDecoder.decode();           //Decode it
    myDecoder.dumpResults(true);  //Now print results. Use false for less detail
    Serial.println(myDecoder.value);
    if (myDecoder.protocolNum == NEC) {
      switch(myDecoder.value) {
        /*case 0:
           Serial.println("FUCK!!!"); 
           break;
        case 16195807:  //Volume Down
          Serial.println("wave");
          /*colorWave(strip.Color(0,   255,   255), position1); // Red
          position1++;
          if (position1 > strip.numPixels())
            position1 = 0;
          
          strip_prog = 1;
          //myReceiver.enableIRIn();
          break;
        case 16212127:  //Play/Pause
          Serial.println("blue");
          //colorWipe(strip.Color(  0,   0, 255), 5); // Blue
          strip_prog = 2;
          //myReceiver.enableIRIn();
          break;
        case 16228447:  //Volume Up
          Serial.println("green");
          //colorWipe(strip.Color(  0, 255,   0), 5); // Green
          strip_prog = 3;
          //myReceiver.enableIRIn();
          break;
        case 16244767: //white
          Serial.println("white");
          strip_prog = 4;
          //myReceiver.enableIRIn();
          break;
        case 16203967: //off
          Serial.println("off");
          //colorWipe(strip.Color(  0, 0,   0), 5); // black
          strip_prog = 0;
          //myReceiver.enableIRIn();
          break; 
        case 16236607: //ON
          Serial.println("On");
          //colorWipe(strip.Color(  0, 0,   0), 5); // black
          strip_prog = 5;
          //myReceiver.enableIRIn();
          break; 
          
      }
    }
    else {
       //colorWipe(strip.Color(  255, 255,   255), 5); // White
       strip_prog = 0;
       
    }
    
    
  }*/

  
  //Continue program
  switch(strip_prog) {
    case 0: //Waiting
      fastLED5();
    break;
    case 1: // Plus Green
      fastLEDGREEN();
    break;
    case 2: //Minus Red
      fastLEDRED();
    break;
    case 3:
       fastLEDRED();       
    break;
    case 4:
       fastLED3();    
    break;
    case 5:
       fastLED4();
    break;
  }

  
}





void fastLEDGREEN()
{
  // Color each pixel from the palette using the index from colorIndex[]
  for (int i = 0; i < NUM_LEDS; i++) {
    //leds[i] = ColorFromPalette(greenblue, colorIndex[i]);
    fill_solid( leds, NUM_LEDS, ColorFromPalette(greenblue, colorIndex[i]));
  }
  
  EVERY_N_MILLISECONDS(55){
    for (int i = 0; i < NUM_LEDS; i++) {
      colorIndex[i]++;
    }
  }
  FastLED.show();
}



void fastLEDRED()
{
  // Color each pixel from the palette using the index from colorIndex[]
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette(Fire, colorIndex[i]);
  }
  
  EVERY_N_MILLISECONDS(15){
    for (int i = 0; i < NUM_LEDS; i++) {
      colorIndex[i]++;
    }
  }
  FastLED.show();
}


void fastLED2 () {
  
    uint16_t beatA = beatsin16(30, 0, 255);
    uint16_t beatB = beatsin16(20, 0, 255);
    fill_rainbow(leds, NUM_LEDS, (beatA+beatB)/2, 8);
    
    FastLED.show();
}

void fastLED5 () {
    for (int a = 0; a < 255; a++)
  {
      //fill_rainbow(leds, NUM_LEDS, (beatA+beatB)/2, 8);
      fill_rainbow( leds, NUM_LEDS, a, 255/NUM_LEDS );
    FastLED.show();
  }
}


void fastLED3() {

  uint8_t sinBeat   = beatsin8(30, 0, NUM_LEDS - 1, 0, 0);
  uint8_t sinBeat2  = beatsin8(30, 0, NUM_LEDS - 1, 0, 85);
  uint8_t sinBeat3  = beatsin8(30, 0, NUM_LEDS - 1, 0, 170);

  // If you notice that your pattern is missing out certain LEDs, you
  // will need to use the higher resolution beatsin16 instead. In this
  // case remove the 3 lines above and replace them with the following:
  // uint16_t sinBeat   = beatsin16(30, 0, NUM_LEDS - 1, 0, 0);
  // uint16_t sinBeat2  = beatsin16(30, 0, NUM_LEDS - 1, 0, 21845);
  // uint16_t sinBeat3  = beatsin16(30, 0, NUM_LEDS - 1, 0, 43690);

  leds[sinBeat]   = CRGB::Blue;
  leds[sinBeat2]  = CRGB::Red;
  leds[sinBeat3]  = CRGB::White;
  
  fadeToBlackBy(leds, NUM_LEDS, 10);

  EVERY_N_MILLISECONDS(10){
  }

  FastLED.show();
}

void fastLED4() {

    uint16_t beatA = beatsin16(30, 0, 255);
    uint16_t beatB = beatsin16(20, 0, 255);
    fill_palette(leds, NUM_LEDS, (beatA + beatB) / 2, 10, orangePink, 255, LINEARBLEND);

    FastLED.show();
}

void fastLEDGreen() {
    fill_solid(leds,NUM_LEDS, CRGB::Black);
    for (int a = 0; a < NUM_LEDS; a++)
    {
        fill_solid(leds,NUM_LEDS, CRGB::Black);
        leds[a] = CRGB::Green;
       //fadeToBlackBy(leds, a, 255 / NUM_LEDS * a);
        FastLED.show(); 
        delay(50);
    }
   
   
}
