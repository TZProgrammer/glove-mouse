import pyautogui
import serial
import time

baud_rate = 115200; #In arduino, Serial.begin(baud_rate)
serial_port = serial.Serial('COM3', baudrate = baud_rate, timeout = 1)

serial_port.write('s'.encode())

sensitivity = 1
sensX = 5
sensY = 5
scrolling = 3
noScroll = 0

tVelocity = 0
xVelocity = 0
yVelocity = 0

indexButtonState  = 0
middleButtonState = 0

movX = 0
movY = 0
scroll = 0

time.sleep(1)

while(1):
  try:
    serial_port.write('s'.encode())
  
    arduinoData = serial_port.readline().decode('ASCII')

    arduinoData = arduinoData.split(' ')

    xVal = float(arduinoData[0])
    yVal = float(arduinoData[1])

    tVelocity = (xVelocity**2+yVelocity**2)**(1/2)
    xVelocity += xVal/10
    # xVelocity -= 1/120*tVelocity
    yVelocity += yVal/10
    # xVelocity -= 1/120*tVelocity

    print(xVal)

    # if ((xVal > -100) and (xVal < 100) and (yVal > -100) and (yVal < 100) and ((xVelocity > -60) and (xVelocity < 60) and (yVelocity > -60) and (yVelocity < 60))):
    #   xVelocity = 0
    #   yVelocity = 0

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
  if(((xVal < 5) or (xVal > -5)) or ((yVal < -5) or (yVal > 5))):
    movX = xVelocity/sensX
    movY = yVelocity/sensY
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