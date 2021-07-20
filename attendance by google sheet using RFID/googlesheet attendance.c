#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>
#include <deprecated.h>
#include <SPI.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Keypad.h>
#include <HTTPClient.h>


const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS]= {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','c'},
  {'*','0','#','D'}
  };

  byte rowPins[ROWS] = {12,12,14,27};
  byte colPins[COLS] = {26, 25, 33, 32};

  Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROW, COLS);

  //OLED DISPLAY
  #define SCREEN_WIDTH 128
  #define SCREEN_HEIGHT 64

  #define OLED_RESET     4
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


  #define RTS_PIN        36
  #define SS_PIN         5
  #define BUZER          15
  #define proximity_sens 39
  #define LOCK_PIN       2

  int Secret_Code =      6969;


String ID_e;
int value = 0;
bool done_flag = 0;
char* response = "";
String res = "";
char* succ_code = "200 ok";
bool rfid_flag = 1;

MFRC522 mfrc522(SS_PIN, RST_PIN);

const char* NAME;

String Event_Name = "rfid";
String Key = "bex_jajPELRWl8qmdeLgff";
String resource = "/trigger" + Event_Name + "/with/key/" + Key;
const char* server = "maker.ifttt.com"

const char* ssid   = "S20_FE";
const char* password = "5838@AMCA";


void setup() {

  Serial.begin(9600);

  pinMode(BUZZER, OUTPUT);
  pinMode(LOCK_PIN, OUTPUT);
  pinMode(proximity_sens, INPUT_PULLUP);
  digitalWrite(BUZZER, LOW);

  if(display.begin(SSD1306_SWITCHCAPVCC, 0x3c)){
      Serial.println(f("SSD1306 allocation failed"));
      for(;;);

}

display.clearDisplay();
display.setTextSize(2);
display.setTextColor(WHITE);
display.print("RFID Door Lock");
display.display();

SPT.begin();
mfrc522.PCD_Init();

initWifi();

display.clearDisplay();
Serial.println("Scan Your Tag");
display.setTextSize(2);
display.setTextColor(WHITE);
display.print("Scan Your Tag");
display.display();
}


void loop() {

  char key = keypad.getKey();

     if (key){
       Serial.println(key);
       beep(200);
       
      }

      if(key == 'A')
      {
        Serial.println('A');
        Serial.println("PIN CODE");
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(10, 0);
        display..println(("PIN CODE"));
        display.setCursor(25,20);
        display.println(("MODE"));
        display.display();
        beep(200);
        beep(200);
        delay(1000);

        Serial.println("Enter the \nFour Digit \nCode");

        rfid_flag = 0;
      }

      //RFID MODE
      if (rfid_flag ==1)
      {
        display.clearDisplay();

        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.print("Scan Your Tag");
        display.display();

        if(digitalRead(proximity_sens)==LOW)
          Exit_sensor();

          if(! mfrc522.PICC_IsNewCardPresent())
          {
            return;
            }

            if (! mfrc522.PICC_ReadCardSerial())
            {
              return;
             }

             String content = "";
             byte letter;
             for(byte i=0; i < mfrc522.uid.size; i++)
             {
              content.concat(string(mfrc522.uid.uidByte[i] < 0x10 ? "0":""));
              content.concat(string(mfrc522.uid.uidByte[i], HEX));
              }

              content.toUpperCase();
              //For User 1
              if (content.substring(1) == "52 17 13 4C") //UID number
               {
                Serial.print("!!--");
                Serial.println(content.substring(1));
                NAME = "swayam";
                display.clearDisplay();

                display.setTextSize(2);
                display.setTextColor(WHITE);
                display.setCursor(1,1);
                display.println("welcome");
                display.println("NAME");
                display.setCursor(1,40);
                display.print("Door Open");
                display.display();

                Door_Open();
                display.Write(BUZZER, LOW);
                
                display.clearDisplay();

                display.setTextSize(2);
                display.setTextColor(WHITE);
                display.setCursor(1,1);
                display.print("Door");
                display.setCursor(1,20);
                display.print("Door closed");
                display.display();
             
                makeIFTTTRequest();
                }
                //for user 2
                else if (content.substring(1) == "52 17 13 4C") //UID number
               {
                Serial.print("!!--");
                Serial.println(content.substring(1));
                NAME = "Disha";
                display.clearDisplay();

                display.setTextSize(2);
                display.setTextColor(WHITE);
                display.setCursor(1,1);
                display.println("welcome");
                display.println("NAME");
                display.setCursor(1,40);
                display.print("Door Open");
                display.display();

                Door_Open();
                display.Write(BUZZER, LOW);
                
                display.clearDisplay();

                display.setTextSize(2);
                display.setTextColor(WHITE);
                display.setCursor(1,1);
                display.print("Door");
                display.setCursor(1,20);
                display.print("Door closed");
                display.display();
             
                makeIFTTTRequest();
                }
//Similarly just by changing UID numbers, many users can be added in this.
//Attendance is being recorded in Google spreadsheet by IFTTT platform connected through WiFi
      }
            
