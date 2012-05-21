import serial
import win32com.client as win32
import sys
import time
#downloaded win32com from: http://sourceforge.net/projects/pywin32/
#this website helped me: http://www.blog.pythonlibrary.org/2010/07/16/python-and-microsoft-office-using-pywin32/
#downloaded serial lib from http://sourceforge.net/projects/pyserial/
#pyserial website: http://pyserial.sourceforge.net/index.html

numArgs = len(sys.argv)
if numArgs == 3:  #make sure you have the correct number of args
	powerDelay = int(sys.argv[1])
	captureDelay = int(sys.argv[2])

	print "power delay : " + str(powerDelay)
	print "capture delay : " + str(captureDelay)

	captureDelaySeconds = captureDelay/1000.0  #calculate capture delay in seconds for use in while loop below

	shell = win32.Dispatch("WScript.Shell")#create shell object?
	ser = serial.Serial(3)  #connect to com4

	ser.write(powerDelay) #send the power delay (in milliseconds) to the arduino
	while 1:
		line = ser.readline() #wait for serial data and a newline
		print line
		line = line[0:5]
		if line == "ENTER":
			time.sleep(captureDelaySeconds)
			shell.SendKeys(" ") #send space key to press button on screen
else:
	print "wrong number of arguments"