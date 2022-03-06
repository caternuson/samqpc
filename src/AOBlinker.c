#include "AOBlinker.h"

static Blinker blinker;                       // the single (local) Blinker instance
QActive * const AO_Blinker = &blinker.super;  // global pointer

// "private" methods
static QState Blinker_initial (Blinker * const me, QEvt const * const e);
static QState Blinker_run     (Blinker * const me, QEvt const * const e);

//-------------------------------------------------------------------
//-------------------------------------------------------------------
void Blinker_ctor(void) {
  Blinker * const me = &blinker;
  me->current_state = false;
  QActive_ctor(&me->super, Q_STATE_CAST(&Blinker_initial));
  QTimeEvt_ctorX(&me->timeEvt, &me->super, BLINKER_TIMEOUT_SIG, 0U);
}

QState Blinker_initial(Blinker * const me, QEvt const * const e) {
  (void)e; // to avoid compiler warn :(
  QTimeEvt_armX(&me->timeEvt, BSP_TICKS_PER_SEC, BSP_TICKS_PER_SEC);
  return Q_TRAN(&Blinker_run);
}

QState Blinker_run(Blinker * const me, QEvt const * const e) {
  QState status;
  switch (e->sig) {
    case Q_ENTRY_SIG:
      status = Q_HANDLED();
      break;
    case BLINKER_TIMEOUT_SIG:
      if (me->current_state) {
        // send LED_OFF
        QF_PUBLISH(Q_NEW(QEvt, LED_OFF_SIG), me);
        me->current_state = false;
      } else {
        // send LED_ON
        QF_PUBLISH(Q_NEW(QEvt, LED_ON_SIG), me);
        me->current_state = true;
      }
      status = Q_HANDLED();
      break;
    default:
      status = Q_SUPER(&QHsm_top);
      break;
  }
  return status;
}