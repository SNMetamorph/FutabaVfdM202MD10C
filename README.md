# FutabaVfdM202MD10C
Library for Arduino framework for convenient working with vacuum fluorescent displays (VFD) based on Futaba M202MD10C board. 

## Supported features
- Cursor positioning
- Cursor visibility toggle
- Text vertical scrolling toggle
- Brightness dimming (4 levels available)
- Display self-test mode triggering
- Code pages switching (12 available)
- User-definable symbols (9 available)
- Internal buffer for ticker text (45 symbols maximum)

## Usage example
There are several different example sketches available in `/examples`, this is one of them:
```c++
#include <FutabaVfdM202MD10C.h>
#include <SoftwareSerial.h>

FutabaVfdM202MD10C display;
SoftwareSerial softSerial(2, 3, true); // display DATA should be connected to pin #3
bool dimmingStatus = true;

void setup() {
    softSerial.begin(9600);
    display.initialize(softSerial);
    display.reset();
    display.print("Wake up, Neo...");
}

void loop() {
    display.toggleCursor(dimmingStatus);
    dimmingStatus = !dimmingStatus;
    delay(500);
}
```

## Credits
My thanks to `abomin` for discovering about display "extended" mode and user characters defining.
