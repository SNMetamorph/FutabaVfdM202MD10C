/*
If vertical scroll disabled, when printing character if write-in position is on 
last character in second row, write-in position will be moved to position of 
first character in first row.

If vertical scroll enabled, when printing character if write-in position is on
last character in second row, all existing characters will be moved from second 
to first row, then second row will be cleaned, and write-in position will be 
moved to position of first character in second row.
*/

#include <FutabaVfdM202MD10C.h>
#include <SoftwareSerial.h>

FutabaVfdM202MD10C display;
SoftwareSerial softSerial(2, 3, true); // display DATA should be connected to pin #3
const char *testingText = "The quick brown fox jumps over the lazy dog.";

void printWithDelay(const char *text)
{
    const int length = strlen(text);
    for (int i = 0; i < length; i++) {
        display.print(text[i]);
        delay(100);
    }
}

void setup() {
    softSerial.begin(9600);
    display.initialize(softSerial);
    display.reset();
    display.toggleCursor(false);
    delay(1000);
}

void loop() {
    display.clear();
    display.print("Vertical scroll: off");
    display.toggleVerticalScroll(false);
    delay(2000);
    display.clear();
    printWithDelay(testingText);
    delay(5000);

    display.clear();
    display.print("Vertical scroll: on");
    display.toggleVerticalScroll(true);
    delay(2000);
    display.clear();
    printWithDelay(testingText);
    delay(5000);
}
