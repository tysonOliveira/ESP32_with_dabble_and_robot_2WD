/*
   Gamepad module provides three different mode namely Digital, JoyStick and Accerleometer.

   You can reduce the size of library compiled by enabling only those modules that you want to
   use. For this first define CUSTOM_SETTINGS followed by defining INCLUDE_modulename.

   Explore more on: https://thestempedia.com/docs/dabble/game-pad-module/
*/
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>

#define IN1 27
#define IN2 26
#define IN3 33
#define IN4 32

void moveForward();
void moveBack();
void moveLeft(uint8_t direction1[]);
void moveRight(uint8_t direction2[]);
void stop();
void speedUp();
void slowDown();

uint8_t left_F[] = {1,0,0,0};
uint8_t right_F[] = {0,0,1,0};
uint8_t left_B[] = {0,1,0,0};
uint8_t right_B[] = {0,0,0,1};

int speed = 200;

uint8_t flag = 0;
uint8_t flagD = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);      // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin("MyEsp32");       //set bluetooth name of your device

  pinMode(IN4, OUTPUT);
  pinMode(IN3, OUTPUT); 
  pinMode(IN2, OUTPUT);
  pinMode(IN1, OUTPUT); 
     
  ledcSetup(0, 30000, 8); // channel, frequency, resolution
  ledcAttachPin(14, 0); // pin, channel

  ledcSetup(1, 30000, 8); // channel, frequency, resolution
  ledcAttachPin(25, 0); // pin, channel
}

void loop() {
  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.  
    
  if (GamePad.isUpPressed()){
    flag = 1;
  }

  if (!GamePad.isUpPressed() && flag){
    speed < 255 ? (speed += 5) : (speed = speed);      
    
    flag = 0;   
  }

  if (GamePad.isDownPressed()){
    flagD = 1;
  }

  if (!GamePad.isDownPressed() && flagD){
    speed > 0 ? (speed -= 5) : (speed = speed);      
        
    flagD = 0;
  } 
  
  if (GamePad.isCrossPressed() && !GamePad.isLeftPressed() && !GamePad.isRightPressed()) {
    Serial.println("Frente");
    moveForward();           
  } else if (GamePad.isCrossPressed() && GamePad.isLeftPressed()) {
    Serial.println("Esquerda para frente");
    moveLeft(left_F);    
  } else if (GamePad.isCrossPressed() && GamePad.isRightPressed()) {
    Serial.println("Direita para frente");
    moveRight(right_F);    
  } else if (GamePad.isTrianglePressed() && !GamePad.isLeftPressed() && !GamePad.isRightPressed()) {
    Serial.println("para tras");
    moveBack();           
  } else if (GamePad.isTrianglePressed() && GamePad.isLeftPressed()) {
    Serial.println("Esquerda para tras");    
    moveLeft(left_B);    
  } else if (GamePad.isTrianglePressed() && GamePad.isRightPressed()) {
    Serial.println("DIreita para tras");
    moveRight(right_B);    
  } else {
    Serial.println("Parar");
    stop();    
  } 
}

void moveForward() {
  ledcWrite(1, speed);
  digitalWrite(IN3, HIGH); 
  digitalWrite(IN4, LOW);
  ledcWrite(0, speed);    
  digitalWrite(IN1, HIGH); 
  digitalWrite(IN2, LOW);
}

void moveBack() {
  ledcWrite(1, speed);
  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, HIGH);
  ledcWrite(0, speed);    
  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, HIGH);  
}

void moveLeft(uint8_t direction1[]) {
  ledcWrite(1, speed);
  digitalWrite(IN3, direction1[0]);       // HIGH
  digitalWrite(IN4, direction1[1]);
  ledcWrite(0, speed);    
  digitalWrite(IN1, direction1[2]); 
  digitalWrite(IN2, direction1[3]); 
}

void moveRight(uint8_t direction2[]) {
  ledcWrite(1, 0);
  digitalWrite(IN3, direction2[0]); 
  digitalWrite(IN4, direction2[1]);
  ledcWrite(0, speed);    
  digitalWrite(IN1, direction2[2]);       // HIGH
  digitalWrite(IN2, direction2[3]);  
}

void stop() {
  ledcWrite(1, 0);
  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, LOW);
  ledcWrite(0, 0);    
  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, LOW);
}

void speedUp() {
      
}

void slowDown() {
  
}
