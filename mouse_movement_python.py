import pyautogui
import serial
import time

sensitivity = 1
sensX = 5
sensY = 5
scrolling = 3
noScroll = 0

indexButtonState  = 0
middleButtonState = 0

movX = 0
movY = 0
scroll = 0

baud_rate = 115200; #In arduino, Serial.begin(baud_rate)
serial_port = serial.Serial('COM3', baudrate = baud_rate)

time.sleep(1)

while(1):
  try:
    arduinoData = serial_port.readline().decode('ASCII')

    arduinoData = arduinoData.split(' ')

    xVal = float(arduinoData[0])
    yVal = float(arduinoData[1])

    prevIndexButtonState = indexButtonState
    indexButtonState  = int(arduinoData[3][0])

    prevMiddleButtonState = middleButtonState
    middleButtonState = int(arduinoData[4][0])


    #print(arduinoData)
  except:
    continue
  #print(xVal)
  
  #indexButtonState reading from file
  #middleButtonState reading from file
  if(((xVal < -10/sensitivity) or (xVal > 10/sensitivity)) or ((yVal < -10/sensitivity) or (yVal > 10/sensitivity))) or (((xVal > -200/sensitivity) or (xVal < 200/sensitivity)) or ((yVal > -200/sensitivity) or (yVal < 200/sensitivity))):
    movX = xVal/sensX
    movY = yVal/sensY
    pyautogui.move(movX, movY)

    
  # if ((indexButtonState and middleButtonState)):
  #     if (yVal > 0):
  #       scroll = scrolling
  #     else:
  #       scroll = -1 * scrolling
  # else:
  #   scroll = noScroll
  if (indexButtonState):
    pyautogui.mouseDown(button = 'left')
  elif (prevIndexButtonState == 1):
    pyautogui.mouseUp(button = 'left')
  if (middleButtonState):
    pyautogui.mouseDown(button = 'right')
  elif (prevMiddleButtonState == 1):
    pyautogui.mouseUp(button = 'right')
  #pyautogui.scroll(scroll)