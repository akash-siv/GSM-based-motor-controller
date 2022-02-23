
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10,11);
boolean stringComplete = false;
String inputString = "";
String fromGSM="";
const int on = 3;
const int off = 2;
int relay = 4;
const long interval = 7200000; // 1 hour = 3600000 millisec
unsigned long previousMillis = 0;


void setup()  
{
  delay(20000);
  Serial.begin(9600);
  Serial.println("Serial Connected");
  mySerial.begin(9600);
  pinMode(on, OUTPUT); 
  pinMode(off, OUTPUT);
  pinMode(relay,OUTPUT);
  digitalWrite(on, HIGH);
  digitalWrite(off, HIGH);
  digitalWrite(relay,HIGH);
  //reserve some buffer space
  inputString.reserve(200);
  fromGSM.reserve(200);
  
  //Turn off echo from GSM
  mySerial.print("ATE0");
  mySerial.print("\r");
  delay(300);

}

void(* resetFunc) (void) = 0;


void loop() // run over and over
{
  //listen from GSM Module
  if (mySerial.available()){
   char inChar = mySerial.read();
    
    if (inChar == '"') {
      
       //check the state 

        if(fromGSM == "Saro"){
          Serial.println("---------ON-------");
          delay(2000);
          mySerial.print("ATH\r");
          digitalWrite(on, LOW);
          delay(2000);
          digitalWrite(on, HIGH);

          for(int i=0;i<=3600;i++){
           delay(1000);
          }

          digitalWrite(off, LOW);
          delay(2000);
          digitalWrite(off, HIGH);
          mySerial.println("ATD9790253340;\r");
          delay(11000);
          mySerial.print("ATH\r");
          delay(10000);
          mySerial.println("ATD9566776760;\r");
          delay(11000);
          mySerial.print("ATH\r");
        }

         if(fromGSM == "Irani"){
          Serial.println("---------ON-------");
          delay(2000);
          mySerial.print("ATH\r");
          digitalWrite(on, LOW);
          delay(2000);
          digitalWrite(on, HIGH);

          for(int i=0;i<=3600;i++){
           delay(1000);
          }

          digitalWrite(off, LOW);
          delay(2000);
          digitalWrite(off, HIGH);
          mySerial.println("ATD9790253340;\r");
          delay(11000);
          mySerial.print("ATH\r");
          delay(10000);
          mySerial.println("ATD9566776760;\r");
          delay(11000);
          mySerial.print("ATH\r");
          }
        
      //write the actual response
      Serial.println(fromGSM);
      //clear the buffer
      fromGSM = "";
        
    }else {
         fromGSM+=inChar;
    }
    }

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    resetFunc();
  }



}



