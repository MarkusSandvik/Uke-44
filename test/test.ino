#include <Wire.h>
#include <Zumo32U4.h>

/////////// NOTES ////////////
/*
- Add switchcase for display modes/ buzzer
- Add switchcase in softwareBattery for special functions
- Add lineFollower
- Add switchcase in line follower for turning, job etc.
-
*/

// Variables for taxiDriver()
bool passengerFound = false;
long searchTime = 0;
long missionStart = 0;
int missionDistance = 0;
int workCase = 2;
int startDistance = 0;
int passengerEntered = 0;

// Test variables
int bankAccount = 0;
int distance = 0;


Zumo32U4OLED display;
Zumo32U4Encoders encoders;
Zumo32U4Buzzer buzzer;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonC buttonC;
Zumo32U4ButtonB buttonB;

void setup(){
    Serial.begin(9600);
    // Wait for button A to be pressed and released.
    display.clear();
    display.print(F("Press A"));
    display.gotoXY(0, 1);
    display.print(F("to start"));
    buttonA.waitForButton();
}

void loop(){
    taxiDriver();
}

void searchForPassenger(){

    int currentMillis = millis();

    if (passengerFound = false){
        searchTime = random(1000, 5000);
        passengerFound = true;
    } // end if
    
    else if (passengerFound == true){
        if (currentMillis - missionStart > searchTime){
            missionDistance = random(100,300);
            motors.setSpeeds(0,0);
            display.clear();
            display.setLayout21x8();
            display.print(F("The passenger want to travel"));
            display.gotoXY(0,1);
            display.print(F("travel for"));
            display.gotoXY(12,1);
            display.print(missionDistance);
            display.gotoXY(18,1);
            display.print(F("cm"));
            display.gotoXY(0,3);
            display.print(F("Do you take the job?"));
            display.gotoXY(0,4);
            display.print(F("A = YES"));
            display.gotoXY(15,4);
            display.print(F("B = NO"));
            display.gotoXY(0,5);
            display.print(F("C = Off duty"));
            while ((buttonA.isPressed() == 0) and (buttonB.isPressed() == 0) and buttonC.isPressed() == 0){
            } // end while
            if (buttonA.isPressed() == 1){
                passengerEntered = currentMillis;
                startDistance = distance;
                workCase = 2;
                passengerFound = true;
            } // end if

            else if (buttonB.isPressed() == 1){
                workCase = 1;
            } // end if

            else if (buttonC.isPressed() == 1){
                workCase = 0;
            } // end if     
        } // end if
    } // end if
} // end void

void drivePassenger(){
    int currentMillis = millis();
    if (distance - startDistance > missionDistance){
        motors.setSpeeds(0,0);
        int payment = (missionDistance / (currentMillis - missionStart)) * 1000;
        bankAccount +=  payment;
        display.clear();
        display.setLayout21x8();
        display.print(F("Passanger delivered"));
        display.gotoXY(0,2);
        display.print(F("Payment:"));
        display.gotoXY(13,2);
        display.print(payment);
        display.gotoXY(18,2);
        display.print(F("kr"));
        display.gotoXY(0,4);
        display.print(F("Continue Working?"));
        display.gotoXY(0,5);
        display.print(F("A = Search for client"));
        display.gotoXY(0,6);
        display.print(F("B = End work"));
        while ((buttonA.isPressed() == 0) and (buttonB.isPressed() == 0)){
        } // end while
        if (buttonA.isPressed() == 1){
            workCase = 1;
        } // end if
        else if (buttonB.isPressed() == 1){
            workCase = 0;
        } // end if
    } // end if
} // end void

void taxiDriver(){
    switch (workCase)
    {
    case 1:
        searchForPassenger();
        break;
    case 2:
        drivePassenger();
        break;
    default:
        break;
    } 
} // end void
