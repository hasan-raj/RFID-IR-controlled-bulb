#include <IRremote.h>
#include <string.h>
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN); 
int RECV_PIN = 6;

IRrecv irrecv(RECV_PIN);
decode_results results;
const int relayPin = 8; 


void setup()
{

  SPI.begin();      
  mfrc522.PCD_Init();  

  pinMode(relayPin, OUTPUT); 
  irrecv.enableIRIn();
  
}

void loop()
{
  if (irrecv.decode(&results))
  {
    switch(results.value)
    {
     case 0x592FA519:
     {
     digitalWrite(relayPin, HIGH); 
     break;
     }
       
     case 0x69C6FA7D:
     {
      digitalWrite(relayPin, LOW); 
      break;
     }
     
    }  
    
    delay (500);
    irrecv.resume(); 
     
   }
  
    
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
 
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }

  String content= "";
  byte letter;
  
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  
  content.toUpperCase();
  if (content.substring(1) == "AA 1B E9 81")
  {
    digitalWrite(relayPin, HIGH); 
    delay(3000);
  }
 
  else   
  {
    digitalWrite(relayPin, LOW); 
    delay(3000);
  }

  

}
