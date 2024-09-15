#include <esp_now.h>
#include <WiFi.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();


typedef struct struc_inputs { //setup of datastructure which data is sent in, matches sender
  int buttonA;
  int buttonB;
  int buttonX;
  int buttonY;
  int buttonJoy;
  int JoyX;
  int JoyY;
  }struc_inputs; //aliase that means we don't have to type struct every time defining structure


struc_inputs Controller_data; 
unsigned long lastPrintTime;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) { //copies incoming data to data structure
  memcpy(&Controller_data, incomingData, sizeof(Controller_data));

//unsigned long currentTime = millis();
 //if (currentTime - lastPrintTime >= 1000) {
 //   lastPrintTime = currentTime;
  //Serial.print("\r");
  //Serial.print("Bytes received: ");
  //Serial.println(len);
 //Serial.print("x: ");
  //Serial.println(Controller_data.JoyX);
 // Serial.print("y: ");
 // Serial.println(Controller_data.JoyY);
 // Serial.println("A:");
 // Serial.println(Controller_data.buttonA);
 // Serial.println("B:");
 // Serial.println(Controller_data.buttonB);
  //Serial.println("X:");
  //Serial.println(Controller_data.buttonX);
 // Serial.println("Y:");
 // Serial.println(Controller_data.buttonY);
   // Serial.println("Joy_Button:");
  //Serial.println(Controller_data.buttonJoy);
  
;

//}
}
 
void setup() {
  tft.init();
  tft.setRotation(1);  
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
 
  Serial.begin(115200);
  
  
  WiFi.mode(WIFI_STA);

  
  if (esp_now_init() != ESP_OK) { //Init ESP-NOW
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to get recv packer info
  esp_now_register_recv_cb((OnDataRecv));
}
 
void loop() {
  tft.fillRect(10, 10, 100, 20, TFT_BLACK);
  tft.setCursor(10, 10);
  tft.printf("x%d",Controller_data.JoyX);
  tft.fillRect(10, 30, 100, 20, TFT_BLACK);
  tft.setCursor(10, 30);
  tft.printf("y%d",Controller_data.JoyY);
  tft.setCursor(10, 50);
  tft.printf("A%d",Controller_data.buttonA);
  tft.setCursor(10, 70);
  tft.printf("B%d",Controller_data.buttonB);
  tft.setCursor(10, 90);
  tft.printf("X%d",Controller_data.buttonX);
  tft.setCursor(10, 110);
  tft.printf("Y%d",Controller_data.buttonY);
  tft.setCursor(10, 130);
  tft.printf("buttonJoy%d",Controller_data.buttonJoy);

delay(10);

}