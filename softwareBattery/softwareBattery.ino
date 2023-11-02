#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4OLED display;
Zumo32U4ButtonA buttonA;

// Variables for softwareBattery
int8_t batteryLevel = 100;
long lastDistance = 0;
int8_t consumptionMeasure = 0;
int8_t timesCharged = 0;

// Variables for hiddenFeature()
bool hiddenActivated = false;
bool emergencyChargingUsed = false;

// Variables for showBatteryStatus()
unsigned long previousMillis = 0;
const long oninterval = 10000;
const long offinterval = 2000;
long displayTime = 0;
bool batteryDisplayed = false;



void setup(){

}

void loop(){

}

long speedometer(){
    return (32,10);
}


void softwareBattery(){
    long distance = distancemeter();
    int8_t averageSpeed = speedometer();
    int8_t distanceChange = distance - lastDistance;
    lastDistance = distance;

    consumptionMeasure += (averageSpeed / distanceChange) // EKSEMPEL PÅ FUNKSJON, OPPDATER NÅR VI TESTER MED DATA

    if (consumptionMeasure >= 10){
        batteryLevel -= 1;
    } // end if
} // end void

void carNeedCharging(){
    if (batteryLevel < 10){ // Gir forvarsel med Lyd, lys og display

    } // end if

    if (batteryLevel < 5){ // Stopper hvert 15 sekund og piper

    } // end if
} // end void

void hiddenFeature(){
    long distance = distancemeter();
    int8_t averageSpeed = speedometer();
    int8_t distanceChange = distance - lastDistance;



    // Function to turn on hiddenActivated

    // Function to turn of hiddenActivated

    // Function to turn on emergencyChargingMode
    


    if (hiddenActivated == true){ // FINN PÅ NOE SOM SKAL AKTIVERE FUNSKJONEN
      
        lastDistance = distance;

        consumptionMeasure += (averageSpeed / distanceChange) // EKSEMPEL PÅ FUNKSJON, OPPDATER NÅR VI TESTER MED DATA

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


    if (currentMillis - previousMillis >= oninterval){
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

    if ((currentMillis - displayTime >= offinterval) && (batteryDisplayed == true)){
        display.clear();
        display.setLayout11x4();                        // Divide screen into 11 columns and 4 rows
        display.print(F("Speed:"));
        display.gotoXY(0,1);
        display.print(speedReading);
        display.gotoXY(7,1);
        display.print(F("m/s"));
        display.gotoXY(0,2);
        display.print(F("Distance:"));
        display.gotoXY(0,3);
        display.print(distance);
        display.gotoXY(7,3);
        display.print(F("m"));
        batteryDisplayed = false;
    } // end if
} // end void