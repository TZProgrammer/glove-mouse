import serial


baud_rate = 115200; #In arduino, Serial.begin(baud_rate)
serial_port = serial.Serial('COM3', baudrate = baud_rate)

while 1:
    arduinoData = serial_port.readline().split()