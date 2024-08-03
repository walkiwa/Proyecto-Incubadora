#define BLYNK_TEMPLATE_ID "TMPL2jdQ1CEHU"
#define BLYNK_TEMPLATE_NAME "Proyecto"
#define BLYNK_AUTH_TOKEN "UFbtWqzgdS7CxkRDYi2TTU95jpir9fkP"
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32_SSL.h>
#include <LiquidCrystal_I2C.h>


char auth[]=BLYNK_AUTH_TOKEN;
char ssid[]="Laboratorios";//ssid de la red WiFi
char pass[]="C3nf0Labs$"; //clave de la red WiFi
DHT dht (DHTPIN, DHTTYPE);
BlynkTimer timer;
float h;
float t;
LiquidCrystal_I2C lcd(0x27,16,2);

void myTimerEvent()
{
Blynk.virtualWrite(V0,h);
delay(100);
Blynk.virtualWrite(V1,t);
}
void setup()
{
  lcd.begin();
  lcd.backlight();
dht.begin();
pinMode(18,OUTPUT);
Serial.begin(9600);
Blynk.begin(auth,ssid,pass);
timer.setInterval(1000L,myTimerEvent);

}
void loop()
{
h=dht.readHumidity();
t=dht.readTemperature();
lcd.setCursor(0, 0);
lcd.print("Temperatura: ");
lcd.print(t, DEC);
delay(1000);
lcd.setCursor(0,1);
lcd.print("Humedad: ");
lcd.print(h,DEC);
delay(1000);
 if(isnan(h)||isnan(t)){
 Serial.println(F("No se puede leer el sensor"));
 return;
 }
 Serial.print(F("Humedad:"));
 Serial.println(h);
 Serial.print(F("Temperatura:"));
 Serial.println(t);
 Blynk.run();
 delay(500);
 timer.run();

 if(t<37.5){
  digitalWrite(18,HIGH);
  }if(t>38.5){
    digitalWrite(18,LOW);
    }
};
