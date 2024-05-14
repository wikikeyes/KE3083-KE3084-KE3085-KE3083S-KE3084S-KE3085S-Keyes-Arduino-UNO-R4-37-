/*  
 * 名称   : IR Control LED
 * 功能   : 红外遥控RGB模块上的RGB LED亮不同颜色灯
 * 作者   : http://www.keyes-robot.com/ 
*/
#include <Arduino.h>
#include <IRremote.hpp>

#define IR_RECEIVE_PIN  5   // 定义红外接收模块引脚D5
IRrecv irrecv(IR_RECEIVE_PIN);     // 创建一个用于接收类的类对象
decode_results results;     // 创建一个解码结果类对象

int redpin = 9;    // 定义红色LED引脚D9
int greenpin = 10; // 定义绿色LED引脚D10
int bluepin = 11;  // 定义蓝色LED引脚D11

boolean flag = true;  //LED标志钻头

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);  // 启动接收器
  pinMode(redpin, OUTPUT);   //设置红色LED引脚为输出模式
  pinMode(greenpin, OUTPUT); //设置绿色LED引脚为输出模式
  pinMode(bluepin, OUTPUT);  //设置蓝色LED引脚为输出模式
}

void loop() {
  if (IrReceiver.decode()) {
      Serial.print(IrReceiver.decodedIRData.decodedRawData, HEX);  // 打印原始数据
      // IrReceiver.printIRResultShort(&Serial); // 在一行中打印接收到的完整数据
      // IrReceiver.printIRSendUsage(&Serial);  // 打印发送这些数据所需的语句
      handleControl(IrReceiver.decodedIRData.decodedRawData);      // 处理来自远程控制的命令
      IrReceiver.resume(); // 启用接收下一个值
  }
}

void handleControl(unsigned long value){
  if (value == 0xBF40FF00 && flag == true){ // 接收数字“OK” 
    analogWrite(redpin, 255);
    analogWrite(greenpin, 255);
    analogWrite(bluepin, 255);
    Serial.println("  led on");
    flag = false;
  } 
  else if (value == 0xBF40FF00 && flag == false){ // 接收数字“OK”
    analogWrite(redpin, 0);
    analogWrite(greenpin, 0);
    analogWrite(bluepin, 0);
    Serial.println("  led off"); 
    flag = true;
  }
  else if(value == 0xE916FF00){
    analogWrite(redpin, 255);
    analogWrite(greenpin, 0);
    analogWrite(bluepin, 0);
    Serial.println("  red led");

  } 
  else if(value == 0xE619FF00){
    analogWrite(redpin, 0);
    analogWrite(greenpin, 255);
    analogWrite(bluepin, 0);
    Serial.println("  green led");
  } 
  else if(value == 0xF20DFF00){
    analogWrite(redpin, 0);
    analogWrite(greenpin, 0);
    analogWrite(bluepin, 255);
    Serial.println("  blue led");
  }
  else if(value == 0xF30CFF00){
    analogWrite(redpin, 255);
    analogWrite(greenpin, 165);
    analogWrite(bluepin, 0);
    Serial.println("  orange led");
  }
  else if(value == 0xE718FF00){
    analogWrite(redpin, 255);
    analogWrite(greenpin, 255);
    analogWrite(bluepin, 0);
    Serial.println("  yellow led");
  }
  else if(value == 0xA15EFF00){
    analogWrite(redpin, 128);
    analogWrite(greenpin, 0);
    analogWrite(bluepin, 128);
    Serial.println("  purple led");
  }
  else if(value == 0xF708FF00){
    analogWrite(redpin, 255);
    analogWrite(greenpin, 215);
    analogWrite(bluepin, 0);
    Serial.println("  gold led");
  }
  else if(value == 0xE31CFF00){
    analogWrite(redpin, 255);
    analogWrite(greenpin, 192);
    analogWrite(bluepin, 203);
    Serial.println("  pink led");
  }
  else if(value == 0xA55AFF00){
    analogWrite(redpin, 255);
    analogWrite(greenpin, 0);
    analogWrite(bluepin, 255);
    Serial.println("  magenta led");
  }
}