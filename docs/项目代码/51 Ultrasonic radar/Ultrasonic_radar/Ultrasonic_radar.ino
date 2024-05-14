/*  
 * 名称   : Ultrasonic radar
 * 功能   : 超声波控制四位数管，蜂鸣器和RGB灯模拟超声波雷达
 * 作者   : http://www.keyes-robot.com/ 
*/
#include "TM1650.h" //导入TM1650库文件

//四位数码管的接口为A4和A5
#define DIO A4
#define CLK A5
TM1650 DigitalTube(CLK,DIO);

#define BUZZER_PIN  2    //定义喇叭引脚为D2

int redpin = 9;    // 定义红色LED引脚D9
int greenpin = 10; // 定义绿色LED引脚D10
int bluepin = 11;  // 定义蓝色LED引脚D11

int TrigPin = A0; //设置Trig引脚为A0
int EchoPin = A1; //设置Echo引脚为A1
int distance;     //超声波测量距离

float checkdistance() { //得到的距离
  // 事先给一个短的低电平，以确保一个干净的高脉冲;
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  // 传感器由10微秒或更长时间的高脉冲触发
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  // 从传感器读取信号:一个高电平脉冲
  // 它的持续时间是从发送ping命令到从对象接收回显的时间(以微秒为单位)
  float distance = pulseIn(EchoPin, HIGH) / 58.00;  //转换成距离
  delay(300);
  return distance;
}

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);  // 设置蜂鸣器为输出模式
  
  DigitalTube.setBrightness();  //设置亮度，0- 7，默认值:2
  DigitalTube.displayOnOFF();   //显示打开或关闭，0=显示关闭，1=显示打开，默认值:1
  for(char b=1;b<5;b++){
    DigitalTube.clearBit(b);    //DigitalTube.clearBit(0 to 3); 清空位显示
  }
  
  DigitalTube.displayBit(1,0);  //DigitalTube.Display(bit,number); bit= 0 - 3，number= 0 - 9
  pinMode(TrigPin, OUTPUT);     //设置Trig引脚作为输出
  pinMode(EchoPin, INPUT);      //设置Echo引脚作为输入
 
  pinMode(redpin, OUTPUT);   //设置红色LED引脚为输出模式
  pinMode(greenpin, OUTPUT); //设置绿色LED引脚为输出模式
  pinMode(bluepin, OUTPUT);  //设置蓝色LED引脚为输出模式
}

void loop() {
  distance = checkdistance();//超声波测距
  displayFloatNum(distance); //数码管显示距离
    if (distance <= 10) {   
      analogWrite(redpin, 255);  //RGB LED 亮红色灯
      analogWrite(greenpin, 0);
      analogWrite(bluepin, 0);
      tone(BUZZER_PIN, 262); //DO播放1000ms
      delay(1000);

  } else if (distance > 10 && distance <= 20) {
      analogWrite(redpin, 0);     //RGB LED 亮绿色灯
      analogWrite(greenpin, 255);
      analogWrite(bluepin, 0);
      tone(BUZZER_PIN, 349); //Fa播放500ms
      delay(500);

  } else {
      analogWrite(redpin, 0);    //RGB LED 亮蓝色灯
      analogWrite(greenpin, 0);
      analogWrite(bluepin, 255);
      tone(BUZZER_PIN, 494); //Si播放125ms
      delay(125);
   }
}

void displayFloatNum(float distance){
  if(distance > 9999)
    return;
  int dat = distance*10;
   //DigitalTube.displayDot(2,true); //Bit0 显示点。在displayBit()之前使用。
  if(dat/10000 != 0){
    DigitalTube.displayBit(0, dat%100000/10000);  
    DigitalTube.displayBit(1, dat%10000/1000);
    DigitalTube.displayBit(2, dat%1000/100);
    DigitalTube.displayBit(3, dat%100/10);
    return;
  }
  if(dat%10000/1000 != 0){
    DigitalTube.clearBit(0); 
    DigitalTube.displayBit(1, dat%10000/1000); 
    DigitalTube.displayBit(2, dat%1000/100);
    DigitalTube.displayBit(3, dat%100/10);
    return;
  }
  if(dat%1000/100 != 0){
  DigitalTube.clearBit(0); 
  DigitalTube.clearBit(1);
  DigitalTube.displayBit(2, dat%1000/100);
  DigitalTube.displayBit(3, dat%100/10);  
  return;
}
  DigitalTube.clearBit(0); 
  DigitalTube.clearBit(1);
  DigitalTube.clearBit(2);
  DigitalTube.displayBit(3, dat%100/10);
}