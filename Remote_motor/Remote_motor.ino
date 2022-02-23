
#include <SoftwareSerial.h>

SoftwareSerial mySerial(12,11);
boolean stringComplete = false;
String inputString = "";
String fromGSM="";
const int On = 3;
const int off = 2;

void setup()  
{
  pinMode(On, OUTPUT); 
  pinMode(off, OUTPUT);
  digitalWrite(On, HIGH);
  digitalWrite(off, HIGH);
  delay(20000);
  Serial.begin(9600);
  Serial.println("Serial Connected");
  mySerial.begin(9600);
  
  //reserve some buffer space
  inputString.reserve(200);
  fromGSM.reserve(500);
  
  //Turn off echo from GSM
  mySerial.print("ATE0");
  mySerial.print("\r");
  delay(300);
     
          
          
          mySerial.println("ATD9840283009;\r");
          delay(20000);
          mySerial.print("ATH\r");
          delay(10000);
          mySerial.println("ATD9442798309;\r");
          delay(20000);
          mySerial.print("ATH\r");
          delay(2000);

}

void(* resetFunc) (void) = 0;

void loop() // run over and over
{
  //listen from GSM Module
  if (mySerial.available()){
   char inChar = mySerial.read();
    
    if (inChar == '"') {
      
       //check the state 

        if(fromGSM == "User"){
          Serial.println("---------ON-------");
          delay(2000);
          mySerial.print("ATH\r");
          digitalWrite(On, LOW);
          delay(2000);
          digitalWrite(On, HIGH);
          delay(1000);
           
           
           while(1){
              if (mySerial.available()){
   char inChar = mySerial.read();
    
    if (inChar == '"') {
      
       //check the state 

        if(fromGSM == "User"){
          Serial.println("---------OFF-------");
          delay(2000);
          mySerial.print("ATH\r");
          digitalWrite(off, LOW);
          delay(2000);
          digitalWrite(off, HIGH);
          delay(30000);
          mySerial.println("ATD9840283009;\r");
          delay(20000);
          mySerial.print("ATH\r");
          delay(10000);
          mySerial.println("ATD9442798309;\r");
          delay(20000);
          mySerial.print("ATH\r");
          delay(2000);
          Serial.println("resetting");
          delay(100);
          resetFunc();  //call reset
         }
        
      //write the actual response
      Serial.println(fromGSM);
      //clear the buffer
      fromGSM = "";
        
    }else {
         fromGSM+=inChar;
    }
    }}
    

      }
        
      //write the actual response
      Serial.println(fromGSM);
      //clear the buffer
      fromGSM = "";
        
    }else {
         fromGSM+=inChar;
    }
    }

}



