#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_SHIELD

#include <OneSheeld.h>

//Motor 1
int EN_A = 5; //Left side
int IN_1 = 3;
int IN_2 = 4;

//Motor 2
int EN_B = 6; //Right side
int IN_3 = 9;
int IN_4 = 10; 

int PWM_max = 100;
int PWM_min = 85;

// Ultra-sonic Sensors
// Sensor 1 - Front
 int distance1 = 0;
 int echopin_front = 13;
 int trigpin_front = 12;
 
// Sensor 2 - Left
 int distance2 = 0;
 int echopin_left = 8;
 int trigpin_left = 11;
 
// Sensor 3 - Right
 int distance3 = 0;
 int echopin_right = 2;
 int trigpin_right = 7;
  
void setup() 
{
  OneSheeld.begin();
  
  pinMode(EN_A,OUTPUT);
  pinMode(IN_1,OUTPUT);
  pinMode(IN_2,OUTPUT);
  pinMode(EN_B,OUTPUT);
  pinMode(IN_3,OUTPUT);
  pinMode(IN_4,OUTPUT);

  analogWrite(EN_A, 80);
  analogWrite(EN_B, 80);
}

void stop_drive(){
  analogWrite(EN_A, 0);
  analogWrite(EN_B, 0);
}

// Function that allows the unit to move forward
void forward_drive(){
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
        
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);

  analogWrite(EN_A, PWM_max);
  analogWrite(EN_B, PWM_max);
}

// Function that allows the unit to move backwards
void reverse_drive(){
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
    
  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW); 
       
  analogWrite(EN_A,PWM_max);
  analogWrite(EN_B,PWM_max);
}

// Function that turns the unit to the left
void left_turn(){
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
        
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
    
  analogWrite(EN_A,PWM_min);
  analogWrite(EN_B,PWM_min);
}

// Function that turns the unit to the right
void right_turn(){
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
        
  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);

  analogWrite(EN_A,PWM_min);
  analogWrite(EN_B,PWM_min);
}
void loop() 

{
  // put your main code here, to run repeatedly:
  if ((GamePad.isUpPressed()||GamePad.isDownPressed()||GamePad.isRightPressed()||GamePad.isLeftPressed())== false)
  {
    stop_drive();
  }
  else if(GamePad.isUpPressed())
    {
      forward_drive(); 
    }
  else if(GamePad.isDownPressed())
  {
    reverse_drive();
  }
  else if(GamePad.isRightPressed())
  {
    left_turn();
  }
  else if(GamePad.isLeftPressed())
  {
    right_turn();
  }

}
