int led = 9;           
int brightness = 0;    
int fadeamount = 5;    
int lightsense = A0;
int sensorval = 0;

void setup() {
  // declare pin 9 to be an output:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
    sensorval = analogRead(lightsense);
    if (sensorval >=600){
		analogWrite(led,0);
    } else if (sensorval >=500 and sensorval <600){
		analogWrite(led,100);
    } else if (sensorval >=400 and sensorval <500){
		analogWrite(led,151);
    } else if (sensorval >=300 and sensorval <400){
		analogWrite(led,177);
    } else if (sensorval >=200 and sensorval <300){
		analogWrite(led,200);
    } else if (sensorval >=100 and sensorval <200){
		analogWrite(led,226);
    } else {
		analogWrite(led,255);
    }
}
