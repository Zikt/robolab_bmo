#include <Servo.h>

Servo servo;  // Создаем объект
void setup() {
  servo.attach(9);   // Указываем объекту класса Servo, что серво присоединен к пину 9
  servo.write(0);   // Выставляем начальное положение 
  pinMode(9, OUTPUT);
  }

void loop() {
  return ; // закомментируй и включи
  servo.write(90); // Поворачиваем серво на 90 градусов
  delay(1000);        
  servo.write(1800);
  delay(1000);        
  servo.write(90);
  delay(1000);
  servo.write(0);
  delay(1000);        
}
