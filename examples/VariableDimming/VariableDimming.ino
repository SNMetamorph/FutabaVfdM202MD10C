#include <FutabaVfdM202MD10C.h>
#include <SoftwareSerial.h>

FutabaVfdM202MD10C display;
SoftwareSerial softSerial(2, 3, true); // display DATA should be connected to pin #3

void setup() {
    softSerial.begin(9600);
    display.initialize(softSerial);
    display.reset();
    display.cursorSetPos(0, 0);
    display.print("This display can");
    display.cursorSetPos(0, 1);
    display.print("change brightness");
}

void loop() {
    constexpr FutabaVfdM202MD10C::Dimming levels[4] = { 
        FutabaVfdM202MD10C::Dimming::Minimum, 
        FutabaVfdM202MD10C::Dimming::Medium, 
        FutabaVfdM202MD10C::Dimming::AboveMedium,
        FutabaVfdM202MD10C::Dimming::Maximum 
    };
    
    for (int i = 0; i < 4; i++) {
        display.setDimming(levels[i]);
        delay(1000);
    }
}
