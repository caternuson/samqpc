#ifndef AO_BLINKER_H
#define AO_BLINKER_H

#include "qpc.h"
#include "bsp.h"
#include "blinker.h"
#include "AOLED.h"

// Blinker "class" definition
typedef struct {
  QActive super;
  QTimeEvt timeEvt;

  bool current_state;
} Blinker;

// "public" methods
void Blinker_ctor(void);

// global pointer
extern QActive * const AO_Blinker;

#endif