/*  
 * 名称   : sound-controlled lights
 * 功能   : 声音传感器控制RGB模块上的RGB LED亮灭
 * 作者   : http://www.keyes-robot.com/ 
*/
int microPin = A0;  //定义声音传感器的控制引脚为A0
int redpin = 9;    // 定义红色LED引脚D9
int greenpin = 10; // 定义绿色LED引脚D10
int bluepin = 11;  // 定义蓝色LED引脚D11

void setup() {
  Serial.begin(9600); //波特率设置为9600
  pinMode(microPin, INPUT);  //设置声音传感器的引脚为输入模式
  pinMode(redpin, OUTPUT);   //设置红色LED引脚为输出模式
  pinMode(greenpin, OUTPUT); //设置绿色LED引脚为输出模式
  pinMode(bluepin, OUTPUT);  //设置蓝色LED引脚为输出模式
}

void loop() {
  int val = analogRead(microPin); //读取模拟值
  Serial.print(val); // 串口打印
  if(val > 150){ //超过阈值
    analogWrite(redpin, 255);  //给PWM口(D9)写入一个255的模拟值
    analogWrite(greenpin, 255);
    analogWrite(bluepin, 255);
    Serial.println(" led on"); 
    delay(5000);
  }else{ //否则
    analogWrite(redpin, 0);  //给PWM口(D9)写入一个0的模拟值
    analogWrite(greenpin, 0);
    analogWrite(bluepin, 0);
    Serial.println(" led off");
  }
  delay(100);
}