#include <esp_now.h>
#include <WiFi.h>

uint8_t broadcastAddress[] = {0x30,0x30,0xf9,0x59,0xc6,0xb0}; //receiver MAC address


typedef struct struc_inputs { //setup of datastructure which data is sent in
  int buttonA;
  int buttonB;
  int buttonX;
  int buttonY;
  int buttonJoy;
  int JoyX;
  int JoyY;
  }struc_inputs; //aliase that means we don't have to type struct every time defining structure

int Pin_buttonA=1; //pin number definitions
int Pin_buttonB=2;
int Pin_buttonX=3;
int Pin_buttonY=10;
int Pin_buttonJoy=16;
int Pin_JoyX=12;
int Pin_JoyY=13;

struc_inputs input_var; //creates an instance of the defined structure
esp_now_peer_info_t peerInfo; //variable to store info about peer

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) { //when called sends a message to receiver ensuring connection is made
//  Serial.print("\r\nLast Packet Send Status:\t");
 // Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail"); //? operator just performs an if else statemnt
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) { //initialize esp now
  Serial.println("Error initializing ESP-NOW");
  return;
  }
  esp_now_register_send_cb(OnDataSent); //sends message to receiver/esures connection

  //Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6); //copies  defined peer mac adress to peer structure so esp now knows where to send data
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  //Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  pinMode(Pin_buttonA,INPUT_PULLUP); //pin definitions
  pinMode(Pin_buttonB,INPUT_PULLUP);
  pinMode(Pin_buttonX,INPUT_PULLUP);
  pinMode(Pin_buttonY,INPUT_PULLUP);
  pinMode(Pin_buttonJoy,INPUT_PULLUP);
  pinMode(Pin_JoyX,INPUT);
  pinMode(Pin_JoyY,INPUT);
  
}


void loop() {

  input_var.buttonA = !digitalRead(Pin_buttonA);
  input_var.buttonB = !digitalRead(Pin_buttonB);
  input_var.buttonX = !digitalRead(Pin_buttonX);
  input_var.buttonY = !digitalRead(Pin_buttonY);
  input_var.buttonJoy = !digitalRead(Pin_buttonJoy);
  input_var.JoyX = analogRead(Pin_JoyX);
  input_var.JoyY = analogRead(Pin_JoyY);
  Serial.print("\n");
 Serial.print(analogRead(Pin_JoyY));
 Serial.print(analogRead(Pin_JoyX));
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &input_var, sizeof(input_var));

  //if (result == ESP_OK) {
   //Serial.println("Sent with success");
 //  } else {
 //      Serial.println("Error sending data");
 //   }
  
  delay(10);  // Small delay to allow other tasks
}
