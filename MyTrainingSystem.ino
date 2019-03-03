#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include  <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // RX | TX
MPU6050 accelgyro;  
int16_t  ax, ay, az;
int16_t  gx, gy, gz;

#define flex_pin0 A0
//#define flex_pin1 A1
#define flex_pin2 A2
#define flex_pin3 A3#define flex_pin0 A0
#define flex_pin1 A1
#define flex_pin2 A2
#define flex_pin3 A3
  
bool blinkState = false;

bool sensorState=false;

char a=1;

bool onoff1=false;
bool onoff2=true;
bool onoff3=false;
  
void setup() {
  
    Wire.begin();
    Serial.begin(9600);
    BTSerial.begin(9600);//藍芽出廠預設值
    accelgyro.initialize();
    pinMode(flex_pin0, INPUT);
 }
 void loop() {
  
if (BTSerial.available()){
  a=BTSerial.read();
  Serial.print(a);
}
  
  
  if(a=='1'){
      onoff1=true;
      onoff2=false;
      onoff3=false;
  }
  if(a=='2'){
      onoff1=false;
      onoff2=true;
      onoff3=false;
  }
   if(a=='3'){
      onoff1=false;
      onoff2=false;
      onoff3=true;
  }
//遊戲一：握力運動＿彎曲感測
  if(onoff1){
   getFlexSensor();
   getFlexSensor1();
//   getThrow();
//    getThrow1();
  }
//遊戲二、三：上肢運動、螞蟻上樹＿mpu6050六感測元件
  if(onoff2){
    getThrow();
    getThrow1();
  }
  
//mpu6050六感測元件其他測試
   if(onoff3){
      getMpu60503();
      getMpu60503_1();
  }

}



void getFlexSensor(){
  //int flex_value0 = map(analogRead(flex_pin0), 0, 850, 0, 100);
//  int flex_value1 = map(analogRead(flex_pin1), 0, 160, 0, 100);
//  int flex_value2 = map(analogRead(flex_pin2), 0, 160, 0, 100);
//  int flex_value3 = map(analogRead(flex_pin3), 0, 160, 0, 100);
  //int led_value = map(flex_value0, 0, 1023, 0, 255);
  //analogWrite(led_pin, led_value);
  BTSerial.print("F");
  BTSerial.print("X");BTSerial.print(analogRead(flex_pin0));
  BTSerial.print("Y");BTSerial.print(analogRead(flex_pin0));
//  BTSerial.print("c");BTSerial.print(flex_value2);
//  BTSerial.print("d");BTSerial.print(flex_value3);
  BTSerial.println("E");
  delay(200);
}


void getFlexSensor1(){
  //int flex_value0 = map(analogRead(flex_pin0), 0, 850, 0, 100);
//  int flex_value1 = map(analogRead(flex_pin1), 0, 160, 0, 100);
//  int flex_value2 = map(analogRead(flex_pin2), 0, 160, 0, 100);
//  int flex_value3 = map(analogRead(flex_pin3), 0, 160, 0, 100);
  //int led_value = map(flex_value0, 0, 1023, 0, 255);
  //analogWrite(led_pin, led_value);
  Serial.print("F");
  Serial.print("X");Serial.print(analogRead(flex_pin0));
  Serial.print("Y");Serial.print(analogRead(flex_pin0));
//  BTSerial.print("c");BTSerial.print(flex_value2);
//  BTSerial.print("d");BTSerial.print(flex_value3);
  Serial.println("E");
  delay(200);
}





void getThrow(){
  
   accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
   Serial.print("F");
   Serial.print("X"); Serial.print(atan2(ax,az)*180/PI);
   Serial.print("Y"); Serial.print((float)gy/16.4);
   Serial.print("Z"); Serial.print(atan2(ay,az)*180/PI);
   Serial.println("E:");
   delay(200);
}

void getThrow1(){
  
   accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
   BTSerial.print("F");
   BTSerial.print("X"); BTSerial.print(atan2(ax,az)*180/PI);
   BTSerial.print("Y"); BTSerial.print((float)gy/16.4);
   BTSerial.print("Z"); BTSerial.print(atan2(ay,az)*180/PI);
   BTSerial.println("E");
   delay(200);
}




void getMpu6050(){

   accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    BTSerial.print("F");
    BTSerial.print("X");BTSerial.print((float)ax/16384);    
    BTSerial.print("x"); BTSerial.print((float)gx/131);
    BTSerial.print("Y");BTSerial.print((float)ay/16384); 
    BTSerial.print("y"); BTSerial.print((float)gy/131);
    BTSerial.print("Z");BTSerial.print((float)az/16384);
    BTSerial.print("z"); BTSerial.print((float)gz/131);
    BTSerial.println("E");
    blinkState = !blinkState;
    delay(200);
}

void getMpu60502(){

   accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    //Serial.print("F");
//    Serial.print("ax:");    Serial.print((float)ax/16384);    
//    Serial.print("gx:");    Serial.println((float)gx/131);
    Serial.print("X軸角度:");Serial.println(atan2(ax,az)*180/PI);
    Serial.print("Y軸角加度:");    Serial.println((float)gy/131);
    Serial.println("-----------------------------------");   
//    Serial.print("ay:");    Serial.print((float)ay/16384); 
//    Serial.print("gy:");    Serial.println((float)gy/131);
//    Serial.print("Y軸角度:");Serial.println(atan2(ay,az)*180/PI);
//    Serial.print("X軸角加度:");    Serial.println((float)gx/131);
//    Serial.println("-----------------------------------");   

    
//    Serial.print("az:");    Serial.print((float)az/16384);
//    Serial.print("gz:");    Serial.println((float)gz/131);
//    Serial.print("Z1軸角度:");Serial.println(atan2(az,ax)*180/PI);
//    Serial.print("Z2軸角度:");Serial.println(atan2(az,ay)*180/PI);

    //Serial.println("E");
    blinkState = !blinkState;
    delay(200);
}

void getMpu60503(){

    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    BTSerial.print("F");
    BTSerial.print("X");BTSerial.print(atan2(ax,az)*180/PI);
    BTSerial.print("Y");BTSerial.print((float)gy/131);
    BTSerial.println("E");

    blinkState = !blinkState;
    delay(200);
}

void getMpu60503_1(){

    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    Serial.print("F");
    Serial.print("X");Serial.print(atan2(ax,az)*180/PI);
    Serial.print("Y");Serial.print((float)gy/131);
    Serial.println("E");

    blinkState = !blinkState;
    delay(200);
}
