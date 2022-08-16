
void page3(){
//  tft.setTextWrap(false);
//  tft.fillScreen(ST77XX_BLACK);
//  tft.setCursor(0, 30);
//  tft.setTextColor(ST77XX_BLUE,ST77XX_BLACK);
//  tft.setTextSize(4);
//  tft.println("Page 3!");
//  tft.setCursor(0, 0); 

  tft.setTextWrap(false);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 25);
  tft.setTextColor(ST77XX_BLUE, ST77XX_BLACK);
  tft.setTextSize(3);
  tft.println("");
  tft.println("Page 3:");
  tft.println("Compass");
  tft.println("");
  tft.setTextSize(2);
  tft.println("Compass Heading: ");
}


#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LIS2MDL.h>


Adafruit_LIS2MDL mag = Adafruit_LIS2MDL(12345);

void compass(){


//  tft.setCursor(0, 0); 
    
  #if defined(ARDUINO_ADAFRUIT_QTPY_ESP32S2) || \
      defined(ARDUINO_ADAFRUIT_QTPY_ESP32S3_NOPSRAM) || \
      defined(ARDUINO_ADAFRUIT_QTPY_ESP32_PICO)
    // ESP32 is kinda odd in that secondary ports must be manually
    // assigned their pins with setPins()!
    Wire1.setPins(SDA1, SCL1);
  #endif

  /* Initialise the sensor */
  if(!mag.begin(0x1E, &Wire1))
  {
    /* There was a problem detecting the LIS2MDL ... check your connections */
    tft.println("Ooops, no LIS2MDL detected ... Check your wiring!");
    while(1);
  }



    /* Get a new sensor event */
    sensors_event_t event;
    mag.getEvent(&event);
  
    float Pi = 3.14159;
  
    // Calculate the angle of the vector y,x
    float heading = (atan2(event.magnetic.y,event.magnetic.x) * 180) / Pi;
  
    // Normalize to 0-360
    if (heading < 0)
    {
      heading = 360 + heading;
    }
    

    tft.setCursor(0,150); 
    tft.println(" ");
    tft.setCursor(0,150); 
    tft.println(heading);
//    delay(500);
    
  

  
}
