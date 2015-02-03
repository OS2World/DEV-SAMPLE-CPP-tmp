#define INCL_KBD
#include <os2.h>
#include <stdlib.h>
#include <stdio.h>

void apiError(const char *func, APIRET rc) {
        printf("%s() returned %ld\n",func,rc);
        exit(1);
}

HKBD hkbd = 0;

int main(void) {
        KBDINFO kbdinfo;
        APIRET rc;

        kbdinfo.cb = sizeof(kbdinfo);
        rc = KbdGetStatus(&kbdinfo,hkbd);
        if(rc) apiError("KbdGetStatus",rc);
        for(;;) {
                printf("shiftstate:\n");
                const USHORT shiftstate = kbdinfo.fsState;
                printf("  Insert     : %s\n", shiftstate&(1<<7) ? "On":"Off");
                printf("  CapsLock   : %s\n", shiftstate&(1<<6) ? "On":"Off");
                printf("  NumLockk   : %s\n", shiftstate&(1<<5) ? "On":"Off");
                printf("  ScrollLock : %s\n", shiftstate&(1<<4) ? "On":"Off");
 
                KBDKEYINFO keyinfo;
                rc = KbdCharIn(&keyinfo,0,hkbd);
                if(rc) apiError("KbdCharIn",rc);
                if(keyinfo.chChar=='q' || keyinfo.chChar=='Q') break;
        }

        return 0;
}

