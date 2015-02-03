#define INCL_WININPUT
#define INCL_WINSYS

#include <os2.h>

#include <stdio.h>

int main(int, char **) {

        HAB hab = WinInitialize(0);
        if(!hab) {
                return -1;
        }

        BYTE keyState[257];
        WinSetKeyboardStateTable(HWND_DESKTOP,keyState+1,FALSE);

        keyState[VK_CAPSLOCK] |= 0x01;

        WinSetKeyboardStateTable(HWND_DESKTOP,keyState+1,TRUE);


        WinTerminate(hab);

        return 0;
}
