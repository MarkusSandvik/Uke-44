#include <Wire.h>
#include <Zumo32U4.h>

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


    if (currentMillis - previousMillis >= interval){
        display.clear();
        display.print(batteryLevel);
        display.gotoXY(0,1);
        display.print(timesCharged);
        display.gotoXY(0,2);
        display.print(batteryHealth);
    } // end if

}