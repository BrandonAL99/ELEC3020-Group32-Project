#include <esp_now.h>
#include <WiFi.h>

uint8_t broadcastAddress[] = {0x30,0x30,0xf9,0x59,0xc6,0xb0}; //receiver MAC address


typedef struct struc_inputs { //setup of datastructure which data is sent in, matches sender
  int start;
  int select;
  int button1;
  int button2;
  int button3;
  int button4;
  int button5;
  int button6;
  int JoyUp;
  int JoyDown;
  int JoyLeft;
  int JoyRight;
  }struc_inputs; //aliase that means we don't have to type struct every time defining structure

int Pin_button1=1; //pin number definitions
int Pin_button2=2;
int Pin_button3=3;
int Pin_button4=10;
int Pin_button5=11;
int Pin_button6=12;
int Pin_JoyUp = 13;
int Pin_JoyDown = 16;
int Pin_JoyLeft = 21;
int Pin_JoyRight = 17;
int Pin_start = 18;
int Pin_select = 44;

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
  pinMode(Pin_button1,INPUT_PULLUP); //pin definitions
  pinMode(Pin_button2,INPUT_PULLUP);
  pinMode(Pin_button3,INPUT_PULLUP);
  pinMode(Pin_button4,INPUT_PULLUP);
  pinMode(Pin_button5,INPUT_PULLUP);
  pinMode(Pin_button6,INPUT_PULLUP);
  pinMode(Pin_start,INPUT_PULLUP);
  pinMode(Pin_select,INPUT_PULLUP);
  pinMode(Pin_JoyUp,INPUT_PULLUP);
  pinMode(Pin_JoyDown,INPUT_PULLUP);
  pinMode(Pin_JoyLeft,INPUT_PULLUP);
  pinMode(Pin_JoyRight,INPUT_PULLUP);
  
}


void loop() {

  input_var.button1 = !digitalRead(Pin_button1);
  input_var.button2 = !digitalRead(Pin_button2);
  input_var.button3 = !digitalRead(Pin_button3);
  input_var.button4 = !digitalRead(Pin_button4);
  input_var.button5 = !digitalRead(Pin_button5);
  input_var.button6 = !digitalRead(Pin_button6);
  input_var.JoyUp = !digitalRead(Pin_JoyUp);
  input_var.JoyDown = !digitalRead(Pin_JoyDown);
  input_var.JoyLeft = !digitalRead(Pin_JoyLeft);
  input_var.JoyRight = !digitalRead(Pin_JoyRight);
  
 esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &input_var, sizeof(input_var));

  /*if (result == ESP_OK) {
   Serial.println("Sent with success");
   } else {
       Serial.println("Error sending data");
    }
  
  delay(10);  // Small delay to allow other tasks
} */
