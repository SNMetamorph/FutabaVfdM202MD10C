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

#include "FutabaVfdM202MD10C.h"

enum ProtocolCommands
{
    ExtendedMode = 0x0,
    SelectCodePage = 0x2,
    DefineCharacter = 0x3,
    DimmingMode = 0x4,
    PrintTickerText = 0x5,
    Backspace = 0x8,
    SelfTest = 0xF,
    DisplayPosition = 0x10,
    DisableVerticalScroll = 0x11,
    EnableVerticalScroll = 0x12,
    CursorOn = 0x13,
    CursorOff = 0x14,
    Reset = 0x1F
};

FutabaVfdM202MD10C::FutabaVfdM202MD10C()
{
    m_pStream = nullptr;
    resetLocalDisplayState();
}

size_t FutabaVfdM202MD10C::write(uint8_t character)
{
    m_pStream->write(character);
    return 1;
}

void FutabaVfdM202MD10C::initialize(Stream& stream)
{
    m_pStream = &stream;
    toggleExtendedMode(true);
}

void FutabaVfdM202MD10C::clear()
{
    if (!m_bVerticalScroll) {
        m_pStream->write(ProtocolCommands::EnableVerticalScroll);
    }
    m_pStream->write('\n');
    m_pStream->write('\n');
    m_pStream->write('\n');
    m_pStream->write(ProtocolCommands::DisplayPosition);
    m_pStream->write(static_cast<uint8_t>(0x0));
    if (!m_bVerticalScroll) {
        m_pStream->write(ProtocolCommands::DisableVerticalScroll);
    }
}

void FutabaVfdM202MD10C::reset()
{
    m_pStream->write(ProtocolCommands::Reset);
    resetLocalDisplayState();
    toggleExtendedMode(true);
}

void FutabaVfdM202MD10C::backspace()
{
    m_pStream->write(ProtocolCommands::Backspace);
}

void FutabaVfdM202MD10C::cursorHomePos()
{
    m_pStream->write(ProtocolCommands::DisplayPosition);
    m_pStream->write(static_cast<uint8_t>(0x0));
}

void FutabaVfdM202MD10C::cursorSetPos(int x, int y)
{
    m_pStream->write(ProtocolCommands::DisplayPosition);
    m_pStream->write(x + y * 20);
}

void FutabaVfdM202MD10C::setDimming(Dimming level)
{
    m_pStream->write(ProtocolCommands::DimmingMode);
    m_pStream->write(static_cast<uint8_t>(level));
}

void FutabaVfdM202MD10C::runSelfTest(bool waitUntilEnd)
{
    m_pStream->write(ProtocolCommands::SelfTest);
    toggleExtendedMode(true);
    if (waitUntilEnd) {
        // display is unavailable during self-test, so maybe we want to wait
        // until display testing will be finished
        delay(8000);
    }
}

void FutabaVfdM202MD10C::toggleCursor(bool status)
{
    m_pStream->write(status ? ProtocolCommands::CursorOn : ProtocolCommands::CursorOff);
}

void FutabaVfdM202MD10C::setCodePage(CodePage page)
{
    m_pStream->write(ProtocolCommands::SelectCodePage);
    m_pStream->write(static_cast<uint8_t>(page));
}

void FutabaVfdM202MD10C::toggleVerticalScroll(bool status)
{
    m_bVerticalScroll = status;
    m_pStream->write(status ? ProtocolCommands::EnableVerticalScroll : ProtocolCommands::DisableVerticalScroll);
}

void FutabaVfdM202MD10C::beginTickerText()
{
    m_pStream->write(ProtocolCommands::PrintTickerText);
}

void FutabaVfdM202MD10C::endTickerText()
{
    m_pStream->write('\r');
}

void FutabaVfdM202MD10C::defineUserCharacter(Character charNumber, const uint8_t data[7])
{
    m_pStream->write(ProtocolCommands::DefineCharacter);
    m_pStream->write(static_cast<uint8_t>(charNumber));
    for (int i = 0; i < 7; i++) {
        m_pStream->write(data[i]);
    }
    m_pStream->write(static_cast<uint8_t>(0x0));
}

void FutabaVfdM202MD10C::resetLocalDisplayState()
{
    m_bVerticalScroll = true;
}

void FutabaVfdM202MD10C::toggleExtendedMode(bool status)
{
    m_pStream->write(ProtocolCommands::ExtendedMode);
    m_pStream->write(status ? 0x1 : 0x0);
}
