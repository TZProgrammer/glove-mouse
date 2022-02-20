import pyautogui

sensX = 100
sensY = 100
scrolling = 3
noScroll = 0

movX = 0
movY = 0
scroll = 0

xVal = 200 # read input of the accelerometer in X-axis
yVal = 200 # read input of the accelerometer in Y-axis
  
indexButtonState = 0
middleButtonState = 0

while(1):
  xVal = 200 # read input of the accelerometer in X-axis
  yVal = 200 # read input of the accelerometer in Y-axis
  
  #indexButtonState reading from file
  #middleButtonState reading from file

  if ((indexButtonState and middleButtonState) and ((yVal < -200) or (yVal > 200))):
    if (yVal > 0):
      scroll = scrolling
    else:
      scroll = -1 * scrolling
  else:
    scroll = noScroll
    if (indexButtonState):
      pyautogui.mouseDown(button = 'left')
    elif (not indexButtonState):
      pyautogui.mouseUp(button = 'left')
    elif (middleButtonState):
      pyautogui.mouseDown(button = 'right')
    elif (not middleButtonState):
      pyautogui.mouseUp(button = 'right')
    if (((xVal < -100) or (xVal > 100)) or ((yVal < -100) or (yVal > 100))):
      movX = xVal/sensX
      movY = -yVal/sensY
  pyautogui.move(movX, movY)
  pyautogui.scroll(scroll)
