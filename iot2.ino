#include <SPI.h>
#include <RF24.h>
#include <BTLE.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <dht.h>
dht DHT;
bool var = 0;
char input;
LiquidCrystal_I2C lcd(0x27,16,2);
 RF24 radio(9,10);
 BTLE btle(&radio);

 int led = 9;           
int brightness = 0;   
int fadeAmount = 5;    

 void setup() {
  lcd.init();
  lcd.init();
  lcd.backlight();
 Serial.begin(9600);

 
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("     Tempfy");
    lcd.setCursor(0,1);
    lcd.print("     V 1.0");
    delay(3000);
    lcd.clear();
   
   Serial.println("Notify agent Started");
 btle.begin("Notify");
  pinMode(7,OUTPUT);

 }


void loop() {
 int sensorValue = analogRead(A0);
   float voltage = sensorValue * (5.0 / 1023.0);
  DHT.read11(A0);

 nrf_service_data buf;
 //buf.service_uuid = NRF_DEVICE_INFORMATION_SERVICE_UUID; //0x180A
 buf.service_uuid = NRF_TEMPERATURE_SERVICE_UUID; //0x1809
 //buf.service_uuid =NRF_BATTERY_SERVICE_UUID; //0x180F
 buf.value = BTLE::to_nRF_Float(DHT.temperature);
 btle.advertise(0x16, &buf, sizeof(buf));
 btle.hopChannel();
   btle.hopChannel();
  
   while(voltage > 3)
   {
    lcd.clear();
    lcd.print("   High Voltage");
   
    
    lcd.setCursor(0,1);
    lcd.print("  Unplug Device");
    delay(1000);
   }
    
    

 if(!btle.listen()){
    
    lcd.setCursor(0,0);
    lcd.print("!");
    digitalWrite(7,HIGH);
  

  
   }else{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" ");
    digitalWrite(7,LOW);
    Serial.flush();
    
   }

  lcd.print(" ");
   lcd.print(+ " { Display } ");
 lcd.setCursor(0,1);
 lcd.print(DHT.temperature);


   }
