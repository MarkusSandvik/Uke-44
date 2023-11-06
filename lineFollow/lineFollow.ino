#include <Wire.h>
#include <Zumo32U4.h>

#define NUM_SENSORS 5

const uint16_t maxSpeed = 400;
const uint16_t minSpeed = 0;
uint16_t speed = 200;
uint16_t correctionSpeed = 100;

Zumo32U4LineSensors lineSensors;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;

Zumo32U4OLED display;

int16_t lastError = 0;

#define NUM_SENSORS 5
unsigned int lineSensorValues[NUM_SENSORS];

unsigned long previousMillis = 0;
const long interval = 5;


void sensorCalibrating(){
    delay(1000);
    for (int i = 0; i < 120; i++){
        motors.setSpeeds(-200,200);
        lineSensors.calibrate();
    } // end for
    motors.setSpeeds(0,0);
} // end void

void lineFollow(){
    int position = lineSensors.readLine(lineSensorValues);
    
    //speed = constrain(speed, minSpeed, maxSpeed);

    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval){
        previousMillis = currentMillis;

        
        if (position == 1000){
            motors.setSpeeds(speed,speed);
        } // end if
        

        else if (position > 1000){
            motors.setSpeeds(speed, correctionSpeed);
        } // end else if

        else if (position < 1000){
            motors.setSpeeds(correctionSpeed, speed);
        } // end else if

        else {
            motors.setSpeeds(speed,speed);
        } // end else
    } // end if
} // end void

void setup(){
    lineSensors.initFiveSensors();

    //loadCustomCharacters();
    
    // Wait for button A to be pressed and released.
    display.clear();
    display.print(F("Press A"));
    display.gotoXY(0, 1);
    display.print(F("to calib"));
    buttonA.waitForButton();

    sensorCalibrating();
    //showReadings();
} // end setup

void loop(){
    lineFollow();
} // end loop



//////Kopierte funksjoner for testing///////

void loadCustomCharacters()
{
  static const char levels[] PROGMEM = {
    0, 0, 0, 0, 0, 0, 0, 63, 63, 63, 63, 63, 63, 63
  };
  display.loadCustomCharacter(levels + 0, 0);  // 1 bar
  display.loadCustomCharacter(levels + 1, 1);  // 2 bars
  display.loadCustomCharacter(levels + 2, 2);  // 3 bars
  display.loadCustomCharacter(levels + 3, 3);  // 4 bars
  display.loadCustomCharacter(levels + 4, 4);  // 5 bars
  display.loadCustomCharacter(levels + 5, 5);  // 6 bars
  display.loadCustomCharacter(levels + 6, 6);  // 7 bars
}

void printBar(uint8_t height)
{
  if (height > 8) { height = 8; }
  const char barChars[] = {' ', 0, 1, 2, 3, 4, 5, 6, (char)255};
  display.print(barChars[height]);
}

// Shows a bar graph of sensor readings on the display.
// Returns after the user presses A.
void showReadings()
{
  display.clear();

  while(!buttonA.getSingleDebouncedPress())
  {
    lineSensors.readCalibrated(lineSensorValues);

    display.gotoXY(0, 0);
    for (uint8_t i = 0; i < NUM_SENSORS; i++)
    {
      uint8_t barHeight = map(lineSensorValues[i], 0, 1000, 0, 8);
      printBar(barHeight);
    }
  }
}