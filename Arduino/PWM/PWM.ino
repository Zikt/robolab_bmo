#include <GyverPWM.h>

void setup() {
  pinMode(3, OUTPUT);

  // Данные функции НЕ УБИРАЮТ один ШИМ выход у 8-ми битных таймеров, оставляя нам ШИМ пины D3, D5, D9 и D10 на ATmega328
  PWM_set(3, 123);
//  /PWM_prescaler(3, 7);  // установить частоту ШИМ на пине D3 равной 31.4 кГц (см. таблицу №2 в GyverPWM.h)
  // частота автоматически будет установлена для пина D11!
}

void loop() {
  // можем пользоваться ШИМом на всех 6-ти пинах!
  PWM_frequency(3, 2, 0);
  
//  analogWrite(3, 200); /// from 256
}
