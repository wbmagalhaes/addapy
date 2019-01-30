import RPi.GPIO as GPIO
import addapy
from adc_consts import *

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)

PIN_DRDY = 11
GPIO.setup(PIN_DRDY, GPIO.IN)

gain = ADS1256_GAIN['1']
rate = ADS1256_DRATE['10']
mode = ADS1256_SMODE['SINGLE_ENDED']
addapy.start_adda(gain, rate, mode)

adcChannel = 0
dacChannel = 0

addapy.write_volts(0, 0.0)
addapy.write_volts(1, 0.0)

def print_volt(volt):
	print("Reading: {:.3f} mV    ".format(volt * 1000), end="\r", flush=True)

def readVolts(ch):
	if ch == PIN_DRDY:
		addapy.read_adc()
		
		volt = addapy.get_channel_volts(adcChannel)
		addapy.write_volts(dacChannel, volt)
		print_volt(volt)

GPIO.add_event_detect(PIN_DRDY, GPIO.FALLING, callback=readVolts)

while True:
	pass
