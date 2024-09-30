#include "project_files.h";

//TFT_eSPI tft = TFT_eSPI();



 
//unsigned long lastPrintTime;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) { //copies incoming data to data structure
  memcpy(&Controller_data, incomingData, sizeof(Controller_data));

/*unsigned long currentTime = millis();
 if (currentTime - lastPrintTime >= 1000) {
  lastPrintTime = currentTime;
  Serial.print("\r");
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Up: ");
  Serial.println(Controller_data.JoyUp);
  Serial.print("Down: ");
  Serial.println(Controller_data.JoyDown);
  Serial.print("Left: ");
  Serial.println(Controller_data.JoyLeft);
    Serial.print("Right: ");
  Serial.println(Controller_data.JoyRight);
  Serial.println("1:");
  Serial.println(Controller_data.button1);
  Serial.println("2:");
  Serial.println(Controller_data.button2);
  Serial.println("3:");
  Serial.println(Controller_data.button3);
  Serial.println("4:");
  Serial.println(Controller_data.button4);
  Serial.println("5:");
  Serial.println(Controller_data.button5);
  Serial.println("6:");
  Serial.println(Controller_data.button6);
  Serial.println("Start:");
  Serial.println(Controller_data.start);
  Serial.println("select:");
  Serial.println(Controller_data.select);
  } */

}
 
void controller_setup() {
  struc_inputs Controller_data;
  /*
  tft.init();
  tft.setRotation(1);  
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
 
  Serial.begin(115200);
  
  */
  WiFi.mode(WIFI_STA);

  
  if (esp_now_init() != ESP_OK) { //Init ESP-NOW
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to get recv packer info
  esp_now_register_recv_cb((OnDataRecv));
}
 
/*
void loop() {
  //tft.fillRect(10, 10, 100, 20, TFT_BLACK); //fillredact no longer needed. Can be used for analog joystick
  tft.setCursor(10, 10);
  tft.printf("1:%d",Controller_data.button1);
  //tft.fillRect(10, 30, 100, 20, TFT_BLACK);
  tft.setCursor(10, 30);
  tft.printf("2:%d",Controller_data.button2);
  tft.setCursor(10, 50);
  tft.printf("3:%d",Controller_data.button3);
  tft.setCursor(10, 70);
  tft.printf("4:%d",Controller_data.button4);
  tft.setCursor(10, 90);
  tft.printf("5:%d",Controller_data.button5);
  tft.setCursor(10, 110);
  tft.printf("6:%d",Controller_data.button6);
  tft.setCursor(10, 130);
  tft.printf("start:%d",Controller_data.start);
  tft.setCursor(10, 150);
  tft.printf("select:%d",Controller_data.select);
  tft.setCursor(120, 10);
  tft.printf("JoyUp:%d",Controller_data.JoyUp);
  tft.setCursor(120, 30);
  tft.printf("JoyDown:%d",Controller_data.JoyDown);
  tft.setCursor(120, 50);
  tft.printf("JoyLeft:%d",Controller_data.JoyLeft);
  tft.setCursor(120, 70);
  tft.printf("JoyRight:%d",Controller_data.JoyRight);

delay(10);

}

*/