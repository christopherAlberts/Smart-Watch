#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

// How many internal neopixels do we have? some boards have more than one!
#define NUMPIXELS       1
#define PIN_NEOPIXEL    5

#ifdef ADAFRUIT_HALLOWING
  #define TFT_CS        39 // Hallowing display control pins: chip select
  #define TFT_RST       37 // Display reset
  #define TFT_DC        38 // Display data/command select
  #define TFT_BACKLIGHT  0 // Display backlight pin

#elif defined(ARDUINO_FEATHER_ESP32) // Feather Huzzah32
  #define TFT_CS         14
  #define TFT_RST        15
  #define TFT_DC         32

#elif defined(ESP8266)
  #define TFT_CS         4
  #define TFT_RST        16                                            
  #define TFT_DC         5

#else
  // For the breakout board, you can use any 2 or 3 pins.
  // These pins will also work for the 1.8" TFT shield.
  #define TFT_CS        A0
  #define TFT_RST        A1 // Or set to -1 and connect to Arduino RESET pin
  #define TFT_DC         A2
#endif

Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

// OPTION 1 (recommended) is to use the HARDWARE SPI pins, which are unique
// to each board and not reassignable. For Arduino Uno: MOSI = pin 11 and
// SCLK = pin 13. This is the fastest mode of operation and is required if
// using the breakout board's microSD card.

// For 1.44" and 1.8" TFT with ST7735 (including HalloWing) use:
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// For 1.3", 1.54", and 2.0" TFT with ST7789:
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// connect a push button between ground and...
const uint8_t   buttonPin1              = 15;
const uint8_t   buttonPin2              = 4;
const uint8_t   buttonPin3              = 33;
const uint8_t   buttonPin4              = 7;


// variables will change:
int buttonState1 = 0; 
int buttonState2 = 0; 
int buttonState3 = 0; 
int buttonState4 = 0;

String pages[4] = {"page1", "page2", "page3", "page4"};

int currentPage = 0;

// the interrupt service routine affects this
volatile bool   isButtonPressed1         = false;
volatile bool   isButtonPressed2         = false;
volatile bool   isButtonPressed3         = false;
volatile bool   isButtonPressed4         = false;

#define SerialDebugging true

// color definitions
const uint16_t  Display_Color_Black        = 0x0000;
const uint16_t  Display_Color_Blue         = 0x001F;
const uint16_t  Display_Color_Red          = 0xF800;
const uint16_t  Display_Color_Green        = 0x07E0;
const uint16_t  Display_Color_Cyan         = 0x07FF;
const uint16_t  Display_Color_Magenta      = 0xF81F;
const uint16_t  Display_Color_Yellow       = 0xFFE0;
const uint16_t  Display_Color_White        = 0xFFFF;
 
// The colors we actually want to use
uint16_t        Display_Text_Color         = Display_Color_White;
uint16_t        Display_Backround_Color    = Display_Color_Blue;

// assume the display is off until configured in setup()
bool            isDisplayVisible        = false;

// declare size of working string buffers. Basic strlen("d hh:mm:ss") = 10
const size_t    MaxString               = 16;

// the string being displayed on the SSD1331 (initially empty)
char oldTimeString[MaxString]           = { 0 };


void setup() {
   
    // button press pulls pin LOW so configure HIGH
    pinMode(buttonPin1,INPUT_PULLUP);
    pinMode(buttonPin2,INPUT_PULLUP);
    pinMode(buttonPin3,INPUT_PULLUP);
    pinMode(buttonPin4,INPUT_PULLUP);

    // read the state of the pushbutton value:
    buttonState1 = digitalRead(buttonPin1);
    buttonState2 = digitalRead(buttonPin2);
    buttonState3 = digitalRead(buttonPin3);
    buttonState4 = digitalRead(buttonPin4);

    // use an interrupt to sense when the button is pressed
    attachInterrupt(digitalPinToInterrupt(buttonPin1), senseButtonPressed1, FALLING);
    attachInterrupt(digitalPinToInterrupt(buttonPin2), senseButtonPressed2, FALLING);
    attachInterrupt(digitalPinToInterrupt(buttonPin3), senseButtonPressed3, FALLING);
    attachInterrupt(digitalPinToInterrupt(buttonPin4), senseButtonPressed4, FALLING);

    #if (SerialDebugging)
    Serial.begin(115200); while (!Serial); Serial.println();
    #endif

    // settling time
    delay(250);

    // ignore any power-on-reboot garbage
    isButtonPressed1 = false;

    #ifdef ADAFRUIT_HALLOWING
      // HalloWing is a special case. It uses a ST7735R display just like the
      // breakout board, but the orientation and backlight control are different.
      tft.initR(INITR_HALLOWING);        // Initialize HalloWing-oriented screen
      pinMode(TFT_BACKLIGHT, OUTPUT);
      digitalWrite(TFT_BACKLIGHT, HIGH); // Backlight on
    #else
      // Use this initializer if using a 1.8" TFT screen:
//      tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
    
      // OR use this initializer (uncomment) if using a 1.44" TFT:
      //tft.initR(INITR_144GREENTAB); // Init ST7735R chip, green tab
    
      // OR use this initializer (uncomment) if using a 0.96" 180x60 TFT:
      //tft.initR(INITR_MINI160x80);  // Init ST7735S mini display
    
      // OR use this initializer (uncomment) if using a 1.54" 240x240 TFT:
      tft.init(240, 280);           // Init ST7789 240x240

      // OR use this initializer (uncomment) if using a 2.0" 320x240 TFT:
      //tft.init(240, 320);           // Init ST7789 320x240
  
      // SPI speed defaults to SPI_DEFAULT_FREQ defined in the library, you can override it here
      // Note that speed allowable depends on chip and quality of wiring, if you go too fast, you
      // may end up with a black screen some times, or all the time.
      //tft.setSPISpeed(40000000);
    #endif

      #if defined(NEOPIXEL_POWER)
    // If this board has a power control pin, we must set it to output and high
    // in order to enable the NeoPixels. We put this in an #if defined so it can
    // be reused for other boards without compilation errors
        pinMode(NEOPIXEL_POWER, OUTPUT);
        digitalWrite(NEOPIXEL_POWER, HIGH);
      #endif

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setBrightness(20); // not so bright

    // initialise the display
    tft.setFont();
    tft.fillScreen(Display_Backround_Color);
    tft.setTextColor(Display_Text_Color);
    tft.setCursor(0, 30);
    tft.setTextSize(4);
    tft.println("What up my Homey1!!!!");

    // the display is now on
    isDisplayVisible = true;

}


void loop() {

    // has the button been pressed?
    if (isButtonPressed1) {

        // yes! toggle display visibility
        isDisplayVisible = !isDisplayVisible;

        // apply
        tft.enableDisplay(isDisplayVisible);
        page1();
        #if (SerialDebugging)
        Serial.print("button pressed @ ");
        Serial.print(millis());
        Serial.print(", display is now ");
        Serial.println((isDisplayVisible ? "ON" : "OFF"));
        #endif

        // confirm button handled
        isButtonPressed1 = false;
        
    }

    if (isButtonPressed2){
      Serial.println("next_page");
      next_page();
      isButtonPressed2 = false;
    }

    if (isButtonPressed3){
      Serial.println("previos_page");
      previos_page();
      isButtonPressed3 = false;
    }

    if(isDisplayVisible){
      digitalWrite(NEOPIXEL_POWER, HIGH);
      pixels.fill(0x00FF00); //GREEN
      pixels.show();
    }
    else{
      digitalWrite(NEOPIXEL_POWER, LOW);
    }


    if (currentPage == 2){
      compass();
    }
    
    // no need to be in too much of a hurry
    delay(1000);

  
   
}
