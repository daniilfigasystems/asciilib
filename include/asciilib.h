#ifndef ASCIILIB
#define ASCIILIB

#ifndef CUSTOMRENDER
#include <stdio.h>
#endif
#include <string.h>
#include <stdlib.h>
#include <math.h>

double asciifactorialstable[20];

typedef struct _asciifb
{
    char* fb;
    int width;
    int height;
    int size;
} asciifb;

void asciiinit(asciifb* vfb);
void asciiclearfb(asciifb* vfb);
void asciicopyatfb(asciifb* vfb, char* src, int offsetx, int offsety, int width, int height);
void asciicopyfb(asciifb* dst, asciifb* src);
void asciidrawcircle(asciifb* vfb, int x, int y, int x1, int y1, char c);
void asciidrawline(asciifb* vfb, int x, int y, int x1, int y1, char c);
void asciiputpixel(asciifb* vfb, int x, int y, char c);
void asciirenderfb(asciifb* vfb);
void asciifreefb(asciifb* vfb);

void asciiinitmath();
double asciifactorial(double n);
double asciipow(double num, double n);
double asciicos(double n);
double asciisin(double n);

char asciigrayscale2ascii(unsigned char grayscale);
void asciigrayscalearray2asciiarray(char* dst, char* src, int width, int height);


/**
* @brief Initialize ascii virtual framebuffer
* @param vfb Pointer to virtual framebuffer
* @return Nothing
*/
void asciiinit(asciifb* vfb)
{
    vfb->size = vfb->width * vfb->height;
    vfb->fb = (char*)malloc(vfb->size);

    memset(vfb->fb, ' ', vfb->size);
}

/**
* @brief Clear virtual framebuffer
* @param vfb Pointer to virtual framebuffer
* @return Nothing
*/
void asciiclearfb(asciifb* vfb)
{
    memset(vfb->fb, ' ', vfb->size);
}

/**
* @brief Copy content of src to virtual framebuffer at offset
* @param vfb Pointer to virtual framebuffer
* @param src Pointer to array with ascii data
* @param offsetx X offset
* @param offsety Y offset
* @param width Width of src
* @param height Height of src
* @return Nothing
*/
void asciicopyatfb(asciifb* vfb, char* src, int offsetx, int offsety, int width, int height)
{
    if ((offsety * vfb->width) + offsetx > vfb->size)
        return;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
            vfb->fb[((offsety * vfb->width) + offsetx) + ((y * vfb->width) + x)] = src[(y * width) + x];
    }
}

/**
* @note Source can't be larger than destination
* @brief Copy primary virtual framebuffer to secondary virtual framebuffer
* @param dst Pointer to primary virtual framebuffer
* @param src Pointer to secondary virtual framebuffer
* @return Nothing
*/
void asciicopyfb(asciifb* dst, asciifb* src)
{
    if (src->size > dst->size)
        return;

    memcpy(dst->fb, src->fb, src->size);
}

/**
* @brief Put pixel
* @param vfb Pointer to virtual framebuffer
* @param x X of pixel
* @param y Y of pixel
* @param c Character of pixel
* @return Nothing
*/
void asciiputpixel(asciifb* vfb, int x, int y, char c)
{
    if ((y * vfb->width) + x > vfb->size)
        return;
    
    vfb->fb[(y * vfb->width) + x] = c == 0 ? ' ' : c;
}

/**
* @brief Draw circle
* @param vfb Pointer to virtual framebuffer
* @param x X of circle
* @param y Y of circle
* @param x1 X1 of circle
* @param y1 Y1 of circle
* @param c Character of circle to draw
* @return Nothing
*/
void asciidrawcircle(asciifb* vfb, int x, int y, int x1, int y1, char c)
{
    for (int i = 0; i < 1000; i++)
        asciiputpixel(vfb, x1 * cos(i) + x + x1, y1 * sin(i) + y + y1, c);
}

/**
* @brief Draw line
* @param vfb Pointer to virtual framebuffer
* @param x X of line
* @param y Y of line
* @param x1 X1 of line
* @param y1 Y1 of line
* @param c Character of line to draw
* @return Nothing
*/
void asciidrawline(asciifb* vfb, int x, int y, int x1, int y1, char c)
{
    for (int i = 0; i < 1000; i++)
        asciiputpixel(vfb, x1 * sin(i) + x, y1 * sin(i) + y, c);
}

#ifndef CUSTOMRENDER
/**
* @brief Render virtual framebuffer
* @param vfb Pointer to virtual framebuffer to render
* @return Nothing
*/
void asciirenderfb(asciifb* vfb)
{
    for (int y = 0; y < vfb->height; y++)
    {
        for (int x = 0; x < vfb->width; x++)
            putchar(vfb->fb[(y * vfb->width) + x]);

        putchar('\n');
    }   
}
#endif

/**
* @brief Free virtual framebuffer
* @param vfb Pointer to virtual framebuffer to free
* @return Nothing
*/
void asciifreefb(asciifb* vfb)
{
    free(vfb->fb);
}

/* cos and sin are under construction as i really poor at understanding math language */
#define ABS(x) ((x<0)?(-x):(x))

/**
* @brief Initialize math module
* @return Nothing
*/
void asciiinitmath()
{
    for (int i = 1; i < 20+1; i++)
        asciifactorialstable[i-1] = asciifactorial(i);
}

/**
* @brief Custom factorial function
* @param n Value
* @return Factorial of n
*/
double asciifactorial(double n)
{
    if (n==1)
        return 1;
    else
        return (double)n * asciifactorial(n - 1.0);
}

/**
* @brief Custom power function
* @param num Number to power
* @param n Value
* @return Power of num
*/
double asciipow(double num, double n)
{
    double k = 1;
    
    for (int i = 0; i < ABS(n); ++i)
        k *= n;

    return k;
}

/**
* @brief Custom cosine function
* @param n Value
* @return Cosine of n
*/
double asciicos(double n)
{
    double cosnum, d = 1.0;
    
    for (int i = 1; i <= (20 / 2) - 1; i++)
    {
        cosnum = pow(n, (i * 2)) / asciifactorialstable[(i * 2) - 1];
        if (i & 0x01)
            d -= cosnum;
        else
            d += cosnum;
    }

    return d;
}

/**
* @brief Custom sine function
* @param n Value
* @return Sine of n
*/
double asciisin(double n)
{
    double cosnum, d;
    for (int i = 0; i <= (20 / 2) - 1; i++)
    {
        cosnum = (asciipow(n, (i * 2) + 1) / asciifactorialstable[i * 2]);
        if (i & 0x01)
            d -= cosnum;
        else
            d += cosnum;
    }

    return d;
}

/* Converting utilites */

/**
* @brief Grayscale (8bit/pixel) to ascii
* @param grayscale Grayscale value
* @return Converted grayscale to ascii
*/
char asciigrayscale2ascii(char grayscale)
{
    if (grayscale < 25) return '@';
    if (grayscale < 50) return '%';
    if (grayscale < 75) return '#';
    if (grayscale < 100) return '*';
    if (grayscale < 125) return '+';
    if (grayscale < 150) return '=';
    if (grayscale < 175) return '-';
    if (grayscale < 200) return ':';
    if (grayscale < 225) return '.';
    return ' ';
}

/**
* @brief Convert array of grayscale pixels to ascii
* @param dst Pointer to destination array
* @param src Pointer to source array
* @param width Width of source
* @param height Height of source
* @return Nothing
*/
void asciigrayscalearray2asciiarray(char* dst, char* src, int width, int height)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
            dst[(y * width) + x] = asciigrayscale2ascii(src[(y * width) + x]);
    }
}

#endif