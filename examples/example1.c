#include <stdio.h>
#include <math.h>
#include "asciilib.h"

char car[6 * 5] = {
    ' ', ' ', '_', '_', ' ', ' ',
    ' ', '/', ' ', ' ', '\\', ' ',
    '-', '-', '-', '-', '-', '-',
    '-', '-', '-', '-', '-', '-',
    ' ', 'O', ' ', ' ', 'O', ' '
};

int main()
{
    /* Initialize ascii library */
    asciifb framebuffer;
    framebuffer.height = 5;
    framebuffer.width = 20;

    asciiinit(&framebuffer);

    /* copy car to framebuffer */
    asciicopyatfb(&framebuffer, car, 10, 0, 6, 5);
    /* render it */
    asciirenderfb(&framebuffer);
    /* move car */
    asciiclearfb(&framebuffer);
    asciicopyatfb(&framebuffer, car, 0, 0, 6, 5);
    /* render it */
    asciirenderfb(&framebuffer);
}