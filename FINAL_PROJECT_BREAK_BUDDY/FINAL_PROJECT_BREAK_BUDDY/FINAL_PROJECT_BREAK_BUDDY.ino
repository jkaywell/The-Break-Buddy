//background libraries
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_SPIDevice.h>

//Purpose of project is to combine sound and light together to make The Break Buddy, an anti-procrastination device using a Neopixel, a timer regulated by a DS3231 RTC chip, and a buzzer.
//Arduino Buzzer code provided by user SURJATEJA via the Arduino Project Hub. LINK: https://create.arduino.cc/projecthub/SURYATEJA/use-a-buzzer-module-piezo-speaker-using-arduino-uno-89df45 Extensively modified by myself.
//RTC chip code provided by user NicolasJ7 via Instructables Circuits. LINK: https://www.instructables.com/Arduino-Timer-With-OnOff-Set-Point/. Extensively modified by myself.



//controls speaker input
int buzzer = 3; //buzzer to arduino pin 3

#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip(60, 9);

// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <Wire.h>
#include <RTClib.h>


RTC_DS3231 rtc;

//continuously keeps track of current time
DateTime start;
    

//higher value, slower notes
int speed = 900;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  strip.begin();

  //show that all the changes in this line have been established
  strip.clear();
  strip.show();

  strip.setBrightness(50);

  //buzzer pin mode
  pinMode (buzzer, OUTPUT); // Set buzzer - pin 9 as an output

#ifndef ESP8266
  while (!Serial);
#endif

  delay(3000); // wait for console opening

//safety function 1
 if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

//safety function 2
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  start = rtc.now();
}

  void loop() {
    //continuously keeps track of current time
    DateTime now = rtc.now();
    
    strip.clear();
    
    //sets buzzer to off in beginning 
    noTone(buzzer);
    
  //unixtime function
  Serial.print(now.unixtime());

    //State I
    if (now.unixtime() - start.unixtime() >= 5) { //900
      Serial.println("State I");
      tone(buzzer, 100); // Send 0.01 KHz sound signal...
      for (int i = 0; i < strip.numPixels(); i++) {
        //set pixel color green
        strip.setPixelColor(i, 0,255,0);
      }
    }


    //State II
    if (now.unixtime() - start.unixtime() >= 10) {  //1800
      Serial.println("State II");
      tone(buzzer, 500); // Send 0.1 KHz sound signal...
      for (int j = 0; j < strip.numPixels(); j++) {
        //set pixel color yellow
        strip.setPixelColor(j, 150,150,0);
      }
    }

    //State III
    if (now.unixtime() - start.unixtime() >= 15) { //2700
      Serial.println("State III");
      tone(buzzer, 1000); // Send 0.5 KHz sound signal...
      for (int k = 0; k < strip.numPixels(); k++) {
        //set pixel color orange
        strip.setPixelColor(k, 179, 30, 0);
      }
    }

    //State IV
    if (now.unixtime() - start.unixtime() >= 20) { //3600
      Serial.println("State IV");
      tone(buzzer, 5000); // Send 1.0 KHz sound signal...
      for (int l = 0; l < strip.numPixels(); l++) {
        //set pixel color red
        strip.setPixelColor(l, 255, 0, 0);
      }
    }
    Serial.println();
    delay(1000);
    strip.show();
  }
