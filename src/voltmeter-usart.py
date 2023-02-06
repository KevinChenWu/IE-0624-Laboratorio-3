#!/usr/bin/python3
import serial

ser = serial.Serial(
	port="/tmp/ttyS1",
	baudrate=9600,
	parity=serial.PARITY_NONE,
	stopbits=serial.STOPBITS_ONE,
	bytesize=serial.EIGHTBITS,
	timeout=0
)

f = open("voltages.csv", "w+")
f.write("V1,V2,V3,V4\n")

print("Connected to: " + ser.portstr)
line = []
count = 0

while True:
	for c in ser.read():
		c = chr(c)
		print(c)
		line.append(c)
		if c == "\n":
			print("Line: " + "".join(line))
			print(len(line))
			if len(line) >= 33 and len(line) <= 41:
				string = "".join(line)
				f.write(string)
			line=[]
