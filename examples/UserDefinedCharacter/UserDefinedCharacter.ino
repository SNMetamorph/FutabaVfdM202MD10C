#include <FutabaVfdM202MD10C.h>
#include <SoftwareSerial.h>

FutabaVfdM202MD10C display;
SoftwareSerial softSerial(2, 3, true); // display DATA should be connected to pin #3

constexpr auto kTwoCrossChar = FutabaVfdM202MD10C::Character::UserChar1;

void setup() {
    softSerial.begin(9600);
    display.initialize(softSerial);
    display.reset();
    display.toggleCursor(false);
    delay(1000);

    // define smile icon character
    // each character consists of 7 bytes
    // 5 most significant bits in byte is character row pixels state, but in reverse order
    // ■□■□□ - 00101000 = 0x28
    // □■□□□ - 00010000 = 0x10
    // ■□■□□ - 00101000 = 0x28
    // □□□□□ - 00000000 = 0x00
    // □□■□■ - 10100000 = 0xA0
    // □□□■□ - 01000000 = 0x40
    // □□■□■ - 10100000 = 0xA0
    constexpr uint8_t data[7] = { 0x28, 0x10, 0x28, 0x00, 0xA0, 0x40, 0xA0 };
    display.defineUserCharacter(kTwoCrossChar, data);
    display.printf("Custom character: %c", kTwoCrossChar);
}

void loop() {
}
