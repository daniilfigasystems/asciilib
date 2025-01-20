#include <stdio.h>
#include <math.h>
#include "asciilib.h"
#include "font.h"

char sword[3 * 7] = {
    ' ', 'O', ' ',
    ' ', 'O', ' ',
    ' ', 'O', ' ',
    ' ', 'O', ' ',
    'O', 'O', 'O',
    ' ', 'O', ' ',
    ' ', 'O', ' '
};
char* name = "test";

int main()
{
    /* Initialize ascii library */
    asciifb framebuffer;
    framebuffer.height = 32;
    framebuffer.width = 40;

    asciiinit(&framebuffer);

    /* draw circle in framebuffer */
    asciidrawcircle(&framebuffer, 1, 1, 15, 7, '#');
    /* render it */
    asciirenderfb(&framebuffer);
    /* clear framebuffer */
    asciiclearfb(&framebuffer);
    /* draw line in framebuffer */
    asciidrawline(&framebuffer, 1, 1, 9, 4, '*');
    /* render it */
    asciirenderfb(&framebuffer);
    /* clear framebuffer*/
    asciiclearfb(&framebuffer);
    /* copy character array to framebuffer */
    asciicopyatfb(&framebuffer, sword, 5, 5, 3, 7);
    /* copy text to framebuffer */
    asciicopyatfb(&framebuffer, name, 4, 13, strlen(name), 1);
    /* render it */
    asciirenderfb(&framebuffer);
    /* clear it */
    asciifreefb(&framebuffer);
}