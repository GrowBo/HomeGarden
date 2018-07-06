import serial
import csv

ser = serial.Serial('/dev/ttyACM0',9600)
s = [0,1]
while True:
	read_serial=ser.readline()
	s[0] = str(int (ser.readline(),16))
	print s[0]
	print read_serial
	with open('thefile.csv', 'rb') as f:
	  data = list(csv.reader(f))
	import collections
	counter = collections.defaultdict(int)
	for row in data:
	    counter[row[0]] = s[0]
	writer = csv.writer(open("/newdatafile", 'w'))
	for row in data:
		writer.writerow(row)
