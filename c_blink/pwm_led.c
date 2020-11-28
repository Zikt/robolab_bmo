#include <wiringPi.h>
#include <unistd.h>
#include <stdio.h>
#define PIN_PWM 2

void set_pwm(int pin, int dry_cycle, int time)
{
	const int PWM_FREQ = 200;
	int dly = 0;
	int i = 0;
	int j = 0;
	dly = 1000 / PWM_FREQ;		/*delay in ms for set freq*/
	while (j * dly < time || time == -1)
	{
		if (i == PWM_FREQ)
			i = 0;
		if (i < PWM_FREQ * dry_cycle / 100)
			digitalWrite(PIN_PWM, HIGH);
		else
			digitalWrite(PIN_PWM, LOW);
		i++;
		j++;
		delay(dly);
	}
	digitalWrite(PIN_PWM, LOW);
	return ;
}



int	main(void)
{
	int dry_cycle;
	int dly;

	dly = 500;
	wiringPiSetup();
	pinMode (PIN_PWM, OUTPUT);
	dry_cycle = 70;
	/*checking...*/
	digitalWrite(PIN_PWM, HIGH);
	delay(3000);
	digitalWrite(PIN_PWM, LOW);

	set_pwm(PIN_PWM, dry_cycle, 10000);
	/*
	digitalWrite(PIN_PWM, HIGH);
	if (PIN_PWM == 2)
		delay(10000);
	digitalWrite(PIN_PWM, LOW);*/
	return (0);
}
