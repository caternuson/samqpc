#include "qpc.h"
#include "bsp.h"

#include "AOBlinker.h"
#include "AOLED.h"

Q_DEFINE_THIS_FILE

int main() {
  static QEvt const *blinkerQSto[10];
  static QEvt const *ledQSto[10];

  QF_init();

  /* initialize publish-subscribe... */
  // this is storage to keep track of who is subscribing to what events
  static QSubscrList subscrSto[MAX_PUB_SIG];  // the actual storage
  QF_psInit(subscrSto, Q_DIM(subscrSto));     // give it to QF to use

  /* initialize event pools... */
  // this is storage for the actual events
  static QF_MPOOL_EL(QEvt) smlPoolSto[2];                              // the actual storage
  QF_poolInit(smlPoolSto, sizeof(smlPoolSto), sizeof(smlPoolSto[0]));  // give it to QF to use

  BSP_init();

  Blinker_ctor();
  LED_ctor();

  QACTIVE_START(AO_Blinker,         // active object pointer to start
                1U,                 // priority at which to start the active object
                blinkerQSto,        // pointer to the storage for the ring buffer of the event queue
                Q_DIM(blinkerQSto), // length of the event queue
                (void *)0,          // pointer to the stack storage
                0U,                 // stack size
                (QEvt *)0);         // initial event (or 0)

  QACTIVE_START(AO_LED,             // active object pointer to start
                2U,                 // priority at which to start the active object
                ledQSto,            // pointer to the storage for the ring buffer of the event queue
                Q_DIM(ledQSto),     // length of the event queue
                (void *)0,          // pointer to the stack storage
                0U,                 // stack size
                (QEvt *)0);         // initial event (or 0)

  return QF_run();
}