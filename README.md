# asciilib
### asciilb is ASCII drawing library that can be used in embedded systems or systems with text mode only support (like serial port or MDA text mode)
## Usage
Include asciilib.h <br /> Create asciifb and set width and height of virtual framebuffer <br /> Initialize virtual framebuffer 
``` c
asciifb vfb;
vfb->width = WIDTH;
vfb->height = HEIGHT;
asciiinit(&vfb); 
```

After you drew in virtual framebuffer you must render it
``` c
asciiputpixel(&vfb, 0, 0, 'O');
asciirenderfb(&vfb);
```