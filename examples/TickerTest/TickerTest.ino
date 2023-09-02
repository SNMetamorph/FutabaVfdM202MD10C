#include <FutabaVfdM202MD10C.h>
#include <SoftwareSerial.h>

FutabaVfdM202MD10C display;
SoftwareSerial softSerial(2, 3, true); // display DATA should be connected to pin #3
int i = 0;

void setup() {
    softSerial.begin(9600);
    display.initialize(softSerial);
    display.reset();
	
    // in case ticker text length will exceed 45 symbols, all next symbols just will be ignored
	display.beginTickerText();
    display.print("This text will scrolling in first row");
    display.endTickerText();
}

void loop() {
    // note that you still can print your data to second row
    display.cursorSetPos(0, 1);
    display.print(i++);
    delay(100);
}
