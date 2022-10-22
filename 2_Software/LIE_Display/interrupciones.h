extern volatile int interruptCounter;
float tiempoInterrupcionsegundos= 0,5;//interrrupcion cada 500ms
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  interruptCounter++;
  portEXIT_CRITICAL_ISR(&timerMux);
}
 
void setup_interrupcion() {
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, tiempoInterrupcionsegundos*1000000, true);
  timerAlarmEnable(timer);
}
