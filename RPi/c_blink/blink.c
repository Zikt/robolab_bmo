#include <wiringPi.h>
#include <unistd.h>

int	main(void)
{
	int i;
	int dly;

	dly = 500;
	wiringPiSetup();
	pinMode (0, OUTPUT);
	pinMode (2, OUTPUT);
	pinMode (3, OUTPUT);
	i = 0;
	while(i < 100)
	{
		digitalWrite(0, HIGH);
		delay(dly);
		digitalWrite(0, LOW);
		digitalWrite(2, HIGH);
		delay(dly);
		digitalWrite(2, LOW);
		digitalWrite(3, HIGH);
		delay(dly);
		digitalWrite(3, LOW);
		i++;
	}
	return (0);
}
