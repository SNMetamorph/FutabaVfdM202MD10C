/*
FutabaVfdM202MD10C - library for Arduino framework for convenient working with Futaba M202MD10C display.
-- Can be used in pair with SoftwareSerial or HardwareSerial
-- Implements as much as possible functions that display supports, such as dimming,
user-defined symbols, code pages, cursor visibility toggle, self-testing, etc.

Copyright (c) 2022 SNMetamorph

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef _FUTABA_VFD_M202MD10C_H
#define _FUTABA_VFD_M202MD10C_H
#include <Arduino.h>

class FutabaVfdM202MD10C : public Print
{
public:    
    enum Character {
        UserChar1 = 0x15,
        UserChar2 = 0x16,
        UserChar3 = 0x17,
        UserChar4 = 0x18,
        UserChar5 = 0x19,
        UserChar6 = 0x1A,
        UserChar7 = 0x1C,
        UserChar8 = 0x1D,
        UserChar9 = 0x1E,
    };

    enum class CodePage {
        Default = 0x0,
        CP897 = 0x1, // Japanese
        CP850 = 0x2, // French, German, Portuguese, Spanish
        CP852 = 0x3, // Czech, Slovak, Polish, Hungarian, Slovene, Croatian, Romanian, Albanian
        CP855 = 0x4, // Belarusian, Bosnian, Bulgarian, Macedonian, Serbian, Ukrainian, Kazakh, Kyrgyz, Mold
        CP857 = 0x5, // Turkish
        CP862 = 0x6, // Hebrew
        CP863 = 0x7, // French Canadian
        CP864 = 0x8, // Arabic
        CP437 = 0x9, // Western European languages, Greek
        CP866 = 0xA, // Russian
        CP869 = 0xB, // Greek
    };

    enum class Dimming
    {
        Minimum = 0x20,
        Medium = 0x40,
        BelowMedium = 0x60,
        Maximum = 0xFF
    };

    FutabaVfdM202MD10C();
    size_t write(uint8_t character) override;

    void initialize(Stream& stream);
    void clear();
    void reset();
    void backspace();
    void cursorHomePos();
    void cursorSetPos(int x, int y);
    void setDimming(Dimming level);
    void runSelfTest();
    void toggleCursor(bool status);
    void setCodePage(CodePage page);
    void defineUserCharacter(Character charNumber, const uint8_t data[7]);
    
private:
    void toggleExtendedMode(bool status);

    Stream *m_pStream;
};

#endif // _FUTABA_VFD_M202MD10C_H
