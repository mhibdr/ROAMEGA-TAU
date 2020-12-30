// Die liberiry, die wie es benuzen werden

#include <Arduino.h>
#include <Servo.h>
#include <math.h>

// PIN-Definition

#define S1PIN 0x0a
#define S2PIN 0x0b
#define S3PIN 0x0c
#define S4PIN 0x0d
#define S5PIN 0x09
#define STATE 0x08
#define SVDT  0x07
#define RUPA  0x06
#define OPEN  0x05
#define CLOSE 0x04
#define Joy_Y   A0
#define Joy_X   A1
#define Joy_B   A2
#define Joy_Y_1 A3
#define Joy_X_1 A4
#define Joy_B_1 A5
#define PotM    A6
#define L1      200 // Test
#define L2      150 // Test
#define L3      130
/*
#define MAX_SAngle    90
#define MAX_Speed    10 
#define MIN_Speed    2000
#define MAX_Distance 350
*/

// Varibalen und device definition

Servo S1 , S2 , S3 , S4 , S5;
String com;
int S1POS , S2POS , S3POS , S4POS , S5POS;
int S1PPOS , S2PPOS , S3PPOS , S4PPOS , S5PPOS;
int X_Cordinates , Y_Cordintes , Z_Cordinates;
int Joy_X_Val , Joy_Y_Val , Joy_B_Val , Joy_X_Val_1 , Joy_Y_Val_1 , Joy_B_Val_1  ;
int index = 0 , TIMEOUT = 0 , RNPU = 0;
int delay_val = 20;
float angle1 , angle2 , angle3;
float Distance , H;
int joy = 0;
int S1POSA[50] , S2POSA[50] , S3POSA[50] , S4POSA[50] , S5POSA[50] , SPEED[50];

int connectionstate = LOW;


void blink(){
  
  digitalWrite(SVDT , HIGH);
  delay(10);
  digitalWrite(SVDT , LOW);
  delay(10);
  
}

void deletpos(){

       memset(S1POSA , 0 , sizeof(S1POSA));
       memset(S2POSA , 0 , sizeof(S2POSA));
       memset(S3POSA , 0 , sizeof(S3POSA));
       memset(S4POSA , 0 , sizeof(S4POSA));
       memset(S5POSA , 0 , sizeof(S5POSA));
       index = 0;
}

void runsaved(){

  while(RNPU != 2){
    
    for (int i = 0 ; i < index - 1 ; i++){

      Joy_B_Val = analogRead(Joy_B);
      Joy_B_Val = map(Joy_B_Val , 0 , 1023 , 0 , 500);
      
      if(Joy_B_Val > 300){
      
        RNPU = 0;
      
        while(RNPU != 1 || RNPU != 2){
          
          Joy_B_Val = analogRead(Joy_B);
          Joy_B_Val = map(Joy_B_Val , 0 , 1023 , 0 , 500);

          Joy_B_Val_1 = analogRead(Joy_B);
          Joy_B_Val_1 = map(Joy_B_Val , 0 , 1023 , 0 , 500);
          
          if(Joy_B_Val_1 > 300 && Joy_B_Val < 300){
      
            RNPU = 1;
      
          }
          if(Joy_B_Val_1 > 300 && Joy_B_Val < 300){
            RNPU = 2;
            break;
          }

        }
      }

      // servo 1
      if(S1POSA[i] == S1POSA[i+1]){
      }
      if (S1POSA[i] > S1POSA[i + 1]) {
          for ( int j = S1POSA[i]; j >= S1POSA[i + 1]; j--) {
            S1.write(j);
            delay(delay_val);
          }
       }
       if (S1POSA[i] < S1POSA[i + 1]) {
         for ( int j = S1POSA[i]; j <= S1POSA[i + 1]; j++) {
           S1.write(j);
            delay(delay_val);
         }
      }
      // Servo 2
      if(S2POSA[i] == S2POSA[i+1]){
      }
      if (S2POSA[i] > S2POSA[i + 1]) {
          for ( int j = S2POSA[i]; j >= S2POSA[i + 1]; j--) {
           S2.write(j);
           delay(delay_val);
         }
        }
      if (S2POSA[i] < S2POSA[i + 1]) {
        for ( int j = S2POSA[i]; j <= S2POSA[i + 1]; j++) {
          S2.write(j);
          delay(delay_val);
        }
      }
      //Servo 3
      if(S3POSA[i] == S3POSA[i+1]){
      }
      if (S3POSA[i] > S3POSA[i + 1]) {
        for ( int j = S3POSA[i]; j >= S3POSA[i + 1]; j--) {
          S3.write(j);
          delay(delay_val);
        }
      }
      if (S3POSA[i] < S3POSA[i + 1]) {
        for ( int j = S3POSA[i]; j <= S3POSA[i + 1]; j++) {
          S3.write(j);
          delay(delay_val);
        }
    }
    //Servo 4
      if(S4POSA[i] == S4POSA[i+1]){
      }
      if (S4POSA[i] > S4POSA[i + 1]) {
        for ( int j = S4POSA[i]; j >= S4POSA[i + 1]; j--) {
          S4.write(j);
          delay(delay_val);
        }
      }
      if (S4POSA[i] < S4POSA[i + 1]) {
        for ( int j = S4POSA[i]; j <= S4POSA[i + 1]; j++) {
          S4.write(j);
          delay(delay_val);
        }
    }
    // Servo 5
      if(S5POSA[i] == S5POSA[i+1]){
      }
      if (S5POSA[i] > S5POSA[i + 1]) {
        for ( int j = S5POSA[i]; j >= S5POSA[i + 1]; j--) {
          S5.write(j);
          delay(delay_val);
        }
      }
      if (S5POSA[i] < S5POSA[i + 1]) {
        for ( int j = S5POSA[i]; j <= S5POSA[i + 1]; j++) {
          S5.write(j);
          delay(delay_val);
        }
      }
    }
  }
}

// wenn Atduion ist zu erste dingen die gemacht werden

void setup() {
  
  S1.attach(S1PIN);
  S1PPOS = S1.read();
  S2.attach(S2PIN);
  S2PPOS = S2.read();
  S3.attach(S3PIN);
  S3PPOS = S3.read();
  S4.attach(S4PIN);
  S4PPOS = S4.read();
  S5.attach(S5PIN);
  S5PPOS = S5.read();


  pinMode (STATE , INPUT);
  pinMode (Joy_X, INPUT);
  pinMode (Joy_Y, INPUT);
  pinMode (Joy_B, INPUT);

  pinMode (Joy_X_1, INPUT);
  pinMode (Joy_Y_1, INPUT);
  pinMode (Joy_B_1, INPUT);

  pinMode (PotM , INPUT);

  pinMode (SVDT , OUTPUT);
  pinMode (RUPA , OUTPUT);

  Serial1.begin(9600);    // Fur HC-06 aber wenn wir HC-05 Benuztuen verden es soll 34800 sein  
  Serial1.setTimeout(1);

}

//Unser Robot funktonen

void loop() {

  connectionstate = digitalRead(STATE);

  while(connectionstate == HIGH){
    
    com = Serial1.readString();
        
    delay_val = analogRead(PotM);

    delay_val = map(delay_val, 0 , 1023 , 5 , 70);

    if(com.startsWith("s1")){            // Z servo
      String CMD = com.substring(2 ,com.length());
      S1POS = CMD.toInt();
      if(S1POS > S1PPOS){
        for(int i = S1PPOS ; i < S1POS ; i++){
          S1.write(i);
          delay(delay_val);
        }
      }
      if(S1POS < S1PPOS){
        for(int i = S1PPOS ; i > S1POS ; i--){
          S1.write(i);
          delay(delay_val);
        }
    }
    S1PPOS = S1POS;
  }

    if(com.startsWith("s2")){                   // X servo
      String CMD = com.substring(2 ,com.length());
      S2POS = CMD.toInt();
      if(S2POS > S2PPOS){
        for(int i = S2PPOS ; i < S2POS ; i++){
          S2.write(i);
          delay(delay_val);
        }
      }
      if(S2POS < S2PPOS){
        for(int i = S2PPOS ; i > S2POS ; i--){
          S2.write(i);
          delay(delay_val);
        }
    }
    S2PPOS = S2POS;
  }

    if(com.startsWith("s3")){                     // Rotation Servo , Y servo
      String CMD = com.substring(2 ,com.length());
      S3POS = CMD.toInt();
      if(S3POS > S3PPOS){
        for(int i = S3PPOS ; i < S3POS ; i++){
          S3.write(i);
          delay(delay_val);
        }
      }
      if(S3POS < S3PPOS){
        for(int i = S3PPOS ; i > S3POS ; i--){
          S3.write(i);
          delay(delay_val);
        }
    }
    S3PPOS = S3POS;
  }

    if(com.startsWith("s4")){                         // Gripper Servo
      String CMD = com.substring(2 ,com.length());
      S4POS = CMD.toInt();
      if(S4POS > S4PPOS){
        for(int i = S4PPOS ; i < S4POS ; i++){
          S4.write(i);
          delay(delay_val);
        }
      }
      if(S4POS < S4PPOS){
        for(int i = S4PPOS ; i > S4POS ; i--){
          S4.write(i);
          delay(delay_val);
        }
    }
    S4PPOS = S4POS;
  }

      if(com.startsWith("s5")){                         // Gripper Servo
      String CMD = com.substring(2 ,com.length());
      S5POS = CMD.toInt();
      if(S5POS > S5PPOS){
        for(int i = S5PPOS ; i < S5POS ; i++){
          S5.write(i);
          delay(delay_val);
        }
      }
      if(S5POS < S5PPOS){
        for(int i = S5PPOS ; i > S5POS ; i--){
          S5.write(i);
          delay(delay_val);
        }
      }
    S5PPOS = S5POS;
  }

    if(com.startsWith("speed")){                         // Die Geschwindeigkeit des Servo
      delay_val = com.substring(5 , com.length()).toInt();
    }
    
    connectionstate = digitalRead(STATE);
  }
 
  // Control with Joystick KY-04
  
  while(connectionstate == LOW){
    {
    angle1 = ((90 - S1POS ) * PI) / 180;
    angle2 = ((90 - S2POS ) * PI) / 180;

    Joy_X_Val = analogRead(Joy_X);
    Joy_Y_Val = analogRead(Joy_Y);
    Joy_B_Val = analogRead(Joy_B);


    Joy_X_Val = map(Joy_X_Val , 0 , 1023 , 180 , 0);
    Joy_Y_Val = map(Joy_Y_Val , 0 , 1023 , 180 , 0);
    Joy_B_Val = map(Joy_B_Val , 0 , 1023 , 0 , 500);
    
    Joy_X_Val_1 = analogRead(Joy_X_1);
    Joy_Y_Val_1 = analogRead(Joy_Y_1);
    Joy_B_Val_1 = analogRead(Joy_B_1);

    Joy_X_Val_1 = map(Joy_X_Val_1 , 0 , 1023 , 180 , 0);
    Joy_Y_Val_1 = map(Joy_Y_Val_1 , 0 , 1023 , 180 , 0);
    Joy_B_Val_1 = map(Joy_B_Val_1 , 0 , 1023 , 0 , 500);

    delay_val = analogRead(PotM);

    delay_val = map(delay_val, 0 , 1023 , 5 , 70);
    }

    if(Joy_X_Val > 110 && S1PPOS < 180 ){
        S1PPOS++;
        S1.write(S1PPOS);
        delay(delay_val);
    }
    
    if(Joy_X_Val < 90 && S1PPOS > 0 ){
        S1PPOS--;
        S1.write(S1PPOS);
        delay(delay_val);
    }

    if(Joy_Y_Val > 110 && S2PPOS < 180 ){
        S2PPOS++;
        S2.write(S2PPOS);
        delay(delay_val);
    }
    
    if(Joy_Y_Val < 90 && S2PPOS > 0 ){
        S2PPOS--;
        S2.write(S2PPOS);
        delay(delay_val);
    }

    if(Joy_X_Val_1 > 110 && S3PPOS < 180){
        S3PPOS++;
        S3.write(S3PPOS);
        delay(delay_val);
    }

    if(Joy_X_Val_1 < 90 && S3PPOS > 0){
      S3PPOS--;
      S3.write(S3PPOS);
      delay(delay_val);
    }

    if(Joy_Y_Val_1 > 110 && S4PPOS < 180) {
      S4PPOS++;
      S4.write(S4POS);
      delay(delay_val);
    }
    
    if(Joy_Y_Val_1 < 90 && S4PPOS > 0) {
      S4PPOS--;
      S4.write(S4POS);
      delay(delay_val);
    }

    if(digitalRead(OPEN) == HIGH && S5PPOS < 180){
      S5PPOS++;
      S5.write(S5PPOS);
      delay(delay_val);
    }

    if(digitalRead(CLOSE) == HIGH && S5PPOS > 120){
      S5PPOS--;
      S5.write(S5PPOS);
      delay(delay_val);
    }
   if(Joy_B_Val > 300 ){

     S1POSA[index] = S1.read();
     S2POSA[index] = S2.read();
     S3POSA[index] = S3.read();
     S4POSA[index] = S4.read();
     S5POSA[index] = S5.read();
     SPEED [index] = delay_val;
     index++;

   }

   if(Joy_B_Val_1 > 300){
        runsaved();
        RNPU = 1;
      }

    if((Joy_B_Val_1 > 300 && Joy_B_Val > 300) || RNPU == 2){
      if(TIMEOUT == 2500){
        deletpos();
        blink();
        TIMEOUT = 0;
        RNPU = 0;
      }
      TIMEOUT++;
    }else {
      TIMEOUT = 0;
    }
    
    connectionstate = digitalRead(STATE);

   }

  }



/* void InverseKinematik(float X , float Y , float Z){
 
  angle1 = acos();
  S2PPOS = (angle1 * 180 / PI).toInt();
  angle2 = 
  S4PPOS = (angle2 * 180 / PI).toInt();
  angle3 = 
  S3PPOS = (angle3 * 180 / PI).toInt();

}

int Vorwartskinematik(int S2PPOS , int  S4PPOS , int S3PPOS){
  
  angle1 = ((S2PPOS * PI) / 180);
  angle2 = ((S4PPOS * PI) / 180);
  angle3 = ((S3PPOS * PI) / 180);
  X_Cordinates = ( L1 * cos(angle1) ) + ( L2 * sin(angle2) );
  Y_Cordintes =  (X_Cordinates * cos(angle3));
  Z_Cordinates = ( L1 * sin(angle1) ) + ( L2 * cos(angle2) ) + L3;
  return X_Cordinates , Y_Cordintes , Z_Cordinates;
}
*/