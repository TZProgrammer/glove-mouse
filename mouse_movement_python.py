import pyautogui

sensX = 10
sensY = 10;
scrolling = 3;
noScroll = 0;

movX = 0;
movY = 0;
scroll = 0;

xVal; // read input of the accelerometer in X-axis
yVal; // read input of the accelerometer in Y-axis
  
indexButtonState = 0
middleButtonState = 0

while(1):
  xVal = 20 # read input of the accelerometer in X-axis
  yVal = 20 # read input of the accelerometer in Y-axis
  
  #indexButtonState reading from file
  #middleButtonState reading from file

  if ((indexButtonState and middleButtonState) and ((yVal < -200) || (yVal > 200))):
    if (yVal > 0):
      scroll = scrolling
    else:
      scroll = -1 * scrolling
  else:
    scroll = noScroll
    if (indexButtonState):
      pyautogui.mouseDown(button = 'left')
    elif (!indexButtonState):
      pyautogui.mouseup(button = 'left')
    elif (middleButtonState):
      pyautogui.mouseDown(button = 'right')
    elif (!middleButtonState):
      pyautogui.mouseDown(button = 'right')
    if (((xVal < -100) || (xVal > 100)) || ((yVal < -100) || (yVal > 100))):
      movX = xVal/sensX
      movY = -yVal/sensY
  pyautogui.move(movX, movY)
  pyautogui.scroll(scroll)
