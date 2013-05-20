/*
Basic IR Home Automation
By Rohin Gopalakrishnanx
Available on Public Domain.
Credits to Shirrif(for his IR library)

created on May20th 2013
*/



#include <IRremote.h>
#define irPin 11

IRrecv irrecv(irPin);
decode_results results;

int LIGHT_CURRSTATE = 0;
int LIGHT_PIN = 0;

int BUTTON_STATE = 0;
int BUTTON_PIN = 0;

int R_PIN = 0;
int G_PIN = 0;
int B_PIN = 0;


void setup() {
   Serial.begin(9600);
   irrecv.enableIRIn();
   pinMode(BUTTON_PIN, INPUT);
   pinMode(LIGHT_PIN, OUTPUT);
   pinMode(R_PIN, OUTPUT);
   pinMode(G_PIN, OUTPUT);
   pinMode(B_PIN, OUTPUT);
   digitalWrite(BUTTON_PIN, HIGH); //internal pullup resistor 
}
 
void loop() {
  
  check_button_state();
  
   if (irrecv.decode(&results)) {
 
      switch (results.value) {
         case 0x143226DB:
           write_led(255, 0, 0); // red
             delay (20);
           write_led(0, 0, 0); // off
             delay (20);
           write_led(255, 0, 0); //red
             delay (10);
           light_function();
           write_led(0, 255, 0); // green
             delay (20);
           check_button_state(); // buttonstate for blue
//           Serial.println("Tube Light");
           break;
         }
         
 
   irrecv.resume();
   }
}

int light_function() {
  if (LIGHT_CURRSTATE == 0){ //off
    digitalWrite(LIGHT_PIN, HIGH); //turn on 
    LIGHT_CURRSTATE = 1;
  }
   else{ // on
     digitalWrite(LIGHT_PIN, LOW); // turn off 
     LIGHT_CURRSTATE = 0;
}
}

int check_button_state() {
  BUTTON_STATE = digitalRead(BUTTON_PIN);
  if (BUTTON_STATE = 1) { // if on
    write_led(0, 0, 255); //blue
  }
   else{
     write_led(0, 0, 0); // off
  }
}
int write_led(int R, int G, int B) { // write's led
  analogWrite(R_PIN, R);
  analogWrite(G_PIN, G);
  analogWrite(B_PIN, B);
}
 
  
