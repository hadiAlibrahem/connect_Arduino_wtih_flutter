#include <ArduinoJson.h>
#include <Servo.h>
#include <Wire.h>  // Include the Wire library for I2C communication
#include <LiquidCrystal_I2C.h> // Include the LiquidCrystal_I2C library 
#include <SPI.h> // Include the SPI library
#include <MFRC522.h> // Include the RFID library

///////////////////////////////////////////////////////////////////
#define   sens3  8      //exiat  spishal
#define   sens4  7     // exit public
#define   Pazar  6
 /////////////////////////////////////////////////////////                

#define SS_PIN 10   // Define the pins for the RFID reader
#define RST_PIN 9   

// Create an instance of the RFID library
MFRC522 mfrc522(SS_PIN, RST_PIN);
//
//// Define the I2C address of the LCD display
//#define I2C_ADDR 0x27
//
//// Define the number of columns and rows of the LCD display
//#define LCD_COLS 16
//#define LCD_ROWS 2
////////////////////////////////////////////////////////////////////////////////////////
Servo myservo;                                                             //define servo name
Servo myservo_sp;
 //////////////////////////////////////////////////////////////////////////////////////  Start SETUP  
//LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLS, LCD_ROWS);
LiquidCrystal_I2C lcd(0x27, 16, 2);// Create an instance of the LiquidCrystal_I2C library

void setup() {
  Serial.begin(115200);
  // Initialize the RFID reader
  SPI.begin();
  mfrc522.PCD_Init();
  // Initialize the LCD display
  lcd.init();
  lcd.backlight();
  ////////////////////////////////
  pinMode(sens4, INPUT);
  pinMode(sens3, INPUT);
   ////////////////////////////
  myservo.attach(5);
  myservo_sp.attach(4) ;
  myservo.write(0); 
  myservo_sp.write(0); 
///////////////////////////////////////////// ////// /

   pinMode(Pazar,OUTPUT); 
  digitalWrite(Pazar,LOW);

}

void loop() {
   if(Serial.available()>0)
 {
     DynamicJsonDocument control(200);
     deserializeJson(control,Serial);
     String meesage1=control["SOS1"];
     String meesage2=control["SOS2"];
     String meesage3=control["BZAR"];
     String meesage4=control["NotAllowedToEnter"];
     String meesage5=control["SuccessflyEnter1"];
     String meesage6=control["SuccessflyEnter2"];
     String meesage7=control["ExitFromPark1"];
     String meesage8=control["ExitFromPark2"];
     
    if(meesage1=="SOS1")
      {
        control["SOS1"]="open";
        LcdSOS1();
      }
        else if(meesage2=="SOS2")
       {
        control["SOS2"]="opene";
        LcdSOS2();
        }
//     else if(meesage3=="BZAR")
//       {
//         control["BZAR"]="close BZAR";
//         Pazare();
//        }
     else if(meesage4=="NotAllowedToEnter")
       {
        control["NotAllowedToEnter"]="close NotAllowedToEnter";         //Serial.print("Error open servo from Esp ");
         LcdNotAllowedToEnter();          
        } 
         else if(meesage5=="SuccessflyEnter1")
        {
         control["SuccessflyEnter1"]="close SuccessflyEnter1";
         LcdSuccessflyEnter1();
        }
         else if(meesage6=="SuccessflyEnter2")
       {
         control["SuccessflyEnter2"]="close SuccessflyEnter2";
         LcdSuccessflyEnter2();
        }
          else if(meesage7=="ExitFromPark1")
       {
         control["ExitFromPark1"]="close ExitFromPark1";
         LcdExitFromPark1();
        }
          else if(meesage8=="ExitFromPark2")
       {
         control["ExitFromPark2"]="close ExitFromPark2";
         LcdExitFromPark2();
        }
 }

sensor4();
sensor3();
Rfid();
}
void Pazare()
   {
         digitalWrite(Pazar,HIGH);
         delay(1500);
         digitalWrite(Pazar,LOW); 
  }
////////////////////////////////////////////////////////////////  
  void LcdNotAllowedToEnter(){   
                    lcd.clear();
                    lcd.setCursor (0,5);
                    lcd.print("Sory.. ");
                    lcd.setCursor (0,1);
                    lcd.print("Not Your Place");  
                    Pazare();                                                  
                    delay (500);
                   lcd.clear();    
                 }
//////////////////////////////////////////////////////////////////////
void LcdSuccessflyEnter1(){
                    lcd.clear();
                    lcd.setCursor (0,0);
                    lcd.print("The Car 1");
                    lcd.setCursor (0,1);
                    lcd.print("Is In Place");                                                              
                    delay (2000);
                    lcd.clear();
  
  
  }

 //////////////////////////////////////////////////////////////////////
void LcdSuccessflyEnter2(){
                    lcd.clear();
                    lcd.setCursor (0,0);
                    lcd.print("The Car 2");
                    lcd.setCursor (0,1);
                    lcd.print("Is In Place");                                                              
                    delay (2000);
                    lcd.clear();
                }


   //////////////////////////////////////////////////////////////////////
void LcdExitFromPark1(){
                    lcd.clear();
                    lcd.setCursor (0,0);
                    lcd.print("The Car 1");
                    lcd.setCursor (0,1);
                    lcd.print("Get Out Now");                                                              
                    delay (2000);
                    lcd.clear();
                }
            
 //////////////////////////////////////////////////////////////////////
void LcdExitFromPark2(){
                    lcd.clear();
                    lcd.setCursor (0,0);
                    lcd.print("The Car 2");
                    lcd.setCursor (0,1);
                    lcd.print("Get Out Now");                                                              
                    delay (2000);
                    lcd.clear();
                }
//////////////////////////////////////////////////////////////////////
void LcdAllowRfid(){lcd.clear();
                    lcd.setCursor (0,0);
                    lcd.print("Entering a Car"); 
                    servoPublic();                   
                    lcd.clear();
                }
//////////////////////////////////////////////////////////////////////
void LcdNotAllowRfid(){
                    lcd.clear();
                    lcd.setCursor (0,5);
                    lcd.print("Sory..");
                    lcd.setCursor (0,1);
                    lcd.print("Book First");                                                               
                    Pazare();                                                          
                    delay (500);
                    lcd.clear();
                }

//////////////////////////////////////////////////////////////////////////////////////////
void LcdSOS1(){
  
             lcd.clear();
             lcd.setCursor (0,5);
             lcd.print("Enter To");
             lcd.setCursor (0,1);
             lcd.print("Space number 1");                                                               
             servoPublic();                                                           
             delay (500);
             lcd.clear();
  
  }
  //////////////////////////////////////////////////////////////////////////////////////////
void LcdSOS2(){
  
             lcd.clear();
             lcd.setCursor (0,5);
             lcd.print("Enter To");
             lcd.setCursor (0,1);
             lcd.print("Space number 2");                                                               
             servoPublic();                                                           
             delay (500);
             lcd.clear();
  
  } 
//////////////////////////////////////////////////////////////////////////////////////
 void LcdExitCarFromSpecial(){
                    lcd.clear();
                    lcd.setCursor (0,0);
                    lcd.print("The Car Got Out");
                    lcd.setCursor (0,1);
                    lcd.print("From Special"); 
                    //   servoSpishal();                   
                     servoPublic();                                                   
                     delay (500);
                     lcd.clear();
  }  
  //////////////////////////////////////////////////////////////////////////////////////
 void LcdExitCarFromPublic(){
                    lcd.clear();
                    lcd.setCursor (0,0);
                    lcd.print("The Car Got Out");
                    lcd.setCursor (0,1);
                    lcd.print("From Public"); 
                    //   servoSpishal();                   
                     servoPublic();                                                   
                     delay (500);
                     lcd.clear();
  }
/////////////////////////////////////////////////////////////////////////////////////////
void Rfid() {
  // Check if an RFID card is present
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // If a card is present, read its UID
    String cardUID ="";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      cardUID += String(mfrc522.uid.uidByte[i], HEX);
    }

if(cardUID == "fa826b89")
          {
 
            LcdAllowRfid();
            mfrc522.PICC_HaltA();
            mfrc522.PCD_StopCrypto1();
      }
else {
     LcdNotAllowRfid();
   // Halt and reset the RFID reader
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
   }
 }
}

//////////////////////////////////////////////////////////////////////////////////End  LOOP
void  servoPublic ()     ///////////////////////////////////////// servo public
 {
  myservo.write(180);
  delay(2000);
  myservo.write(90);
    // delay(15);
}


void  servoSpishal ()     ///////////////////////////////////////// servo public
 {
  myservo.write(0);
  delay(2000);
  myservo_sp.write(90);
    // delay(15);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
void sensor3()                    // for exit  car in  special parking
{
      if(digitalRead(sens3)==HIGH)
      {
        LcdExitCarFromSpecial(); 
      }
}
//////////////////////////////////////////////////////////////////////////////
void sensor4()                    // for exit  car in  public  parking
     {
      if(digitalRead(sens4)==HIGH)
      {
       LcdExitCarFromPublic();                                }
      }
