//#include <EasyOta.h>
#include <Arduino.h>
#include <FS.h>
#include <ArduinoJson.h>
#include "WordClock.h"
#include <ArduinoOTA.h>
#include <Ticker.h>
//Library for the pixels
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

//NTP library
#include <NTPClient.h>
#include <TimeLib.h>
// change next line to use with another board/shield
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
//#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>
#include <math.h>

#include <ESP8266HTTPUpdateServer.h>

//#include <ArduinoOTA.h>

//needed for the WiFiManager library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
//Uncomment if you want the WifiManager to send debug-info to the UART
//#define DEBUG
//define FORMAT
#define Time_Wait 10000

#define PixPin 2
#define PixAmount 69

const char* host = "Woord_Klok";
//Build a webserver
ESP8266WebServer KlokServer(80);
ESP8266HTTPUpdateServer httpUpdater;

//needed by the NTP client
WiFiUDP ntpUDP;

// You can specify the time server pool and the offset (in seconds, can be
// changed later with setTimeOffset() ). Additionaly you can specify the
// update interval (in milliseconds, can be changed using setUpdateInterval() ).
NTPClient timeClient(ntpUDP, "nl.pool.ntp.org", 3600, 60000);

WordClock_Class Klok;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PixAmount, PixPin, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

const char* SettingFile = "/settings.json";
const char* IndexPage = "/Index.html";

Ticker PixelTick;

//Prototypes
void Do_Pixel(void);
void OTASetup(void);
void HandleRoot(void);
void SaveJson(void);
void BackToRoot(void);
int dow(int y, int m, int d);
int NthDate(int year, int month, int DOW, int NthWeek);

//Variables
uint8_t ClientBegin=0;
uint8_t Red=0;
uint8_t Green=0;
uint8_t Blue=0;

void setup(){

  Serial.begin(115200);
  OTASetup();

  SPIFFS.begin();

  //Start the Neopixel strip
  strip.begin();
  //strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'

  //Start the wordclock
  Klok.init();

 
}
void loop(){
  yield();//feed the watchdog

  if(WiFi.status() != WL_CONNECTED || ClientBegin==0){
      PixelTick.attach(0.5, Do_Pixel);
      //create a local instance, because when we are done, we don't need it anymore
      WiFiManager wifiManager;

      wifiManager.setDebugOutput(false);

      //Call the portal
      //wifiManager.setConfigPortalBlocking(false);
      if(!wifiManager.autoConnect("Woord_klok_AP")){
        ESP.reset();
        delay(1000);
      }
      //wifi is ok, resume with the program
      PixelTick.detach();
      if(ClientBegin==0){
        DynamicJsonBuffer jsonBuffer(200);
        timeClient.begin();
        timeClient.update();
        ArduinoOTA.begin();
        MDNS.begin(host);
        MDNS.addService("http", "tcp", 80);

        httpUpdater.setup(&KlokServer);
        KlokServer.on("/", HandleRoot);
        KlokServer.begin();


        File f = SPIFFS.open(SettingFile, "r");
        //Cannot open file, assume it doesn't exist
        if(!f){
          f = SPIFFS.open(SettingFile, "w");
          //Cannot create file, assume no format
          if(!f){
            SPIFFS.format();
            f.close();
            f = SPIFFS.open(SettingFile, "w");
            //Something has gone seriously wrong...
            if(!f){
              Serial.println("Unable to format system! Resetting!");
              ESP.reset();
              yield();
              }
            }
          f.print("{\"Red\": 255, \"Green\": 255, \"Blue\": 255}");
          }

        JsonObject& JSsettings = jsonBuffer.parseObject(f);
        // Test if parsing succeeds.
        if (!JSsettings.success()) {

          File f = SPIFFS.open(SettingFile, "w");
          char BeginSetting[] ="{\"Red\": 255, \"Green\": 255, \"Blue\": 255}";
          JsonObject& JSsettings = jsonBuffer.parseObject(BeginSetting);
          if (!JSsettings.success()) {
            Serial.println("Second time parseObject() failed during setup");
            delay(2000);
            ESP.reset();
            yield();

          }
          Serial.print(f);
          Red=JSsettings["Red"];
          Green=JSsettings["Green"];
          Blue=JSsettings["Blue"];
        }
        else{
          Red=JSsettings["Red"];
          Green=JSsettings["Green"];
          Blue=JSsettings["Blue"];
        }

        f.close();
        ClientBegin=1;
      }
  }
  else{
    ArduinoOTA.handle();
    KlokServer.handleClient();//Server needs time to
    MDNS.update();//mDNS handling
    static unsigned long Old_Millis=millis()+Time_Wait;

    if(millis()>=Old_Millis){
      Old_Millis+=Time_Wait;
      //Get the current time
      timeClient.update();
    }

    int Now_Minutes=timeClient.getMinutes();
    static int Old_Minutes=61;
    int Hours=timeClient.getHours();
    unsigned long t=timeClient.getEpochTime();
    int Day=day(t);
    int Month=month(t);
    int Year=year(t);
    int Dow = dow(Year, Month, Day);
    if((Month==3 && Dow==0 && Day+7>31 && Hours>2)||
      (Month==3 && Dow>0 && Day+7>31)||
      (Month==10 && Dow==0 && Day+7<31 && Hours<2)||
      (Month==10 && Dow>0 && Day+7<31)||
      (Month>3 && Month<10)){
      if(Hours<24){
        Hours+=1;
      }
      else{
        Hours=1;
      }
    }

    if(Now_Minutes>19){
      if(Hours==23){
        Hours=0;
      }
      else{
        Hours++;
      }
    }

    if(Now_Minutes!=Old_Minutes){
      Klok.Update++;
      Old_Minutes=Now_Minutes;
      for(int i = 1; i<23; i++){
        Klok.Woord[i].Show=0;
      }
      switch(Now_Minutes){
        case 0:
        case 60:
          Klok.Woord[Is].Show=1;
          Klok.Woord[Precies].Show=1;
          Klok.Woord[Uur].Show=1;
        break;

        case 1 ... 4:
          Klok.Woord[Was].Show=1;
          Klok.Woord[Uur].Show=1;
        break;

        case 35 ... 39:
          Klok.Woord[Half].Show=1;
        case 5 ... 9:
          Klok.Woord[Is].Show=1;
          Klok.Woord[m_Vijf].Show=1;
          Klok.Woord[Over].Show=1;
        break;

        case 40 ... 44:
          Klok.Woord[Half].Show=1;
        case 10 ... 14:
          Klok.Woord[Is].Show=1;
          Klok.Woord[m_Tien].Show=1;
          Klok.Woord[Over].Show=1;
        break;

        case 15 ... 19:
          Klok.Woord[Is].Show=1;
          Klok.Woord[Kwart].Show=1;
          Klok.Woord[Over].Show=1;
        break;

        case 20 ... 24:
          Klok.Woord[Half].Show=1;
        case 50 ... 54:
          Klok.Woord[Is].Show=1;
          Klok.Woord[m_Tien].Show=1;
          Klok.Woord[Voor].Show=1;
        break;

        case 25 ... 29:
          Klok.Woord[Half].Show=1;
        case 55 ... 59:
          Klok.Woord[Is].Show=1;
          Klok.Woord[m_Vijf].Show=1;
          Klok.Woord[Voor].Show=1;
        break;

        case 30:
          Klok.Woord[Is].Show=1;
          Klok.Woord[Precies].Show=1;
          Klok.Woord[Half].Show=1;
        break;

        case 31 ... 34:
          Klok.Woord[Was].Show=1;
          Klok.Woord[Half].Show=1;
        break;

        case 45 ... 49:
          Klok.Woord[Is].Show=1;
          Klok.Woord[Kwart].Show=1;
          Klok.Woord[Voor].Show=1;
        break;
      }//Minutes

      switch(Hours){
        case 0:
        case 12:
        case 24:
          Klok.Woord[Twaalf].Show=1;
        break;

        case 1:
        case 13:
          Klok.Woord[Een].Show=1;
        break;

        case 2:
        case 14:
          Klok.Woord[Twee].Show=1;
        break;

        case 3:
        case 15:
          Klok.Woord[Drie].Show=1;
        break;

        case 4:
        case 16:
          Klok.Woord[Vier].Show=1;
        break;

        case 5:
        case 17:
          Klok.Woord[h_Vijf].Show=1;
        break;

        case 6:
        case 18:
          Klok.Woord[Zes].Show=1;
        break;

        case 7:
        case 19:
          Klok.Woord[Zeven].Show=1;
        break;

        case 8:
        case 20:
          Klok.Woord[Acht].Show=1;
        break;

        case 9:
        case 21:
          Klok.Woord[Negen].Show=1;
        break;

        case 10:
        case 22:
          Klok.Woord[h_Tien].Show=1;
        break;

        case 11:
        case 23:
          Klok.Woord[Elf].Show=1;
        break;
      }//Hours
    }
    if(Klok.Update>0){
      Klok.Update=0;

      for(uint8_t x = 0; x<23; x++){
        if(Klok.Woord[x].Show>0){
          for(int y=Klok.Woord[x].Pixel; y<(Klok.Woord[x].Pixel+Klok.Woord[x].Pixels);y++){
            strip.setPixelColor(y, strip.Color(Red,Green,Blue));
          }
        }
        else{
          for(int y=Klok.Woord[x].Pixel; y<(Klok.Woord[x].Pixel+Klok.Woord[x].Pixels);y++){
            strip.setPixelColor(y, strip.Color(0,0,0));
          }
        }
      }
      strip.show();
    }
  }
}

void Do_Pixel(void){
  if(Red<255){
    Red++;
  }
  else if(Green<255){
    Green++;
  }
  else if(Blue<255){
    Blue++;
  }
  else if(Blue==255){
    Red=0;
    Green=0;
    Blue=0;
  }

  for(uint8_t i=0; i<strip.numPixels(); i++){
    strip.setPixelColor(i, strip.Color(Red, Green, Blue));
  }
  strip.show();

}

void OTASetup(void){
  //Here the OTA is initialised
  ArduinoOTA.setHostname(host);
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_SPIFFS
      type = "filesystem";
    }

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\n\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });

}

void HandleRoot(void){
  //Collect args and process them
  if(KlokServer.args()>0){
    Klok.Update++;
    if(KlokServer.hasArg("Red")){
      Red=KlokServer.arg("Red").toInt();
    }
    if(KlokServer.hasArg("Green")){
      Green=KlokServer.arg("Green").toInt();
    }
    if(KlokServer.hasArg("Blue")){
      Blue=KlokServer.arg("Blue").toInt();
    }
  SaveJson();
  }
  //Fetch the HTML file
  File f = SPIFFS.open(IndexPage, "r");
  if(!f){
    Serial.println("Unable to open index page");
  }
  String page = f.readStringUntil(EOF);
  f.close();
  //Set the correct values
  page.replace("$Red", String(Red));
  page.replace("$Green", String(Green));
  page.replace("$Blue", String(Blue));

  KlokServer.send(200, "text/html", page);
}

void SaveJson(void){
  DynamicJsonBuffer jsonBuffer(200);
  File f = SPIFFS.open(SettingFile, "r");
  if(!f){
    Serial.println("Cannot open file during saving!");
    return;
  }
  JsonObject& JSsettings = jsonBuffer.parseObject(f);
  f.close();

  if (!JSsettings.success()) {
    Serial.println("parseObject() failed during saving!");
    return;
  }

  JSsettings["Red"]   =Red;
  JSsettings["Green"] =Green;
  JSsettings["Blue"]  =Blue;

  if(SPIFFS.exists(SettingFile)){
    SPIFFS.remove(SettingFile);
  }

  f = SPIFFS.open(SettingFile, "w");
  JSsettings.printTo(f);
  //char temp[50]={0};
  //JSsettings.printTo(temp);
  //f.print(temp);
  //Serial.println(f.readStringUntil(EOF));
  f.close();
  //jsonBuffer.clear();
}

int dow(int y, int m, int d)
  {
      static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
      y -= m < 3;
      return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
  }

int NthDate(int year, int month, int DOW, int NthWeek){
  int targetDate = 1;
  int firstDOW = dow(year,month,targetDate);
  while (firstDOW != DOW){
    firstDOW = (firstDOW+1)%7;
    targetDate++;
  }
  //Adjust for weeks
  targetDate += (NthWeek-1)*7;
  return targetDate;
}
