import RPi.GPIO as GPIO
from time import sleep
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
GPIO.setup(37,GPIO.OUT,initial=GPIO.LOW)

while True:
	GPIO.output(37,GPIO.HIGH)
	sleep(1)
	GPIO.output(37, GPIO.LOW)
	sleep(1)
