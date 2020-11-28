import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)
GPIO.setup(22,GPIO.OUT)
GPIO.output(22,GPIO.HIGH)
time.sleep(1)
GPIO.output(22,GPIO.LOW)
if GPIO.input(22):
	print("Pin is high")
