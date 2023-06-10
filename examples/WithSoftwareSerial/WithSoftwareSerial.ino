#include <FutabaVfdM202MD10C.h>
#include <SoftwareSerial.h>

FutabaVfdM202MD10C display;
SoftwareSerial softSerial(2, 3, true); // display DATA should be connected to pin #3

void setup() {
    softSerial.begin(9600);
    display.initialize(softSerial);
    display.reset();
    display.cursorSetPos(0, 0);
    display.print("This is Futaba");
    display.cursorSetPos(0, 1);
    display.print("M202MD10C display");
}

void loop() {
}
