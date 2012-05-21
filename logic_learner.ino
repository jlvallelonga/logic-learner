int btnPin = 3;
int printerPwrPin = 7;
boolean lastButton = LOW;
boolean currentValue = LOW;
int powerDelay = 0;
int powerOnTime = 10000;

char inData[20];
char inChar = -1;
byte index = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(btnPin, INPUT);
  pinMode(printerPwrPin, OUTPUT);
}

void serialEvent() {
  //get the power delay from the computer
  while (Serial.available() > 0) {
    if (index < 19) {
      inChar = Serial.read();
      inData[index] = inChar;
      index++;
      inData[index] = '\0'; //gets overwritten if there is more data
    }
    delay(30);  //delay so that data from computer has time to fill up the buffer
  }
  powerDelay = atoi(inData); //convert the char array to an integer
  Serial.print("powerDelay: "); //send out power delay to computer output
  Serial.println(powerDelay);  //   just to make sure it's correct
}

void loop() {
  index = 0;
  //wait for button to be pressed
  currentValue = debounce(lastButton, btnPin);
  if (lastButton == LOW && currentValue == HIGH) {
    Serial.println("ENTER");
    delay(powerDelay); //delay for time specified on the computer
    digitalWrite(printerPwrPin, HIGH); //turn printer on
    delay(powerOnTime); //wait for printer to finish starting up
    digitalWrite(printerPwrPin, LOW); //turn printer off
  }
  lastButton = currentValue;
}

//based on example code from Jeremy Blum:
//http://www.jeremyblum.com/2011/01/10/arduino-tutorial-2-now-with-more-blinky-things/
boolean debounce(boolean lastValue, int switchPin) {
  boolean currentValue = digitalRead(switchPin);
  if (lastValue != currentValue) {
    delay(8);
    currentValue = digitalRead(switchPin);
  }
  return currentValue;
}
