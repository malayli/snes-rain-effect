#include <snes.h>
#include "level.h"

int main(void) {
    consoleInit();
    initLevel();

    while(1) {
        updateLevel();
        WaitForVBlank();
    }
    return 0;
}
