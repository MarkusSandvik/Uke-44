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
bool passengerOn = false;
bool passengerFound = false;
long searchTime = 0;
long missionStart = 0;
int missionDistance = 0;
int workCase = 2;

// Test variables
int bankAccount = 0;
int distance = 0;
int payment = 100;


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
}