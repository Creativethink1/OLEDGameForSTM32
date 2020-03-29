#ifndef HOPPER_H
#define HOPPER_H

#include "main.h"
#include "key_bsp.h"
#include "oled_bsp.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
/*  Defines  */

//#define DEBUG
#define APP_TITLE       "HOPPER"
#define APP_INFO        "OBN-Y02 VER 0.21"
#define APP_RELEASED    "NOVEMBER 2017"

#define LEFT_BUTTON _BV(0)
#define RIGHT_BUTTON _BV(1)
#define UP_BUTTON _BV(2)
#define DOWN_BUTTON _BV(3)
#define A_BUTTON _BV(4)
#define B_BUTTON _BV(5)

#define PI    3.141592653589793
#define false 0
#define true  1
#define F(s)  (s) 
#define SysTick_LoadValue (72000000 / 1000U) //根据当前时钟频率自动计算Systick初始值
#define CYCLES_PER_MICROSECOND	(72000000 / 1000000U)
#define memcpy_P(dest, src, num) memcpy((dest), (src), (num))
#define strcpy_P(dest, src) strcpy((dest), (src))
#define strcat_P(dest, src) strcat((dest), (src))
#define strcmp_P(a, b) strcmp((a), (b))
#define strstr_P(a, b) strstr((a), (b))
#define strlen_P(a) strlen((a))

/*  Typedefs  */

typedef unsigned char   uchar;
typedef unsigned int    uint;
typedef unsigned char   bool;
typedef uint8_t byte;

/*  Global Functions  */
/*  link  */
void SetFrameRate(uint8_t rate);
bool NextFrame(void);

bool ButtonDown(uint8_t buttons);
bool ButtonPressed(uint8_t buttons);
bool ButtonUp(uint8_t buttons);

/*  logo  */
void initLogo(void);
bool updateLogo(void);
void drawLogo(void);

/*  title  */
void initTitle(void);
bool updateTitle(void);
void drawTitle(void);
uint8_t setLastScore(int score, uint32_t frames);
/*  game  */
void initGame(void);
bool updateGame(void);
void drawGame(void);

/*  link  */
void randomSeed(unsigned long seed);
long random(long howbig);
long random2(long howsmall, long howbig);
uint8_t setLastScore(int score, uint32_t frames);
uint32_t micros(void);

/*  Global Variables  */
void Hopper(void);
  
 
	
/*  For Debugging  */

#endif
