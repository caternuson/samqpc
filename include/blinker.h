#ifndef _BLINKER_H
#define _BLINKER_H

enum BlinkerSignals {
  LED_ON_SIG = Q_USER_SIG,
  LED_OFF_SIG,
  BLINKER_TIMEOUT_SIG,
  MAX_PUB_SIG
};

#endif