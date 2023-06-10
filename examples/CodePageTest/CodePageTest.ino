#include <FutabaVfdM202MD10C.h>
#include <SoftwareSerial.h>

FutabaVfdM202MD10C display;
SoftwareSerial softSerial(2, 3, true); // display DATA should be connected to pin #3

void setup() {
    softSerial.begin(9600);
    display.initialize(softSerial);
    display.reset();
    display.cursorSetPos(0, 0);
    display.toggleCursor(false);
    
    // sentence "ВОТ ЭТО ПРИКОЛ" written in binary form, in encoding CP866
    // if everything works - you'll see it on display
    const char *cyrillicText = "\x82\x8E\x92\x20\x9D\x92\x8E\x20\x8F\x90\x88\x8A\x8E\x8B";
    display.setCodePage(FutabaVfdM202MD10C::CodePage::CP866);
    display.print(cyrillicText);
}

void loop() {
}
