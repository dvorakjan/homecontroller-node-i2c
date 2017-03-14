#include "src/Button/Button.h"
#include <Wire.h>

#define I2C_ADDRESS 0x04

/* 
 *  VSTUPY                             VYSTUPY
 *  ======                             =======
 *  
 *  5  LozniceVpravo                   2  PokojLED
 *  6  LozniceVlevo                    3  Chodba
 *  7  PokojDruhyZPrava                4  Bar
 *  8  PokojVpravo                     13 JidelnaPodhled
 *  9  Chodba                          14 LozniceLED
 *  10 PokojDruhyZleva                 15 Jidelna
 *  11 PokojVlevo / KuchynVpravo       16 LozniceLustr
 *  12 KuchynVlevo                     17 Pokoj
 *  
 */

#define BUTTONS_COUNT 8
Button buttons[BUTTONS_COUNT] = {
  Button(5, 16, 60), 
  Button(6, 16),    
  Button(7, 2),     
  Button(8, 17),    
  Button(9, 3, 120),  
  Button(10, 15),   
  Button(11, 4),    
  Button(12, 13),   
};
unsigned long previousMillis = 0;

void setup() {
  Serial.begin(9600); 
  Serial.print("RelayController init:\n[");
  
  for (int i=0; i<BUTTONS_COUNT; i++) {
    buttons[i].init();
    Serial.print(i + ",");
  }
  
  Serial.println("] ---> OK");

  Wire.begin(I2C_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
  Serial.println("I2C init done");
}

void loop() {
  unsigned long currentMillis = millis();
  
  for (int i=0; i<BUTTONS_COUNT; i++) {
    buttons[i].update();

    // on state change, change state of output
//    if ( buttons[i].isFell()   || buttons[i].isRise()  ) {       // Hybsky style - control by state change
  if ( buttons[i].isFell() ) {                                 // Dvorak style - control by fell
      buttons[i].writeState(!buttons[i].getState(), buttons, true);
    }
    
  }

  // check auto-off timers every second
  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;
    for (int i=0; i<BUTTONS_COUNT; i++) {
      buttons[i].checkCountdown();
    }
  }
}

String getButtonsStates(void) {
  String out = "";
  for (int i=0; i<BUTTONS_COUNT; i++) {
    out = out + buttons[i].getState();
  }
  return out;
}

void receiveData(int byteCount){
  while(Wire.available()) {
    int number = Wire.read();
    int device  = (uint8_t) ((number) >> 4);
    int command = (uint8_t) ((number) & 0xf);
    int out = 0;
    
    if (device==0) out=2;
    if (device==1) out=3;
    if (device==2) out=4;
    if (device==3) out=13;
    if (device==4) out=14;
    if (device==5) out=15;
    if (device==6) out=16;
    if (device==7) out=17;

    Serial.print("I2C received ");
    Serial.print(number);
    Serial.print(" - dev=");
    Serial.print(device);
    Serial.print(" - out=");
    Serial.print(out);
    Serial.print(", cmd=");
    Serial.println(command);
    
    if (command == 1) {
      digitalWrite(out, HIGH);
    }
    if (command == 0) {
      digitalWrite(out, LOW);
    }
  }
}

void sendData(){
  int stat = 0;
  stat = stat | (digitalRead(2) << 7);
  stat = stat | (digitalRead(3) << 6);
  stat = stat | (digitalRead(4) << 5);
  stat = stat | (digitalRead(13) << 4);
  stat = stat | (digitalRead(14) << 3);
  stat = stat | (digitalRead(15) << 2);
  stat = stat | (digitalRead(16) << 1);
  stat = stat | (digitalRead(17));
  
  Serial.print("sendData ");
  Serial.print(stat);
  Serial.print(" (");
  Serial.print(String(stat, BIN));
  Serial.println(")");
  
  Wire.write(stat);
}

