#include <unistd.h>
#include <stdio.h>
#define PIN_PWM 2
#define HIGH 1
#define LOW 0

void digitalWrite(int pin, int val)
{
	// printf("pin: %d\n", pin);
	printf("%c", (val) ? '-': '_');
}

void delay(int timer)
{
	printf("(%d)", timer);
}

void set_pwm(int pin, float dry_cycle, int timer, int freq)
{
	printf("\ngenerating pwm on %d:\n \
		f = %d, width(%f) for %d ms\n", pin, freq, dry_cycle, timer);
	float T = 0; // period of wave
	int n = 0;
	int signal = 1;
	T = 1000 / freq;		/*delay in ms for set freq*/
	while (n * T < timer || timer == -1)
	{
		if (signal)
		{
			digitalWrite(PIN_PWM, HIGH);
			delay(T * dry_cycle / 100);
		}
		else
		{
			digitalWrite(PIN_PWM, LOW);
			delay(T * (1 - dry_cycle / 100));
			n++;
		}
		signal = signal ? 0 : 1;
	}
	digitalWrite(PIN_PWM, LOW);
}



int	main(void)
{
	int dry_cycle;
	int dly;

	dly = 500;
	// wiringPiSetup();
	dry_cycle = 20;
	printf("checking...\n");
	digitalWrite(PIN_PWM, HIGH);
	delay(3000);
	digitalWrite(PIN_PWM, LOW);
	set_pwm(PIN_PWM, dry_cycle, 1000, 10);
	return (0);
}
