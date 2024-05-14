/*  
 * 名称   : PIR alarm
 * 功能   : PIR控制蜂鸣器和SK6812 RGB模块
 * 作者   : http://www.keyes-robot.com/ 
*/
#define PIR_PIN  5     //PIR运动传感器控制引脚为D5
#define BUZZER_PIN  8  //定义有源蜂鸣器控制引脚为D8
int item = 0;

int redpin = 9;    // 定义红色LED引脚D9
int greenpin = 10; // 定义绿色LED引脚D10
int bluepin = 11;  // 定义蓝色LED引脚D11
int val;

void setup() {
  Serial.begin(9600);//启动串口监视器，设置波特率为9600
  pinMode(PIR_PIN, INPUT);  //设置PIR运动传感器的引脚为输入模式
  pinMode(BUZZER_PIN, OUTPUT); //设置有源蜂鸣器的引脚为输出模式
  pinMode(redpin, OUTPUT);   //设置红色LED引脚为输出模式
  pinMode(greenpin, OUTPUT); //设置绿色LED引脚为输出模式
  pinMode(bluepin, OUTPUT);  //设置蓝色LED引脚为输出模式
}

void loop() {
  item = digitalRead(PIR_PIN);//读取红外热释传感器输出的数字信号
  Serial.println(item);          //打印变量item的值
  if (item == 1) {  //运动检测
    digitalWrite(BUZZER_PIN, HIGH); //打开蜂鸣器
    for(val = 0; val < 255; val++){  //val的值不断由0增加到255
      analogWrite(bluepin, val);  //给PWM口(D11)写入一个0 ~ 255的模拟值
      analogWrite(greenpin, 255-val);
      analogWrite(redpin, 128-val);
      delay(3); 
      }
    for(val = 255; val > 0; val--){  //val的值不断由255减少到0
      analogWrite(bluepin, val);
      analogWrite(greenpin, 255-val);
      analogWrite(redpin, 128-val);
      delay(3); 
      }
  } else {  //没有检测到任何信号或数据
    digitalWrite(BUZZER_PIN, LOW); //关掉蜂鸣器
    analogWrite(bluepin, 0);
    analogWrite(greenpin, 0);
    analogWrite(redpin, 0);
  }
}