#include <FutabaVfdM202MD10C.h>
#include <SoftwareSerial.h>

FutabaVfdM202MD10C display;
SoftwareSerial softSerial(2, 3, true); // display DATA should be connected to pin #3
bool dimmingStatus = true;

void setup() {
    softSerial.begin(9600);
    display.initialize(softSerial);
    display.clear();
    display.print("Wake up, Neo...");
}

void loop() {
    display.toggleCursor(dimmingStatus);
    dimmingStatus = !dimmingStatus;
    delay(500);
}
