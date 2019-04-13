#include <Wire.h>
#include <virtuabotixRTC.h>

//Time Clock
virtuabotixRTC myRTC(4, 5, 6); //Wiring of the RTC (CLK,DAT,RST)
int est;


// Sonar Sensor
const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;

// Relay
int Relay = 8;

// Mic Sensors
int Led = 2;
int MicPin = 3;
int val = 0;


// Setup Arduino
void setup() {
//1. Mic Sensors PinOut
pinMode(Led ,OUTPUT);
pinMode(MicPin,INPUT);

//2. Relay PinOut
pinMode(Relay ,OUTPUT);

//3. Ultrasonic PinOut
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT); 
Serial.begin(9600); 
}

//Time
void Time(int H, int M, char origin){
	myRTC.updateTime();
	int leaseH = myRTC.hours;
	int leaseM = myRTC.minutes;
	if (origin=="Ultrasonic") {
		leaseH += H;
	}
	else {
		leaseM += M;
	}
	
	//convert 60 minutes to an hour
	if (leaseM >= 60) {
		leaseH += 1;
		leaseM -= 60;
	}
}

//Ultrasonic Sensor
void Ultrasonic() {
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
	duration = pulseIn(echoPin, HIGH);
	distance= duration*0.034/2;
	Serial.print("Distance: ");
	Serial.println(distance);

	if (distance > 5){
		digitalWrite(Relay, HIGH);
		Time(1, 0, "Ultrasonic");
		for (; myRTC.minutes != leaseM && myRTC.hours != leaseH; myRTC.updateTime()) {
			delay(2000);
		}
		Time(0, 15, "Pre-mic");
		Mic();
	}
}

//Mic Sensor
void Mic() {
	for (; myRTC.minutes != leaseM; myRTC.updateTime){
		val = digitalRead(MicPin);
		if (val == HIGH){
			Time(0, 15, "Mic input");
		}
	}
	digitalWrite(Relay, 0);
}

//Main
void loop() {
  Ultrasonic();
}
