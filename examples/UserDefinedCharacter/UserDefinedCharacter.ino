#include <FutabaVfdM202MD10C.h>
#include <SoftwareSerial.h>

FutabaVfdM202MD10C display;
SoftwareSerial softSerial(2, 3, true); // display DATA should be connected to pin #3

void setup() {
    softSerial.begin(9600);
    display.initialize(softSerial);
    display.clear();
    delay(1000);

    // define smile icon character
    // each character consists of 7 bytes, 5 most significant bits in byte 
    // is character row pixels state, left to right
    // 01110000 = 0x70
    // 10101000 = 0xA8
    // 11111000 = 0xF8
    // 10001000 = 0x88
    // 01110000 = 0x70
    constexpr uint8_t data[7] = { 0x70, 0xA8, 0xF8, 0x88, 0x70, 0x00, 0x00 };
    display.defineUserCharacter(FutabaVfdM202MD10C::Character::UserChar1, data);
}

void loop() {
    display.write(FutabaVfdM202MD10C::Character::UserChar1);
    delay(500);
}
