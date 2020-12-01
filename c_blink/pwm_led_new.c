#include <unistd.h>
#include <stdio.h>
#include <wiringPi.h>
#define PIN_PWM 2
#define HIGH 1
#define LOW 0

// void digitalWrite(int pin, int val)
// {
// 	// printf("pin: %d\n", pin);
// 	printf("%c", (val) ? '-': '_');
// }

// void delay(unsigned int timer)
// {
// 	printf("(%d)", timer);
// }


/*
The guaranteed width of the PWM is 1 ms.
Type coercion can distort values.
Valid range of:
	pin:		valid pin #
	dry_cycle:	[1...99]
	freq:		[1...1000]
	timer: 		[-1, 0...99] ~ time of work. -1 infinity loop
*/
void set_pwm(unsigned int pin, unsigned int dry_cycle, unsigned int freq, ssize_t timer)
{
	printf("\ngenerating pwm on %d:\n \
		f = %d, width(%d) for %zu ms\n", pin, freq, dry_cycle, timer);
	float T = 0; // period of wave
	float min_quot = 0;
	float max_quot = 0;
	unsigned int n = 0;
	int signal = 1;

	if (dry_cycle > 100 || freq > 1000 || freq == 0)
		return ;
	T = (float)1000 / (float)freq;
	min_quot = (dry_cycle < 50) ? (T * (float)dry_cycle / (float)100) : T * ((float)1 - (float)dry_cycle / (float)100); // !will be round to int
	if (min_quot < (float)1)
	{
		min_quot = 1;
		printf("WARNING: too high Frequency. PWM behavior may be incorrect. (%f/%f)\n", min_quot, T);
	}
	max_quot = (T - (float)min_quot);
	max_quot = (max_quot < 1) ? 1 : max_quot;
	printf("min: %d, max: %d\n", (unsigned int)min_quot, (unsigned int)max_quot);
	while (n * T < timer || timer == -1)
	{
		if (signal)
		{
			digitalWrite(PIN_PWM, HIGH);
			delay((dry_cycle > 50)? max_quot : min_quot);
		}
		else
		{
			digitalWrite(PIN_PWM, LOW);
			delay((dry_cycle > 50)? min_quot : max_quot);
			n++;
		}
		signal = signal ? 0 : 1;
	}
	digitalWrite(PIN_PWM, LOW);
}



int	main(void)
{
	int dry_cycle;

	// wiringPiSetup();
	dry_cycle = 60;
	digitalWrite(PIN_PWM, HIGH);
	delay(3000);
	digitalWrite(PIN_PWM, LOW);
	// set_pwm(PIN_PWM, dry_cycle, 100, 100);
	return (0);
}
