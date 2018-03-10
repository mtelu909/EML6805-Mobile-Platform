/*
* Advanced Robotic Design
*       Midterm Exam Part 1
*                
* by Mackenson Telusma
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN

float Drive = 0;
float Turn = 0;
int center_value = 512;
int PWM_max = 100;

//Motor 1
int EN_A = 5; //Left side
int IN_1 = 3;
int IN_2 = 4;

//Motor 2
int EN_B = 6; //Right side
int IN_3 = 9;
int IN_4 = 10; 

const byte address[][6] = {"00001","00002"};

void setup() {
  //Serial.begin(9600);
  
  radio.begin();
  radio.openReadingPipe(0, address[0]);
  radio.openReadingPipe(0, address[1]);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  pinMode(EN_A,OUTPUT);
  pinMode(IN_1,OUTPUT);
  pinMode(IN_2,OUTPUT);
  pinMode(EN_B,OUTPUT);
  pinMode(IN_3,OUTPUT);
  pinMode(IN_4,OUTPUT);

  analogWrite(EN_A, 80);
  analogWrite(EN_B, 80);

  //Serial.print("Forward-Reverse Value");
  //Serial.print("\t");
  //Serial.print("Left-Right Value");
  //Serial.print("\n");
}
void loop() {
  while (radio.available()) {
    int potValue_updown = 0;
    int potValue_leftright = 0;

    radio.read(&potValue_leftright, sizeof(potValue_leftright));
    delay(100);
    radio.read(&potValue_updown, sizeof(potValue_updown));

    Drive = map(potValue_updown, 1023, 0, -PWM_max, PWM_max);
    if(Drive < -PWM_max)
      Drive = -PWM_max;
      else if(Drive > PWM_max)
        Drive = PWM_max;
    Turn = map(potValue_leftright,0, 1023, -PWM_max, PWM_max);
    if(Turn < -PWM_max)
      Turn = -PWM_max;
      else if(Turn > PWM_max)
        Turn = PWM_max;
        
 if(Turn >-20 && Turn < 20)
  {
//Setting up the conditions for forward and reverese movement 
   if(Drive > -20 && Drive < 20)
   {
    Drive = 0;
   }
   else if(Drive > 20)
    {
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
        
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
    } 
    else if(Drive < -20)
    {
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
    
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      Drive = abs(Drive);
    }
      analogWrite(EN_A,abs(Drive));
      analogWrite(EN_B,abs(Drive));
  }
  else if(Turn < -20)
  {
    digitalWrite(IN_1, HIGH);
    digitalWrite(IN_2, LOW);
        
    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, HIGH);
    
    analogWrite(EN_A,abs(Turn));
    analogWrite(EN_B,abs(Turn));
  }
  else if(Turn > 20)
  {
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, HIGH);
        
    digitalWrite(IN_3, HIGH);
    digitalWrite(IN_4, LOW);

    analogWrite(EN_A,Turn);
    analogWrite(EN_B,Turn);
  }   

    //Serial.print(Drive);
    //Serial.print("\t");
    //Serial.print(Turn);
    //Serial.print("\n");
       
  }
}
