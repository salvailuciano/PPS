#include <Arduino.h>
#include "mux.h"
void setup_mux()
{
pinMode(channelA, OUTPUT);
pinMode(channelB, OUTPUT);
pinMode(channelC, OUTPUT);

digitalWrite(channelA, LOW);
digitalWrite(channelB, LOW);
digitalWrite(channelC, LOW);
}
