#include "hopper.h"

/*  Defines  */

#define SIGNAL_PTN      0xEEE3AA3AU  // "OBN" in Morse code

/*  Local Variables  */

	static const uint8_t imgOBN[][96] = { // 24x32 x3
    {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0xF0, 0x58, 0xAC, 0x56, 0xAB, 0x55,
        0xAB, 0x55, 0x00, 0xFF, 0x01, 0x01, 0x01, 0x02, 0x02, 0x04, 0x08, 0x10, 0x60, 0x80, 0x00, 0x00,
        0x3F, 0xFF, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xA8, 0x5F, 0xAC, 0x5C, 0xAC, 0x5C,
        0xAC, 0x5C, 0xAC, 0x5C, 0x0C, 0xCF, 0x3C, 0x00, 0x00, 0x00, 0x01, 0x03, 0x06, 0x0D, 0x1A, 0x15,
        0x2A, 0x25, 0x2A, 0x25, 0x2A, 0x25, 0x22, 0x15, 0x12, 0x09, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, // O
    },{
        0xFF, 0xFF, 0x57, 0xAB, 0x57, 0xAB, 0x57, 0xAB, 0x57, 0xAB, 0x03, 0xFF, 0x80, 0x80, 0x80, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA,
        0x55, 0xAA, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x04, 0x08, 0x30, 0xC0, 0x00, 0x00,
        0x1F, 0x7F, 0xD5, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x54, 0xAF, 0x56, 0xAE, 0x56, 0xAE,
        0x56, 0xAE, 0x56, 0x2E, 0x86, 0x67, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x06, 0x0D, 0x0A,
        0x15, 0x12, 0x15, 0x12, 0x15, 0x12, 0x11, 0x0A, 0x09, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, // B
    }, {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x80, 0x80, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xF0, 0x78, 0xAC, 0x56, 0xAB, 0x55, 0xAA,
        0x55, 0xAA, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x04, 0x08, 0x30, 0xC0, 0x00, 0x00,
        0xFF, 0xFF, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x00, 0xFF, 0xFE, 0xAE, 0x56, 0xAE,
        0x56, 0xAE, 0x56, 0xAE, 0x56, 0x07, 0xFE, 0x00, 0x1F, 0x17, 0x15, 0x12, 0x15, 0x12, 0x15, 0x12,
        0x15, 0x12, 0x10, 0x1F, 0x17, 0x12, 0x15, 0x12, 0x15, 0x12, 0x15, 0x12, 0x15, 0x10, 0x1F, 0x00, // N
    }
};

	static const uint8_t imgSoft[] = { // 32x8
    0xC0, 0xC6, 0xCF, 0xDF, 0xFF, 0xFB, 0x73, 0x03, 0x7C, 0xFE, 0xFF, 0xC7, 0xE3, 0xFF, 0x7F, 0x3E,
    0x00, 0xFF, 0xFF, 0xFF, 0x1B, 0x1B, 0x1B, 0x03, 0x00, 0x03, 0x03, 0xFF, 0xFF, 0xFF, 0x03, 0x03,
};

static uint8_t  counter;
static bool     signalOn;

/*---------------------------------------------------------------------------*/
/*                              Main Functions                               */
/*---------------------------------------------------------------------------*/

void initLogo(void)
{
    counter = 120; // 2 secs
}

bool updateLogo(void)
{
    counter--;
    signalOn = (SIGNAL_PTN >> (counter - 15) / 3) & 1;
    
    bool ret = (counter == 0);
//    if (ret) {
//        //dprintln("Start " APP_TITLE " : " APP_INFO);
//    }
    return ret;
}

void drawLogo(void)
{
    OLED_ClearDisplay();
    int shake = (120 - counter) / 40;
    for (int i = 0; i < 3; i++) {
        int y = 12 + (i == shake) * signalOn;
        OLED_DrawBitmap(28 + i * 24, y, imgOBN[i], 24, 32, WHITE);
    }
		OLED_DrawBitmap(68, 44, imgSoft, 32, 8, WHITE);
   // arduboy.printEx(16, 58, F(APP_INFO));
}
