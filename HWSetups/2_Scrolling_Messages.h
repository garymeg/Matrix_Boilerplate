#include <Adafruit_GFX.h>
#include <vector>
#include <string>

//uint8_t stat_NeedToChange;
char str[500];
int16_t textX = 64, // matrix.width(),
    textMin = 0,
        hue = 0,
        textY = 0,
        Scrolling = 0;

std::vector<String> myMessages;
const std::string WHITESPACE = " \n\r\t\f\v";

std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

void getNextMessage()
{
    String message = myMessages.front();
    //debugPrinting("Next Message : " + message);
    myMessages.erase(myMessages.begin());
    strcpy(str, message.c_str());

    int16_t x1, y1;
    uint16_t w, h;

    matrix.setFont(&FreeSansBold18pt7b);                   // Use nice bitmap font
    matrix.getTextBounds(message, 0, 0, &x1, &y1, &w, &h); // How big is it?
    textMin = -w;                                          // All text is off left edge when it reaches this point
    textY = matrix.height() / 2 - (y1 + h / 2);            // Center text vertically

    // textMin = (int16_t)message.length() * -24;
    textX = 64; // matrix.width();
}

void performTextScrolling()
{
    Serial.println(str);
    matrix.setTextWrap(false); // Allow text to run off right edge
    matrix.fillScreen(myBLACK);
    // #if defined(ARDUINO_ARCH_RP2040)
    matrix.setTextColor(matrix.colorHSV(hue, 100, 100));
    // #elif defined(ARDUINO_ARCH_ESP32)
    //   matrix.setTextColor(matrix.ColorHSV(hue, 100, 100, true));
    // #endif
    // matrix.setTextColor(0xFFFF);
    matrix.setCursor(textX, textY);
    matrix.print(str);
    matrix.show();

    // textX = textX - 2;
    //  Have we reach the end of the Text?
    if ((--textX) < textMin+1)
    {
        // Anymore Messages in the Queue
        if (!myMessages.empty())
        {
            getNextMessage();
        }
        else
        {
            matrix.setTextWrap(true); // Allow text to wrap round
            Scrolling = 0;
        }
    }
}
// Input a value 0 to 24 to get a color value.
// The colours are a transition r - g - b - back to r.
uint16_t Wheel(byte WheelPos)
{
    if (WheelPos < 8)
    {
        return matrix.Color444(7 - WheelPos, WheelPos, 0);
    }
    else if (WheelPos < 16)
    {
        WheelPos -= 8;
        return matrix.Color444(0, 7 - WheelPos, WheelPos);
    }
    else
    {
        WheelPos -= 16;
        return matrix.Color444(WheelPos, 0, 7 - WheelPos);
    }
}
