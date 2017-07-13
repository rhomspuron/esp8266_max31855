//**************************************************************//
// Pin descriptions
// 0 -> Alarm Reley
// 1 -> TODO  
// 2 -> Buzzer
// 3 -> TODO
// 4 -> 
// 5 -> CLK
// 6 .. 14-> TOTO  
// 15 -> Switch
// 16 -> LED WiFi
//**************************************************************//
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <SPI.h>

#include "max31855.h"
#include "stringstream.h"

//**************************************************************//
//                 Gloabals declarations                        //
//**************************************************************//
#define SPI_SOFTWARE
#define GPIO_LED_WIFI_CONNECTED 16  
#define GPIO_MISO 12
#define GPIO_MOSI 13
#define GPIO_SCK 14
#define GPIO_CS_1 4
#define GPIO_CS_2 5
#define MAX31855_FREQ 8000000 //8MHz 

String double2str(double value, int presition=100);

//**************************************************************//
//                Gloabals Variables                            //
//**************************************************************//

#ifdef SPI_SOFTWARE
MAX31855 thermocouple_1 = MAX31855(GPIO_CS_2, GPIO_SCK, GPIO_MISO);
MAX31855 thermocouple_2 = MAX31855(GPIO_CS_1, GPIO_SCK, GPIO_MISO);
#else
MAX31855 thermocouple_1 = MAX31855(GPIO_CS_2);
MAX31855 thermocouple_2 = MAX31855(GPIO_CS_1);
#endif

//**************************************************************//
//                Setup Method                                  //
//**************************************************************//

void setup() {
  Serial.begin(115200);
  delay(100);
  digitalWrite(GPIO_LED_WIFI_CONNECTED, LOW);
  
}

//**************************************************************//
//                Main Loop Method                              //
//**************************************************************//

void loop() { 
  Serial.print("Read thermocouple_1 value: ");
  Serial.print(double2str(thermocouple_1.readThermocouple()));
  Serial.print(", internal value: ");
  Serial.println(double2str(thermocouple_1.readInternal()));
  Serial.print("Read thermocouple_2 value: ");
  Serial.print(double2str(thermocouple_2.readThermocouple()));
  Serial.print(", internal value: ");
  Serial.println(double2str(thermocouple_2.readInternal()));
  delay(1000);
  
   
}

//**************************************************************//
//                Functions                                     //
//**************************************************************//
String double2str(double value, int precision){
  String str_buff;
  StringStream buff = StringStream(str_buff);
  buff.print(int(value),DEC);
  buff.print(".");
  unsigned int frac;
  if(value >= 0)
    frac = (value - int(value)) * precision;
  else
    frac = (int(value)- value ) * precision;
  buff.print(frac,DEC) ;
  
  return str_buff;
}

//**************************************************************//



