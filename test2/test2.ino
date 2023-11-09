#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4OLED display;
Zumo32U4Encoders encoders;
Zumo32U4Buzzer buzzer;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonC buttonC;

// Variables for softwareBattery
int8_t batteryLevel = 100;
long lastDistance = 0;
float consumptionMeasure = 0;
int8_t timesCharged = 0;
unsigned long batteryMillis = 0;

// Variables for hiddenFeature()
bool hiddenActivated = false;
bool emergencyChargingUsed = false;
bool emergencyChargeMode = false;

// Variables for showBatteryStatus()
unsigned long previousMillis = 0;
unsigned long refreshPreviousMillis = 0;
const long onInterval = 10000;
const long offInterval = 2000;
const long refreshInterval = 500;
long displayTime = 0;
bool batteryDisplayed = false;

// Variables for speedometer
int16_t previousCountLeft = 0;
int16_t previousCountRight = 0;

// Variables for regneDistanse()
int16_t lastAverage = 0;
long distance = 0;
unsigned long distanceMillis = 0;



///////// TEST VARIABLES ////
int batteryHealth = 2;
float iAmSpeed = 0;



void setup(){
    Serial.begin(9600);
    // Wait for button A to be pressed and released.
    display.clear();
    display.print(F("Press A"));
    display.gotoXY(0, 1);
    display.print(F("to start"));
    buttonA.waitForButton();
    
} // end setup

void loop(){
    softwareBattery();
    showBatteryStatus();
    regneDistanse();
    speedometer();
    if (buttonA.isPressed())
    {
        motors.setSpeeds(200, 200);
    }
    else if (buttonC.isPressed())
    {
        motors.setSpeeds(-400, -400);
    }
    else
    {
        motors.setSpeeds(0, 0);
    }
} // end loop

float speedometer(){
    static uint8_t lastDisplayTime;

    long countsLeft = encoders.getCountsLeft();
    long countsRight = encoders.getCountsRight();
    if ((uint8_t)(millis() - lastDisplayTime) >= 100)
    {
        int16_t newCountLeft = countsLeft - previousCountLeft;
        int16_t newCountRight = countsRight - previousCountRight;
        int16_t avrage = (newCountLeft+newCountRight)/2;
        float distanse = 75.81*12;
        float oneRound = 122.5221135;
        float meters = avrage/distanse*oneRound;
        //Serial.println(meters);
        previousCountLeft = countsLeft;
        previousCountRight = countsRight;
        //display.clear();
        //display.print(meters);
        lastDisplayTime = millis();
        iAmSpeed = meters;
        return meters;
    } // end if
} // end void

void regneDistanse(){
    int currentMillis = millis();

    if (currentMillis - distanceMillis > 100){
        // Millis funksjon
        long countsLeft = encoders.getCountsLeft();     // Get amount of encoder readings
        long countsRight = encoders.getCountsRight();   

        long average = (countsLeft + countsRight)/2;    // Uses the average of the encoder readings

        float round = 75.81*12;                         // Calculation of wheelrotation
        int diffAverage = abs(average-lastAverage);     // use the absolute value to count distance both forward and backward
        distance += (diffAverage/round)*12.5221135;
        
        lastAverage = average;                          // Make current readings as reffrence for next run's calculations
        distanceMillis = currentMillis;
    } // end if
} // end void


void softwareBattery(){
    long currentMillis = millis();

    if (currentMillis - batteryMillis > 100){
    batteryMillis = currentMillis;
    consumptionMeasure += (abs(iAmSpeed)/30); // EKSEMPEL PÅ FUNKSJON, OPPDATER NÅR VI TESTER MED DATA
    Serial.print(consumptionMeasure);
    } // end if

    if (consumptionMeasure >= 10){
        batteryLevel -= 1;
        consumptionMeasure = 0;
    } // end if
} // end void

void carNeedCharging(){
    if (batteryLevel < 10){ // Gir forvarsel med Lyd, lys og display

    } // end if

    if (batteryLevel < 5){ // Stopper hvert 15 sekund og piper

    } // end if
} // end void

void hiddenFeature(){
    int8_t averageSpeed = speedometer();
    int8_t distanceChange = distance - lastDistance;



    // Function to turn on hiddenActivated

    // Function to turn of hiddenActivated

    // Function to turn on emergencyChargingMode
    


    if (hiddenActivated == true){ // FINN PÅ NOE SOM SKAL AKTIVERE FUNSKJONEN
      
        lastDistance = distance;

        consumptionMeasure += (averageSpeed / distanceChange); // EKSEMPEL PÅ FUNKSJON, OPPDATER NÅR VI TESTER MED DATA

        if (consumptionMeasure <= -10){
            if ((emergencyChargeMode == true) && (emergencyChargingUsed = false)){
                batteryLevel += 20;
                emergencyChargingUsed = true;
            } // end if

            else{
                batteryLevel += 2;
            } // end else
        } // end else
    } // end if
} // end void

void showBatteryStatus(){                               
    unsigned long currentMillis = millis();
    

    ///////// DISABLE WHILE CHARGING //////////

    batteryLevel = constrain(batteryLevel, 0, 100);

    if (batteryDisplayed == false){
        if (currentMillis - refreshPreviousMillis >= refreshInterval){
            //float speedReading = speedometer();
            display.clear();
            display.setLayout11x4();                        // Divide screen into 11 columns and 4 rows
            display.print(F("Speed:"));
            display.gotoXY(0,1);
            display.print(iAmSpeed);
            display.gotoXY(7,1);
            display.print(F("m/s"));
            display.gotoXY(0,2);
            display.print(F("Distance:"));
            display.gotoXY(0,3);
            display.print(distance);
            display.gotoXY(7,3);
            display.print(F("cm"));
            refreshPreviousMillis = currentMillis;
        } // end if
    } // end if


    if (currentMillis - previousMillis >= onInterval){
        display.clear();
        display.setLayout21x8();                        // Divide screen into 21 columns and 8 rows
        display.print(F("Battery level"));
        display.gotoXY(15,0);
        display.print(batteryLevel);
        display.gotoXY(0,2);
        display.print(F("Times Charged"));
        display.gotoXY(15,2);
        display.print(timesCharged);
        display.gotoXY(0,4);
        display.print(F("Battery Health"));
        display.gotoXY(15,4);
        display.print(batteryHealth);
        previousMillis = currentMillis;
        displayTime = currentMillis;
        batteryDisplayed = true;                        // To make the next if sentence only run once after this text have been ran
    } // end if

    if ((currentMillis - displayTime >= offInterval) && (batteryDisplayed == true)){
        batteryDisplayed = false;
    } // end if
} // end void