// Cretion : Hamid el mouden 
// 2019-07-19

#include "system_run.h"
#include "Program1.h"
#include"icon.h"
#include"Strings.h"
#include <TimeLib.h>

 
 int val;




void(* resetFunc) (void) = 0;


void errer(){
tft.fillRect(10,100,220,30,0x001F);
  tft.setCursor (40, 105); tft.setTextColor (BLACK); tft.println ("ERRER SIM");
tft.fillRect(10,130,220,70,0x8410);


tft.fillRect(73,143,100,40,BLACK);//ok
tft.fillRect(72,142,100,40,BLACK);//ok
tft.fillRect(69,139,100,40,BLACK);//ok
tft.fillRect(70,140,100,40,0x8410);//ok



  tft.setCursor (100, 150); tft.setTextColor (BLACK); tft.println ("OK");

  
}





void setup() {
  
 Serial.begin(9600);
  setSyncProvider(getTeensy3Time);
  
   
 input_();
lcd_on();
check_sys();

buzer_active();
check_sd();
tft.setTextWrap(false); // Don't wrap text to next line
go_home();
/* for ( unsigned int i = 0 ; i < EEPROM.length() ; i++ )
 EEPROM.write(i, 0);*/

 errer();
}
 void buzer_active()
 {
 Serial.println(EEPROM.read(addr));
     int val2 = EEPROM.read(addr);
    switch (val2) {
    case 1:
    pinMode(buzer,OUTPUT);
      break;
    case 0:
    pinMode(buzer,INPUT);
      break;
  }
  }

void digitalClockDisplay() {
  // digital clock display of the time

   tft.fillRect(10,198,220,50,BLACK);
  Serial.print(hour());
  tft.setTextSize(6);
  tft.setCursor (12, 200);
tft.setTextColor (GREEN);
tft.println (hour());
  tft.setCursor (82, 200);
tft.println (minute());
  tft.setCursor (160, 200);
  tft.println (second());
  
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}

/*  code to process time sync messages from the serial port   */
#define TIME_HEADER  "T"   // Header tag for serial time sync message

unsigned long processSyncMessage() {
  unsigned long pctime = 0L;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013 

  if(Serial.find(TIME_HEADER)) {
     pctime = Serial.parseInt();
     return pctime;
     if( pctime < DEFAULT_TIME) { // check the value is a valid time (greater than Jan 1 2013)
       pctime = 0L; // return 0 to indicate that the time is not valid
     }
  }
  return pctime;
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

 



void loop() {
 
   
  up_State = digitalRead(up_);
    ok_State = digitalRead(ok_);
     back_State = digitalRead(back_);
     
run1:
      if (up_State == HIGH) { // ggo home
     check_sys();
    delay (200);
}
  if (ok_State == HIGH) { // select page 1
    pip();
    option ++;
    if (option == 6) option = 1;
    menu (option);
    delay (200);
}

 if (digitalRead (back_) == HIGH && option == 1) { // goto phone
        option = 1; delay(200);
        menu_phone(1); delay(200);

   while (1) {
      ok_State = digitalRead(ok_);
      if (ok_State == HIGH) { // select menu up down phone
        option1 ++;
        if (option1 == 6) option1 = 1;
        menu_phone (option1);
        delay (200);
      }
       if (digitalRead (back_) == HIGH && option1 == 5) { // exit page2 go to loop
        option1 = 1;
        delay(200);
        menu (option);

        goto run1;

      }
   }
}
 
 if (digitalRead (back_) == HIGH && option == 2) { // goto message
        option = 1; delay(200);
       menu_message(1); delay(200);
        
   while (1) {
      ok_State = digitalRead(ok_);
      if (ok_State == HIGH) { // select menu up down phone
        option2 ++;
        if (option2 == 5) option2 = 1;
        menu_message (option2);
        delay (200);
      }
       if (digitalRead (back_) == HIGH && option2 == 4) { // exit page2 go to loop
        option2 = 1;
        delay(200);
        option = 2;
        menu (option);

        goto run1;

      }
   }

}
 if (digitalRead (back_) == HIGH && option == 3) { // goto sd file
        option = 2; delay(200);
           menu_sdfile(1); delay(200);
        
   while (1) {
      ok_State = digitalRead(ok_);
      if (ok_State == HIGH) { // select menu up down phone
        option3 ++;
        if (option3 == 6) option3 = 1;
        menu_sdfile (option3);
        delay (200);
      }
       if (digitalRead (back_) == HIGH && option3 == 5) { // exit page2 go to loop
        option3 = 1;
        delay(200);
        option = 3;
        menu (option);

        goto run1;

      }
   }
}
///config

 if (digitalRead (back_) == HIGH && option == 4) { // goto config
        option = 3;  delay(200);
                menu_config(1); delay(200);
        
   while (1) {
      ok_State = digitalRead(ok_);
      if (ok_State == HIGH) { // select menu up down phone
        option4 ++;
        if (option4 == 6) option4 = 1;
        menu_config(option4);
        delay (200);
      }
/////////////////////***************************************
      if (digitalRead (back_) == HIGH && option4 == 1) { // buzzer of/on
        option4 = 1;
        delay(200);

 int b = 1;
          EEPROM.update(addr, b);
          pinMode(buzer,OUTPUT);
      } /************************************************************/
          if (digitalRead (back_) == HIGH && option4 == 2) { // buzzer of/on
        option4 = 2;
        delay(200);

 int a = 0;
          EEPROM.update(addr, a);
          pinMode(buzer,OUTPUT);
      }//////////////////******************///////////////////////////
       if (digitalRead (back_) == HIGH && option4 == 5) { // exit page2 go to loop
         
        option4 = 1;
        delay(200);
        option = 4;
        menu (option);

        goto run1;

      }
   }
}
 if (digitalRead (back_) == HIGH && option == 5) { // goto sd file
        option = 4; delay(200);
         
           menu_autre(1); delay(200);
        
   while (1) {
      ok_State = digitalRead(ok_);
      if (ok_State == HIGH) { // select menu up down phone
        option5 ++;
        if (option5 == 4) option5 = 1;
        menu_autre(option5);
        delay (200);
      }
      
       if (digitalRead (back_) == HIGH && option5 == 2) { // exit menu autre
        option5 = 1;
        delay(200);
        option = 5;
        menu (option);

        goto run1;

      }
      if (digitalRead (back_) == HIGH && option5 == 3) { // exit menu autre
        option5 = 3;
        delay(200);

        while(1){
           ok_State = digitalRead(ok_);
      if (ok_State == HIGH) { // select menu up down phone
         option5 = 1;
        delay(200);
        option = 5;
        menu (option);

        goto run1;
      }
      
         if (Serial.available()) {
    time_t t = processSyncMessage();
    if (t != 0) {
      Teensy3Clock.set(t); // set the RTC
      setTime(t);
    }
  }
  digitalClockDisplay();  
  delay(500);
  
        }
      }

}
} 
}


void scrole1()

{

String text = " . . Text scrolling on Adafruit TFT shield . ."; // sample text

const int width = 18; // width of the marquee display (in characters)

// Loop once through the string

for (int offset = 0; offset < text.length(); offset++)

{

// Construct the string to display for this iteration

String t = "";

for (int i = 0; i < width; i++)

t += text.charAt((offset + i) % text.length());

// Print the string for this iteration

tft.setCursor(0, tft.height()/2-10); // display will be halfway down screen

tft.print(t);

// Short delay so the text doesn't move too fast

delay(200);

}

}











































void check_sys(){

  tft.fillScreen(back_color);
   tft.drawBitmap(150, 100,galery, 64, 64,BLUE);
  tft.drawBitmap(10, 100,phone1, 64, 64,GREEN);
 /* ok_State = digitalRead(ok_);
    while(1){
     
         if (Serial.available()) {
    time_t t = processSyncMessage();
    if (t != 0) {
      Teensy3Clock.set(t); // set the RTC
      setTime(t);
    }
  }
  digitalClockDisplay();  
  delay(1000);
    if (ok_State == HIGH) { // select page 1
    
    menu(1);
    delay (200);
       }
        }*/
}

void menu (int select) {  //=================================== menu

  tft.fillScreen(BLACK);

  top_menu1();
  bat();
  drawline_page1();
  btn_page1();

  int position [6] = {0, 30, 65, 105, 145,185};
  tft.fillRect  (10, position [select], 220, 40, 0xA145);
  page1_text();

}

void menu_phone (int select) { //=================================menu phone
  tft.fillScreen(BLACK);
 // top_menu1();
  bat();
  drawline_page1();
  btn_page1();
  int position [6] = {0, 30, 65, 105, 145,185};
  tft.fillRect (10, position [select], 220, 40, BLUE);
  phone_text();
}


void menu_message (int select) { //=================================menu message
  tft.fillScreen(BLACK);
 // top_menu1();
  bat();
  drawline_page1();
  btn_page1();
  int position [5] = {0, 30, 65, 105, 145};
  tft.fillRect (10, position [select], 220, 40, BLUE);
  message_text();
}

void menu_sdfile (int select) { //=================================menu sdfile
  tft.fillScreen(BLACK);
 // top_menu1();
  bat();
  drawline_page1();
  btn_page1();
  int position [6] = {0, 30, 65, 105, 145,185};
  tft.fillRect (10, position [select], 220, 40, BLUE);
  sdfile_text();
}

void menu_config(int select) { //=================================menu co,fig
  tft.fillScreen(BLACK);
 // top_menu1();
  bat();
  drawline_page1();
  btn_page1();
  int position [6] = {0, 30, 65, 105, 145,185};
  tft.fillRect (10, position [select], 220, 40, BLUE);
  config_text();
}
void menu_autre(int select) { //=================================menu autre
  tft.fillScreen(BLACK);
 // top_menu1();
  bat();
  drawline_page1();
  btn_page1();
  int position [4] = {0, 30, 65,105};
  tft.fillRect (10, position [select], 220, 40, BLUE);
  autre_text();
}


void go_home(){
    tft.fillScreen(back_color);
    top_home();
    bat();
    drawline_page1();
    btn_home();
    tft.setTextSize(2);
tft.setCursor (50, 2);
tft.setTextColor (GREEN);
tft.println ("Main List");
page1_text();
}

void page1_text()
{
tft.setTextSize (3);
tft.setTextColor (WHITE);
 tft.drawBitmap(18, 35,phone_icon, 32, 32,GREEN);
tft.setCursor (60, 40);
tft.println ("Phone");
 tft.drawBitmap(18, 70,sms_icon, 32, 32,YELLOW);
tft.setCursor (60, 75);
tft.println ("Message");
 tft.drawBitmap(18, 110,sd_icon, 32, 32,BLUE);
tft.setCursor (60, 115);
tft.println ("SD File");
 tft.drawBitmap(18, 150,config_icon, 32, 32,RED);
tft.setCursor (60, 155);
tft.println ("Config");
 tft.drawBitmap(18, 190,auter_icon, 32, 32,ORANGE); 
tft.setCursor (60, 195);
tft.println ("Autre");

}
void phone_text()
{

    tft.setTextSize(2);
tft.setCursor (50, 2);
tft.setTextColor (GREEN);
tft.println ("Phone");

tft.setTextSize (3);
tft.setTextColor (WHITE);
tft.setCursor (16, 35);
tft.println ("Call IN");
tft.setCursor (16, 75);
tft.println ("Call OUT");

tft.setCursor (16, 115);
tft.println ("Contact");
tft.setCursor (16, 155);
tft.println ("Delate");
tft.setCursor (16, 195);
tft.println ("Exit");

}

 void message_text()
{

 
    tft.setTextSize(2);
tft.setCursor (50, 2);
tft.setTextColor (GREEN);
tft.println ("Message");

tft.setTextSize (3);
tft.setTextColor (WHITE);
tft.setCursor (16, 35);
tft.println ("Inbox");
tft.setCursor (16, 75);
tft.println ("Outbox");

tft.setCursor (16, 115);
tft.println ("Delate");
tft.setCursor (16, 155);
tft.println ("Exit");
//tft.setCursor (16, 195);
//tft.println ("Exit");

}
void sdfile_text()
{

 
    tft.setTextSize(2);
tft.setCursor (50, 2);
tft.setTextColor (GREEN);
tft.println ("SD File");

tft.setTextSize (3);
tft.setTextColor (WHITE);
tft.setCursor (16, 35);
tft.println ("Photos");
tft.setCursor (16, 75);
tft.println ("Files");

tft.setCursor (16, 115);
tft.println ("Info");
tft.setCursor (16, 155);
tft.println ("Option");
tft.setCursor (16, 195);
tft.println ("Exit");

}

void pip(){
  digitalWrite(buzer,HIGH);
  delay(100);
  digitalWrite(buzer,LOW);
}
char* on ="( ON )";
char* of ="( OF )";
void config_text()
{

 
    tft.setTextSize(2);
tft.setCursor (50, 2);
tft.setTextColor (GREEN);
tft.println ("Config");

tft.setTextSize (3);
tft.setTextColor (WHITE);
tft.setCursor (16, 35);
tft.println ("Sound 1");

 Serial.println(EEPROM.read(addr));
    int val2 = EEPROM.read(addr);
    switch (val2) {
    case 1:
    tft.setCursor (120, 35);
tft.println (on);
    pinMode(buzer,OUTPUT);
      break;
    case 0:
    tft.setCursor (120, 35);
tft.println (of);
    pinMode(buzer,INPUT);
      break;
  }
  

tft.setCursor (16, 75);
tft.println ("Sound 0");

tft.setCursor (16, 115);
tft.println ("Set-up LCD");
tft.setCursor (16, 155);
tft.println ("Info");
tft.setCursor (16, 195);
tft.println ("Exit");

}

void autre_text()
{

  
    tft.setTextSize(2);
tft.setCursor (50, 2);
tft.setTextColor (GREEN);
tft.println ("Autre");

tft.setTextSize (3);
tft.setTextColor (WHITE);
tft.setCursor (16, 35);
tft.println ("Temporature");
tft.setCursor (16, 75);
tft.println ("Exit");
tft.setCursor (16, 115);
tft.println ("Clock");
/*
tft.setCursor (16, 155);
tft.println ("Info");
tft.setCursor (16, 195);
tft.println ("Exit");*/

}
