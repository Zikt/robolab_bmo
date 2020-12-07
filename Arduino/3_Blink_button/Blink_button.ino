/*
О вреде использования delay...
https://alexgyver.ru/lessons/interrupts/

Вопрос встал после того, как была написана собственная функция для формирования ШИМ-сигнала.
Если в программе используется функция delay, то следует иметь в виду, что во время спячки,
процессор не будет обрабатывать сигналы на других пинах, например, проспит нажатие на кнопку.
Рассмотрим программу:
*/

/*
const int led_pin = 13;
const int button_pin = 2;
boolean button;

void setup() {
  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  button = !digitalRead(button_pin);
  Serial.print("Button: ");Serial.println(button);
  digitalWrite(led_pin, HIGH);
  delay(1000);
  digitalWrite(led_pin, LOW);
  delay(1000);
}

/*
Как видим, программа реагирует на нажатие кнопки, только во время "бодрствования"

Одно из наиболее простых решений проблемы - это прибегнуть к помощи дополнительных устройств и опций,
встроенных в плату Arduino. Одна из опций - аппаратное прерывание.

Что это?

Дело в том, что процессор не отдает свою работу встроенным в плату устройствам,
а всего лишь прерывает свою работу, если эти устройства обращаются к нему.
Процессор обрабатывает этот запрос, а затем продолжит работу с места останова.
Параллельных вычислений в Arduino нет!

Подключается прерывание при помощи функции attachInterrupt(pin, handler, mode):
  pin – номер прерывания
  handler – имя функции-обработчика прерывания (её нужно создать самому)
  mode – “режим” работы прерывания:
      LOW (низкий) – срабатывает при сигнале LOW на пине
      RISING (рост) – срабатывает при изменении сигнала на пине с LOW на HIGH
      FALLING (падение) – срабатывает при изменении сигнала на пине с HIGH на LOW 
      CHANGE (изменение) – срабатывает при изменении сигнала (с LOW на HIGH и наоборот)
*/

/*
const int led_pin = 13;
const int button_pin = 2;
boolean button;

void setup() {
  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT_PULLUP);
  Serial.begin(9600);

  attachInterrupt(0, button_handler, FALLING);                                        
}

void button_handler(){  
  button = !digitalRead(button_pin);
  Serial.print("Button: ");Serial.println(button);
}

void loop() {
  digitalWrite(led_pin, HIGH);
  delay(1000);
  digitalWrite(led_pin, LOW);
  delay(1000);
}

/*
*Важная информация мелким шрифтом где-то внизу

1.  Нумерация пинов в attachInterrupt:
  pin = 0 !!! т.к. отсчет ведется только по пинам
  поддерживающим аппаратные прерывания (у nano (D2, D3))

2.  В handler не работают функции времени (delay, millis...)

3.  Если handler изменяет значение глобальной переменной, то эта переменная должна быть
  объявлена как тип volatile.

4.  На мониторе можно увидеть "дребезг контакта" при нажатии кнопки. С ним тоже придется бороться.
*/


/*
  Рассмотрим использование перемнной типа volatile на примере изменения флага в аппаратном прерывании.
  Показать поведение перенной flag с volatile и без него.
*/
const int led_pin = 13;
const int button_pin = 2;
boolean button;
int flag = 0;
//volatile int flag = 0;

void setup() {
  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT_PULLUP);
  Serial.begin(9600);

  attachInterrupt(0, button_handler, FALLING);                                        
}

void button_handler(){
  flag = 1;         // меняем значение флага
}

void loop() {
  flag = 0;         // где-то было задано значение
  digitalWrite(led_pin, HIGH);
  delay(1000);
  digitalWrite(led_pin, LOW);
  delay(1000);

  if (flag != 0){
    button = !digitalRead(button_pin);
    Serial.println("tick"); 
    flag = 0;
  }
}
