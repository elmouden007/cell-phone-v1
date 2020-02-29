 #include "Config.h"

 int test_size = 3;
int back_color = BLACK;
int text_color = GREEN;
 
  void lcd_off(){

    delay(1000);
      pinMode(led,OUTPUT);
   //digitalWrite(led,1);
      tft.begin ();
      tft.setTextWrap(false);
      tft.fillScreen(back_color);
      tft.setRotation(2);
      tft.setTextSize(test_size);
      tft.setTextColor (text_color);
     
      tft.setCursor (0, 60);
      tft.print("LCD OK"); //test lcd text
      Serial.println("LCD ================= OK");

  }

  void lcd_on(){
    delay(1000);
     pinMode(led,OUTPUT);
   digitalWrite(led,1);
      tft.begin ();
      tft.setTextWrap(false);
      tft.fillScreen(back_color);
      tft.setRotation(2);
      tft.setTextSize(test_size);
      tft.setTextColor (text_color);
      tft.setCursor (0, 60);
      tft.print("LCD OK"); //test lcd text
      Serial.println("LCD ================= OK");
  }

File myFile; File root; Sd2Card card; SdVolume volume; SdFile root1;

void check_sd(){
    Serial.print("Initializing SD card..."); if (!SD.begin(20)) { Serial.println("failed!"); 
       tft.setCursor (0, 100);
     tft.print("SD Errer"); //test lcd text
    }
    Serial.println("OK!");
    tft.setCursor (0, 100);
     tft.print("SD OK"); //test lcd text
  
}
