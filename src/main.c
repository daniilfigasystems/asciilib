#include <stdio.h>
#include <math.h>
#include "asciilib.h"
#include "font.h"

char sword[3 * 7] = {
    ' ', 'O', ' ',
    ' ', 'O', ' ',
    'O', 'O', 'O',
    ' ', 'O', ' ',
    ' ', 'O', ' ',
    ' ', 'O', ' ',
    ' ', 'O', ' '
};
char* name = "Sigma";

int main()
{
    asciifb framebuffer;
    framebuffer.height = 32;
    framebuffer.width = 40;

    asciiinit(&framebuffer);

    asciidrawcircle(&framebuffer, 1, 1, 15, 7, '#');
    asciirenderfb(&framebuffer);
    asciiclearfb(&framebuffer);
    asciidrawline(&framebuffer, 1, 1, 9, 4, '*');
    asciirenderfb(&framebuffer);
    asciiclearfb(&framebuffer);
    asciicopyatfb(&framebuffer, sword, 5, 5, 3, 7);
    asciicopyatfb(&framebuffer, name, 4, 13, strlen(name), 1);
    asciirenderfb(&framebuffer);
    asciifreefb(&framebuffer);
}