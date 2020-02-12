// NORTOS: The simplisity matter! By Aleksei Tertychnyi, 2015, WTFPL licenced
#ifndef __NORTOS_H
#define __NORTOS_H

#ifdef __cplusplus
extern "C" {
#endif
  
#define Q_SIZE_FAST 16
#include <stdint.h>

void pFastQueueIni(void); // initialization of Queue
int8_t F_push(void (*pointerQ)(void) ); // push element from the queue
void (*F_pull(void))(void); // pull element from the queue
void Delay_ms_OnFastQ(uint32_t Delay); 

uint32_t millis(void);   // redefine to get ms
  

int8_t F_last; // number of last element of fast-speed queue
int8_t F_first; // number of first element of fast-speed queue

uint32_t Timer;


__weak void SimpleF(){;};

void (*pFastQueue[Q_SIZE_FAST])();

inline void pFastQueueIni(void){ // initialization of Queue
  for(uint8_t i = 0; i < Q_SIZE_FAST; i++){
    pFastQueue[i] = SimpleF;
  }
  F_last = 0;
  F_first = 0;
  Timer = 0;
}

inline int8_t F_push(void (*pointerQ)(void) ){ // push element from the queue
  if ((F_last+1)%Q_SIZE_FAST == F_first)return 1;
  pFastQueue[F_last++] = pointerQ;
  F_last%=Q_SIZE_FAST;
  return 0;
}

inline void (*F_pull(void))(void){ // pull element from the queue
  void (*pullVar)(void);
  if (F_last == F_first)return SimpleF;
  pullVar = pFastQueue[F_first++];
  F_first%=Q_SIZE_FAST;
  return pullVar;
}

inline void Delay_ms_OnFastQ(uint32_t Delay){ // pull element from the queue
 uint32_t TargetTime = Delay + millis();
 while(millis() < TargetTime){
  F_pull()();
 }
}  
  
#ifdef __cplusplus
}
#endif

#endif