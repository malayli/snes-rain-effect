#include <snes.h>
#include "level.h"
#include "utils.h"

// ROM

extern char rainPic, rainPic_end;
extern char rainPalette, rainPalette_end;
extern char rainMap, rainMap_end;

extern char terrainPic, terrainPic_end;
extern char terrainPalette, terrainPalette_end;
extern char terrainMap, terrainMap_end;

// RAM

u8 framesCounter;
u8 lightningFramesCounter;
u8 lightningState;

/*!\brief Initialize the Level screen.
*/
void initLevel() {
    framesCounter = 0;
    lightningFramesCounter = 0;
    lightningState = 0;

    bgSetMapPtr(BG0, 4096, SC_64x64);
    bgSetMapPtr(BG1, 0, SC_64x64);

    bgInitTileSet(BG0,
        &rainPic,
        &rainPalette,
        PAL0,
        (&rainPic_end - &rainPic),
        16*2,
        BG_16COLORS,
        0x2000);

    bgInitTileSet(BG1,
        &terrainPic,
        &terrainPalette,
        PAL1,
        (&terrainPic_end - &terrainPic),
        16*2*3,
        BG_16COLORS,
        0x3000);

    WaitForVBlank();

    dmaCopyVram(&rainMap, 4096, 64*64*2);
    dmaCopyVram(&terrainMap, 0, 64*64*2);

    setMode(BG_MODE1, BG3_MODE1_PRORITY_HIGH);
    bgSetDisable(BG0);
    bgSetEnable(BG1);
    bgSetEnable(BG2);
    bgSetDisable(BG3);

    // Workaround for SNES
    bgSetScroll(BG0, 0, -1);
    bgSetScroll(BG1, 0, -1);
    bgSetScroll(BG2, 0, -1);
    
    bgSetScroll(BG0, 50, 667);
    bgSetScroll(BG1, 50, 667);

    REG_TS = 0b00000001;

    REG_CGWSEL = 0b10000010;

    REG_CGADSUB = 0b01110010;

    setFadeEffect(FADE_IN);
	WaitForVBlank();
}

/*!\brief Update the rain.
*/
void updateRain() {
    if (framesCounter == 0) {
        bgSetScroll(BG0, 50, 667);

    } else if (framesCounter == 4) {
        bgSetScroll(BG0, 50, 923);

    } else if (framesCounter == 8) {
        bgSetScroll(BG0, 306, 923);

    } else if (framesCounter == 12) {
        bgSetScroll(BG0, 306, 155);

    } else if (framesCounter == 16) {
        bgSetScroll(BG0, 562, 155);

    } else if (framesCounter == 20) {
        bgSetScroll(BG0, 562, 411);

    } else if (framesCounter == 24) {
        bgSetScroll(BG0, 818, 411);

    } else if (framesCounter == 28) {
        bgSetScroll(BG0, 818, 667);
    }

    framesCounter++;

    if (framesCounter == 32) {
        framesCounter = 0;
    }
}

/*!\brief Update the lightning state.
    \param state the next lightning state to set when stop condition is true.
    \param start the start frame index for enabling the lightning.
    \param stop the stop frame index for disabling the lightning.
*/
void updateLightningState(u8 state, u8 start, u8 stop) {
    if (lightningFramesCounter == start) {
        REG_CGADSUB = 0b00110010;
        lightningFramesCounter++;

    } else if (lightningFramesCounter == stop) {
        REG_CGADSUB = 0b01110010;
        lightningFramesCounter = 0;
        lightningState = state;

    } else {
        lightningFramesCounter++;
    }
}

/*!\brief Update the lightning.
*/
void updateLightning() {
    switch(lightningState) {
        case 0:
            updateLightningState(1, 32, 34);
            break;

        case 1:
            updateLightningState(2, 32, 40);
            break;

        case 2:
            updateLightningState(3, 44, 46);
            break;

        case 3:
            if (lightningFramesCounter == 170) {
                lightningFramesCounter = 0;
                lightningState = 0;

            } else {
                lightningFramesCounter++;
            }
            break;
    }
}

/*!\brief Update the Level screen.
*/
void updateLevel() {
    updateRain();
    updateLightning();
}

/*!\brief Clear the Level screen.
*/
void clearLevel() {
    // Fade out so light to black
	setFadeEffect(FADE_OUT);
	WaitForVBlank();

    oamClear(0, 0);
    dmaClearVram();

    bgSetDisable(BG0);
    bgSetDisable(BG1);
    bgSetDisable(BG2);
    bgSetDisable(BG3);
}
