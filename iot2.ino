//All Made By Neksha DeSilva.
//Code On Github ( https://github.com/NekshaDeSilva/Tempfy/blob/main/tempfy.ino )
//Copiright (c) Ananda College Colombo 10 ( https:///acicts.lk )
//Copiright (c) 2022@ Arduino LLC all rights reserved.

#include <SPI.h>
#include <RF24.h>
#include <BTLE.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <dht.h>
#define DHT11_PIN 4
dht DHT;
bool var = "Sensor Disconnected";
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
  lcd.noBacklight();
 Serial.begin(9600);

 
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("     Tempfy");
    lcd.setCursor(0,1);
    lcd.print("     V 1.0");
    delay(3000);
    lcd.clear();
   
   Serial.println("Notify agent Started");
 btle.begin("Tempfy");
  pinMode(7,OUTPUT);
   pinMode(2,OUTPUT);

 }


void loop() {
    lcd.print(" ");
   lcd.print(+ " { Tempfy } ");
 lcd.setCursor(0,1);
 lcd.print(DHT.temperature / 1);
 Serial.println(DHT.temperature / 1);

 if(DHT.temperature > 33){
  lcd.print(+ "  warm");
 }

  if(DHT.temperature < 27 ){
  lcd.print(+ "  cold");
 }

  if(27 < DHT.temperature < 33 ){
  lcd.print(+ "  normal");
 }

 int sensorValue = analogRead(A0);
   float voltage = sensorValue * (5.0 / 1023.0);
  DHT.read11(DHT11_PIN);

 nrf_service_data buf;
 //buf.service_uuid = NRF_DEVICE_INFORMATION_SERVICE_UUID; //0x180A
 buf.service_uuid = NRF_TEMPERATURE_SERVICE_UUID; //0x1809
 //buf.service_uuid =NRF_BATTERY_SERVICE_UUID; 
 buf.value = BTLE::to_nRF_Float(DHT.temperature / 1);
 btle.advertise(0x16, &buf, sizeof(buf));
 btle.hopChannel();
   btle.hopChannel();
  
   while(voltage > 4)
   {
    lcd.clear();
    lcd.print("   Error Occured");
   
    
    lcd.setCursor(0,1);
    lcd.print("  Replug Device");
    
   }


    

 if(!btle.listen()){
    digitalWrite(7,HIGH);
  
  

  
   }else{
    digitalWrite(7,LOW);
 
    
   
    
   }
   if(DHT.temperature = -999.00){
     buf.value = BTLE::to_nRF_Float(var);
   }

delay(1000);


   }
  
//All Made By Neksha DeSilva.
//Code On Github ( https://github.com/NekshaDeSilva/Tempfy/blob/main/tempfy.ino )
//Copiright (c) Ananda College Colombo 10 ( https://github.com/acicts )
//Copiright (c) 2022@ Arduino LLC all rights reserved.
//Copiright (c) Microsoft Corporation all rights reserved.
