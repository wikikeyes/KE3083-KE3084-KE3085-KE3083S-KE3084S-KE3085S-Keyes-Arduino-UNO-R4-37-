/* 
 * 名称   : Button_control_rgb
 * 功能   : 模拟一个小台灯
 * 作者   : http://www.keyes-robot.com/ 
*/
#define PIN_BUTTON  5  //将自锁按键的引脚连接到D5
int val = 0;            //用于存储键值

int redpin = 9;    // 定义红色LED引脚D9
int greenpin = 10; // 定义绿色LED引脚D10
int bluepin = 11;  // 定义蓝色LED引脚D11

void setup() {
  Serial.begin(9600);//启动串口监视器，设置波特率为9600
  pinMode(PIN_BUTTON, INPUT);  //设置自锁按键的引脚为输入模式
  pinMode(redpin, OUTPUT);   //设置红色LED引脚为输出模式
  pinMode(greenpin, OUTPUT); //设置绿色LED引脚为输出模式
  pinMode(bluepin, OUTPUT);  //设置蓝色LED引脚为输出模式
}

// 循环函数会一直运行下去
void loop() {
  val = digitalRead(PIN_BUTTON);  //读取自锁按键的值并将其赋值给变量val
  Serial.println(val);          //打印变量val的值
  if (val == 0) {             //按下自锁按键时读取到低电平，RGB亮白灯
    analogWrite(redpin, 255);  //给PWM口(D9)写入一个255的模拟值
    analogWrite(greenpin, 255);
    analogWrite(bluepin, 255);
  }
  else {   //按起自锁按键时读取到高电平，RGB不亮
    analogWrite(redpin, 0);  //给PWM口(D9)写入一个0的模拟值
    analogWrite(greenpin, 0);
    analogWrite(bluepin, 0);
  } 
}
