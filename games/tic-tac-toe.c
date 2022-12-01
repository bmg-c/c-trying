#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`
#include <stdlib.h>

#define BUFSIZE 32

typedef enum arrowKey_e
{
    ARROWKEY_UNKNOWN = 0,
    ARROWKEY_UP,
    ARROWKEY_DOWN,
    ARROWKEY_LEFT,
    ARROWKEY_RIGHT,
    ENTER,
} arrowKey_t;


// Read a keyboard key press and return the character pressed, or a negative
// number in the event of an error.
// NB: for help reading output from system calls, see here:
//  1. https://stackoverflow.com/a/28971647/4561887
//  2. https://stackoverflow.com/a/18297075/4561887
arrowKey_t readArrowKeyPress()
{
    arrowKey_t arrowKeyPressed = ARROWKEY_UNKNOWN;

    // This bash cmd is from my answer here:
    // https://stackoverflow.com/a/70979348/4561887
    // `-n3` here means to read 3 chars at once, since an arrow key press
    // comes in as 3 chars.
    // The `-t .01` forces a timeout of that many seconds, which means the loop
    // interval will be this fast.
    const char* cmd = "bash -c 'read -s -t .1 -n3 c && printf \"%s\" \"$c\"'";
    FILE *fp = popen(cmd, "r");
    if (fp == NULL)
    {
        printf("\nError opening pipe!\n");
        return arrowKeyPressed;
    }

    char buf[BUFSIZE] = {0};
    char* retval1 = fgets(buf, BUFSIZE, fp);
    if (retval1 == NULL)
    {
        // printf("\nFailed to read cmd response.\n");
        // Timeout occured; just exit.
        return arrowKeyPressed;
    }

    // See meaning of this return value here:
    // https://stackoverflow.com/questions/43116/how-can-i-run-an-external-program-from-c-and-parse-its-output/28971647#comment60311936_28971647
    int retval2 = pclose(fp);
    if (retval2 == -1)
    {
        printf("\nError obtaining the cmd's exit status code.\n");
        return arrowKeyPressed;
    }
    else if (retval2 != 0)
    {
        printf("\nCommand exited with exit status code %i.\n", retval2);
        return arrowKeyPressed;
    }

    // Map the readings to arrow keys
    if ((buf[0] == 27) && (buf[1] == 91) && (buf[2] == 65))
    {
        arrowKeyPressed = ARROWKEY_UP;
    }
    else if ((buf[0] == 27) && (buf[1] == 91) && (buf[2] == 66))
    {
        arrowKeyPressed = ARROWKEY_DOWN;
    }
    else if ((buf[0] == 27) && (buf[1] == 91) && (buf[2] == 67))
    {
        arrowKeyPressed = ARROWKEY_RIGHT;
    }
    else if ((buf[0] == 27) && (buf[1] == 91) && (buf[2] == 68))
    {
        arrowKeyPressed = ARROWKEY_LEFT;
    }
    else if ((buf[0] == 97) && (buf[1] == 97) && (buf[2] == 97))
    {
        arrowKeyPressed = ENTER;
    }

    return arrowKeyPressed;
}


int main() {
    char game[3][3] = {'*', '*', '*', '*', '*', '*', '*', '*', '*'};
    int focus[2] = {2, 2};
    char i = 1;
    char was;



    while (true) {
        system("clear");
        was = game[focus[0]][focus[1]];
        game[focus[0]][focus[1]] = '.';
        printf("%c ", game[0][0]);
        printf("%c ", game[0][1]);
        printf("%c\n", game[0][2]);
        printf("%c ", game[1][0]);
        printf("%c ", game[1][1]);
        printf("%c\n", game[1][2]);
        printf("%c ", game[2][0]);
        printf("%c ", game[2][1]);
        printf("%c\n\n", game[2][2]);
        game[focus[0]][focus[1]] = was;

        arrowKey_t arrowKeyPressed = readArrowKeyPress();
        if (arrowKeyPressed == ARROWKEY_UNKNOWN) continue;
        switch (arrowKeyPressed) {
            case ENTER:
                if (was == '*') {
                    if (i == 1) {
                        game[focus[0]][focus[1]] = 'X';
                        i = 0;
                    } else {
                        game[focus[0]][focus[1]] = 'O';
                        i = 1;
                    }
                }

                was = game[0][0];
                if (was != '*') {
                    if (was == game[0][1] && was == game[0][2]) {
                        printf("\"%c\" has won!\n", was);
                        return 0;
                    }
                    if (was == game[1][0] && was == game[2][0]) {
                        printf("\"%c\" has won!\n", was);
                        return 0;
                    }
                }

                was = game[1][1];
                if (was != '*') {
                    if (was == game[0][0] && was == game[2][2]) {
                        printf("\"%c\" has won!\n", was);
                        return 0;
                    }
                    if (was == game[0][2] && was == game[2][0]) {
                        printf("\"%c\" has won!\n", was);
                        return 0;
                    }
                    if (was == game[1][0] && was == game[1][2]) {
                        printf("\"%c\" has won!\n", was);
                        return 0;
                    }
                    if (was == game[0][1] && was == game[2][1]) {
                        printf("\"%c\" has won!\n", was);
                        return 0;
                    }
                }

                was = game[2][2];
                if (was != '*') {
                    if (was == game[0][2] && was == game[1][2]) {
                        printf("\"%c\" has won!\n", was);
                        return 0;
                    }
                    if (was == game[2][0] && was == game[2][1]) {
                        printf("\"%c\" has won!\n", was);
                        return 0;
                    }
                }

                break;
            case ARROWKEY_UP:
                focus[0]--;
                if (focus[0] == -1) focus[0]++;
                break;
            case ARROWKEY_DOWN:
                focus[0]++;
                if (focus[0] == 3) focus[0]--;
                break;
            case ARROWKEY_LEFT:
                focus[1]--;
                if (focus[1] == -1) focus[1]++;
                break;
            case ARROWKEY_RIGHT:
                focus[1]++;
                if (focus[1] == 3) focus[1]--;
                break;
            default:
                break;
        }


        // printf("Key pressed = %s\n", arrowKeyGetName(arrowKeyPressed));
    }

    return 0;
}
