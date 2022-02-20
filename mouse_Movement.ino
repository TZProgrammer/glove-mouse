#include <Mouse.h>


const float sensX = 10;
const float sensY = 10;
const int scrolling = 3;
const int noScroll = 0;

char movX = 0;
char movY = 0;
char scroll = 0;

char xVal; // read input of the accelerometer in X-axis
char yVal; // read input of the accelerometer in Y-axis
  
const int indexButtonPin = 1;
const int middleButtonPin = 2;
  
int indexButtonState = 0;
int middleButtonState = 0;

void setup() {
  // put your setup code here, to run once:
  
  pinMode(indexButtonPin, OUTPUT);
  pinMode(middleButtonPin, OUTPUT);

  Mouse.begin();
  
}

void loop() {
  // put your main code here, to run repeatedly:

  xVal = 20; // read input of the accelerometer in X-axis
  yVal = 20; // read input of the accelerometer in Y-axis
  
  indexButtonState = digitalRead(indexButtonPin);
  middleButtonState = digitalRead(middleButtonPin);

  if ((indexButtonState && middleButtonState) && ((yVal < -200) || (yVal > 200))){
    if (yVal > 0){
       scroll = scrolling;
    }
    else{
      scroll = -1 * scrolling;
    }
  }
  else{
    scroll = noScroll;
    if (indexButtonState){
      if (Mouse.isPressed()){
        Mouse.release(MOUSE_LEFT);
      }
      else{
         Mouse.press(MOUSE_LEFT);
      }
    }
    else if (middleButtonState){
      if (Mouse.isPressed()){
        Mouse.release(MOUSE_RIGHT);
      }
      else{
         Mouse.press(MOUSE_RIGHT);
      }
    }
    else{
      if (((xVal < -100) || (xVal > 100)) || ((yVal < -100) || (yVal > 100))){
        movX = xVal/sensX;
        movY = yVal/sensY;
      }
    }
  }
  Mouse.move(movX, movY, scroll);
}
