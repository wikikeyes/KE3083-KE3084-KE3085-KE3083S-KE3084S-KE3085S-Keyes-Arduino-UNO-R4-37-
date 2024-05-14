/*
 * 名称   : RGB LED
 * 功能   : RGB 点亮
 * 作者   : http://www.keyes-robot.com/ 
*/
int redpin = 9;    // 定义红色LED引脚D9
int greenpin = 10; // 定义绿色LED引脚D10
int bluepin = 11;  // 定义蓝色LED引脚D11
int val;

void setup() {
  pinMode(redpin, OUTPUT);   //设置红色LED引脚为输出模式
  pinMode(greenpin, OUTPUT); //设置绿色LED引脚为输出模式
  pinMode(bluepin, OUTPUT);  //设置蓝色LED引脚为输出模式 
}

void loop() {
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
}
