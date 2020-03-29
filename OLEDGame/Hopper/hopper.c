#include "hopper.h"
/*  Defines  */

enum MODE {
    LOGO_MODE = 0,
    TITLE_MODE,
    GAME_MODE
};

/*  Typedefs  */

typedef struct {
    void (*initFunc)(void);
    bool (*updateFunc)(void);
    void (*drawFunc)(void);
} MODULE_FUNCS;

/*  Global Variables  */


/*  Local Variables  */

static const MODULE_FUNCS moduleTable[] = {
    { initLogo,  updateLogo,  drawLogo },
    { initTitle, updateTitle, drawTitle },
    { initGame,  updateGame,  drawGame },
};

static enum MODE mode = LOGO_MODE;

void setup(void)
{

	OLED_FillScreen(0);
    SetFrameRate(60);
   moduleTable[LOGO_MODE].initFunc();

}

void loop(void)
{

    if (!(NextFrame())) return;
    bool isDone = moduleTable[mode].updateFunc();
    moduleTable[mode].drawFunc();

    OLED_Refresh_Gram();//¸üÐÂOLEDÏÔ´æ
    if (isDone) {
        mode = (mode == TITLE_MODE) ? GAME_MODE : TITLE_MODE;
        moduleTable[mode].initFunc();
    }

}
void Hopper(void)
{
	setup();
	while(1)
	{
	loop();
	}	
}

