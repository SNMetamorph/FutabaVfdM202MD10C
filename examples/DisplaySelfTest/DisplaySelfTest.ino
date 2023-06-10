#include <FutabaVfdM202MD10C.h>
#include <SoftwareSerial.h>

FutabaVfdM202MD10C display;
SoftwareSerial softSerial(2, 3, true); // display DATA should be connected to pin #3

void setup() {
    softSerial.begin(9600);
    display.initialize(softSerial);
    display.reset();
}

void loop() {
    display.clear();
    display.print("Self-test after... ");

    for (int i = 3; i > 0; i--) {
        display.print(i, DEC);
        delay(1000);
        display.backspace();
    }
    
    display.runSelfTest();
    delay(8000);
}
