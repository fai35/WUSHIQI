#include <Servo.h>

const int buttonPins[10] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; // 按键引脚
const int buzzerPin = 12; // 蜂鸣器引脚
const int servoPin = 13; // 舵机引脚

Servo myServo;

const String correctPassword = "12345"; // 正确密码
String inputPassword = ""; // 输入的密码
int attemptCount = 0; // 尝试次数

void setup() {
    for (int i = 0; i < 10; i++) {
        pinMode(buttonPins[i], INPUT_PULLUP);
    }
    pinMode(buzzerPin, OUTPUT);
    myServo.attach(servoPin);
    myServo.write(0); // 初始位置，门锁关闭
    Serial.begin(9600);
}

void loop() {
    for (int i = 0; i < 10; i++) {
        if (digitalRead(buttonPins[i]) == LOW) {
            delay(200); // 防抖
            inputPassword += String(i);
            Serial.println(inputPassword);
            if (inputPassword.length() == 5) {
                if (inputPassword == correctPassword) {
                    Serial.println("密码正确，门锁打开");
                    myServo.write(90); // 打开门锁
                    delay(5000); // 保持门锁打开5秒
                    myServo.write(0); // 关闭门锁
                } else {
                    attemptCount++;
                    Serial.println("密码错误");
                    if (attemptCount >= 3) {
                        Serial.println("尝试次数过多，蜂鸣器报警");
                        for (int j = 0; j < 5; j++) {
                            digitalWrite(buzzerPin, HIGH);
                            delay(500);
                            digitalWrite(buzzerPin, LOW);
                            delay(500);
                        }
                    }
                }
                inputPassword = ""; // 重置输入密码
            }
        }
    }
}