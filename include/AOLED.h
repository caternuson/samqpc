#ifndef AO_LED_H
#define AO_LED_H

#include "qpc.h"
#include "bsp.h"
#include "blinker.h"

// LED "class" definition
typedef struct {     /* the LED active object type definition */
    QActive super;   /* inherit QActive */
} LED;

// "public" methods
void LED_ctor(void);

// global pointer
extern QActive * const AO_LED;


#endif