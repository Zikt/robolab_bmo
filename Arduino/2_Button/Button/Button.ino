/*
О чтении сигнала на дискретном пине...
(https://alexgyver.ru/lessons/digital/)

Подключаем к пину значение +5В через кнопку:

 _____/ ____
|           |
+          pin

*/

/*
const int button_pin = 2;
boolean button;

void setup() {
  pinMode(button_pin, INPUT);
  Serial.begin(9600);
}

void loop() {
  button = digitalRead(button_pin);
  Serial.print("Button: ");Serial.println(button);
}

*/
/*
...в результате получаем наводки, когда кнопка разомкнута. Чтобы избежать
наводок необхоидмо подключить резистор большого сопротивления 10 кОм и замкнуть пин к земле:

 ___/ ____rrrrr____
|       |          |
+      pin         -

Теперь при размыкании кнопки все наводки уходят "в землю". 
Такой резистор называется PULL-DOWN (тянет к земле)


Однако схема усложнилась, появился лишний резистор. К счастью, эту проблему решили и пины 
Arduino уже имеют подтягивающие резисторы, но с одной оговоркой, он подключен не к земле,
как на схеме выше, а к питанию:

 ___/ ____rrrrr____
|       |          |
-      pin         +

Такой подтягивающий резистор называется PULL-UP (тянущий к питанию).
Как видим, для корректной работы необходимо подключить пин через ключ к земле.
При разомкнутой кнопке на пин поступает сигнал 1, при замкнутой - сигнал уходит в
землю и на пине - 0.

Чтобы задействовать, встроенный резистор, необходимо установить его в режим INPUT_PULLUP:

*/


const int button_pin = 2;
boolean button;

void setup() {
  pinMode(button_pin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  button = !digitalRead(button_pin);                // инвертировать!
  Serial.print("Button: ");Serial.println(button);
}
