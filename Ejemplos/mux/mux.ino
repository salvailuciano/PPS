//Constants
#define number_of_mux 1
#define numOfMuxPins number_of_mux * 8
#define enPin 2
#define channelA 5
#define channelB 6
#define channelC 7

//Init CD4051B
pinMode(channelA, OUTPUT);
pinMode(channelB, OUTPUT);
pinMode(channelC, OUTPUT);
pinMode(enPin, OUTPUT);
digitalWrite(channelA, LOW);
digitalWrite(channelB, LOW);
digitalWrite(channelC, LOW);
digitalWrite(enPin, LOW);

}

void loop() {
int A = 0;
int B = 1;
int C = 0;

digitalWrite(channelA, A);
digitalWrite(channelB, B);
digitalWrite(channelC, C);

}
