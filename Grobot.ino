// LED display v1.0 By Igor Fonseca Albuquerque, Thiago Farrauche, Diego Augustus and Yhan Christian

//include libraries
#include "LedControl.h"
#include <DHT.h>;
#include <LiquidCrystal.h>

//---------------------------temp and hum--------------------------------------
#define DHTPIN 9     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino
//-----------------------------------------------------------------------------

//----------------------------soil moisture------------------------------------
int sensor_pin = A0;
int output_value ;
//-----------------------------------------------------------------------------

//-----------------------------LED Matrix--------------------------------------
LedControl lc = LedControl(13,12,11,5); //Pin 13 = DIN, Pin 12 = CLK, Pin 11 = CS. 5 = number of displays
//-----------------------------------------------------------------------------

//-----------------------------LCD Screen--------------------------------------
// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 8, en = 7, d4 = 6, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);




//************************
// Definition of the faces
//************************

int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value
float high_temp, good_temp, low_temp, high_hum, good_hum, low_hum;

// neutral eye
byte neutral_eye[8] = {B00000000,
                       B00011000,
                       B00100100,
                       B01000010,
                       B01000010,
                       B00100100,
                       B00011000,
                       B00000000};

// spooky eye
byte spooky_eye[8] = {B00111100,
                      B01111110,
                      B11111111,
                      B11111111,
                      B11111111,
                      B11111111,
                      B01111110,
                      B00111100};

// closed eye (up)
byte closed_eye_up[8] = {B00000000,
                         B00001100,
                         B00011000,
                         B00011000,
                         B00011000,
                         B00011000,
                         B00001100,
                         B00000000};
                        
// closed eye (down)
byte closed_eye_down[8] ={B00000000,
                          B00001100,
                          B00001100,
                          B00000110,
                          B00000110,
                          B00001100,
                          B00001100,
                          B00000000};

                                                  
byte dead[8] ={B10000001,
                         B01000010,
                         B00100100,
                         B00011000,
                         B00011000,
                         B00100100,
                         B01000010,
                         B10000001};

byte speechless[8] = {B00011000,
                         B00011000,
                         B00011000,
                         B00011000,
                         B00011000,
                         B00011000,
                         B00011000,
                         B00011000};

byte wave[8] = {B00011000,
                         B00001100,
                         B00011000,
                         B00110000,
                         B00011000,
                         B00001100,
                         B00011000,
                         B00110000};

// happy mouth           //part 1 
byte happy_mouth[24] = { B00000000,
                         B00000000,
                         B00000000,
                         B00000000,
                         B01100000,
                         B00110000,
                         B00011000,
                         B00001100,    
                         //part 2
                         B00001110,
                         B00000110,
                         B00000110,
                         B00000110,
                         B00000110,
                         B00000110,
                         B00000110,
                         B00001100,
                         //part 3 
                         B00001100,
                         B00011000,
                         B00110000,
                         B01100000,
                         B00000000,
                         B00000000,
                         B00000000,
                         B00000000 };
                         
                                                  
// sad mouth            //part 1
byte sad_mouth[24] = {   B00000000,
                         B00000000,
                         B00000000,
                         B00000000,
                         B00000110,
                         B00001100,
                         B00011000,
                         B00110000,
                         //part 2
                         B00110000,
                         B01100000,
                         B01100000,
                         B01100000,
                         B01100000,
                         B01100000,
                         B01100000,
                         B00110000,
                         //part 3
                         B00110000,
                         B00011000,
                         B00001100,
                         B00000110,
                         B00000000,
                         B00000000,
                         B00000000,
                         B00000000 };

//very happy mouth            //part 1
byte very_happy_mouth[24] = { B00000000,
                              B00000000,
                              B01110000,
                              B01111100,
                              B01100110,
                              B01100110,
                              B01100011,
                              B01100011,
                              //part 2
                              B01100011,
                              B01100011,
                              B01100011,
                              B01100011,
                              B01100011,
                              B01100011,
                              B01100011,
                              B01100011,                        
                              //part 3
                              B01100011,
                              B01100011,
                              B01100110,
                              B01100110,
                              B01111100,
                              B01110000,
                              B00000000,
                              B00000000 };                         
                         
// neutral mouth              //part 1
byte neutral_mouth[24] = {    B00000000,
                              B00000000,
                              B00010000,
                              B00010000,
                              B00010000,
                              B00010000,
                              B00010000,
                              B00010000,
                              //part 2
                              B00010000,
                              B00010000,
                              B00010000,
                              B00010000,
                              B00010000,
                              B00010000,
                              B00010000,
                              B00010000,
                              //part 3
                              B00010000,
                              B00010000,
                              B00010000,
                              B00010000,
                              B00010000,
                              B00010000,
                              B00000000,
                              B00000000 };
                         
// tongue out            //part 1
byte tongue_mouth[24] = {B00000000,
                         B00000000,
                         B00000100,
                         B11001110,
                         B01111110,
                         B00111110,
                         B00011100,
                         B00001100,    
                         //part 2
                         B00001110,
                         B00000110,
                         B00000110,
                         B00000110,
                         B00000110,
                         B00000110,
                         B00000110,
                         B00001100,
                         //part 3 
                         B00001100,
                         B00011000,
                         B00110000,
                         B01100000,
                         B00000000,
                         B00000000,
                         B00000000,
                         B00000000 };

// opened mouth            //part 1
byte opened_mouth[24] = {  
//                           B00000000,
//                           B00000000,
//                           B00000000,
//                           B00000000,
//                           B00000000,
//                           B00000000,
//                           B00000000,
//                           B00000000,

                           B00000000,
                           B00011100,
                           B00100010,
                           B01000001,
                           B01000001,
                           B00100010,
                           B00011100,
                           B00000000,
                           // part 2
                           B00000000,
                           B00011100,
                           B00100010,
                           B01000001,
                           B01000001,
                           B00100010,
                           B00011100,
                           B00000000,
//                             B00000000,
//                           B00000000,
//                           B00000000,
//                           B00000000,
//                           B00000000,
//                           B00000000,
//                           B00000000,
//                           B00000000,
                           // part 3
                           B00000000,
                           B00000000,
                           B00000000,
                           B00000000,
                           B00000000,
                           B00000000,
                           B00000000,
                           B00000000 };

//**************
// Arduino Setup
//**************
void setup()
{
  lcd.begin(16, 2);
  dht.begin();
  lcd.print("T: ");
  lcd.print("H: ");

  high_temp = 33;
  good_temp = 23;
  low_temp = 20.4;
  high_hum = 94;
  good_hum = 70;
  low_hum = 60;
  //start serial communication
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

//**********
// Main Loop
//**********
void loop()
{
  delay(100);

    //Read data and store it to variables hum and temp
    hum = dht.readHumidity();
    temp= dht.readTemperature();

   
   output_value= analogRead(sensor_pin);
   output_value = map(output_value,550,0,0,100);
   Serial.print("Soil Mositure: ");
   Serial.print(output_value);
   lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);

   Serial.println("%");
    //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");
    lcd.setCursor(4,0);
    lcd.print((temp));
  lcd.setCursor(4, 1);
  lcd.print((hum));
    delay(500); //Delay 2 sec.
//  int sensorValue = analogRead(A0);
  // print out the value you read:
//  Serial.println(sensorValue);
//  delay(100);        // delay in between reads for stability
  if (Serial.available())  //verifies if there is serial data available
  {
    char cmd = Serial.read();
                
    if(cmd == ':') {
      display_eyes(neutral_eye, neutral_eye);
    }
    if(cmd == '~') {
      display_eyes(wave, wave);
    }
    if(cmd == ';') {
      display_eyes(neutral_eye, closed_eye_up);
    }
    if(cmd == '8') {
      display_eyes(spooky_eye, spooky_eye);
    }
    if(cmd == ')'){
      display_mouth(happy_mouth);
    }    
    if(cmd == '('){
      display_mouth(sad_mouth);
    }    
    if((cmd == 'D')||(cmd == 'd')){
      display_mouth(very_happy_mouth);
    }
    if((cmd == 'p')||(cmd == 'P')){
      display_mouth(tongue_mouth);
    }    
    if((cmd == 'o')||(cmd == 'O')){
      display_mouth(opened_mouth);
    }    
    if(cmd == '|'){
      display_mouth(neutral_mouth);
    }    

  }
//  high_temp = 40;
//  good_temp = 32;
//  low_temp = 27;
//  high_hum = 99;
//  good_hum = 99;
//  low_hum = 60;
  if(temp >= high_temp && hum <= low_hum){
    display_eyes(dead, dead);
    lcd.setCursor(0,0);
    lcd.print("I Dead");
  }
  else if(temp <= low_temp && hum >= high_hum){
    display_eyes(speechless, speechless);
    lcd.setCursor(0,0);
    lcd.print("I Fine");
  }
  else if(temp >= low_temp && hum >= high_hum){
    display_eyes(dead, dead);
    lcd.setCursor(0,0);
    lcd.print("I Dead");
  }
  else if(temp <= good_temp+4 && temp >= good_temp -4 && hum >= good_hum - 10 && hum <= good_hum + 15){
    display_eyes(closed_eye_up, closed_eye_up);
    lcd.setCursor(0,0);
    lcd.print(" Cool ");
  }
  else if(temp <= low_temp && hum <= low_hum){
    display_eyes(wave, wave);
    lcd.setCursor(0,0);
    lcd.print("I Dead");
  }
  else{
    display_eyes(neutral_eye, neutral_eye);
  }
}


//********************
// Auxiliary functions
//********************

//change eyes
void display_eyes(byte right_eye[], byte left_eye[]) {
  for(int i=0;i<8;i++) {
   lc.setRow(0,i,left_eye[i]);
   lc.setRow(1,i,right_eye[i]);
  } 
}


//change mouth
void display_mouth(byte mouth[]) {
  for(int i=0;i<8;i++) {
    lc.setRow(2,i,mouth[i]);
    lc.setRow(3,i,mouth[i+8]);
    lc.setRow(4,i,mouth[i+16]);
  }
}

//setRow is used instead of setColumn because it runs faster! Although, characters must be declared rotated 90 degrees counter-clockwise
