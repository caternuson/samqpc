#include "AOLED.h"

static LED led;                       // the single (local) Blinker instance
QActive * const AO_LED = &led.super;  // global pointer

// "private" methods
static QState LED_initial (LED * const me, QEvt const * const e);
static QState LED_run     (LED * const me, QEvt const * const e);

//-------------------------------------------------------------------
//-------------------------------------------------------------------
void LED_ctor(void) {
  LED * const me = &led;
  QActive_ctor(&me->super, Q_STATE_CAST(&LED_initial));
}

QState LED_initial(LED * const me, QEvt const * const e) {
  QActive_subscribe(&me->super, LED_ON_SIG);
  QActive_subscribe(&me->super, LED_OFF_SIG);
  return Q_TRAN(&LED_run);
}

QState LED_run(LED * const me, QEvt const * const e) {
  switch (e->sig) {
    case Q_ENTRY_SIG:
      break;
    case LED_ON_SIG:
      BSP_ledOn();
      break;
    case LED_OFF_SIG:
      BSP_ledOff();
      break;
    default:
      return Q_SUPER(&QHsm_top);
  }
  return Q_HANDLED();
}
