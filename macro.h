#ifndef MACRO_H
#define MACRO_H

#define SET(port,b) (port) |= (1<<(b))
#define CLR(port,b) (port) &= ~(1<<(b))

#endif
