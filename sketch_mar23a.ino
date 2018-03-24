#include <dht.h>

dht DHT;

#define DHT11_PIN 7

int Mercury_tilt = 8;
int Buzzer = 10;

int shockPin = 11; // Use Pin 10 as our Input
int shockVal = HIGH; // This is where we record our shock measurement
boolean bAlarm = false;

unsigned long lastShockTime; // Record the time that we measured a shock

int shockAlarmTime = 250; // Number of milli seconds to keep the shock alarm high


void setup(){
  Serial.begin(2400);
  pinMode(Buzzer, OUTPUT);
  pinMode(Mercury_tilt, INPUT);

pinMode (shockPin, INPUT) ; // input from the KY-002
}

void loop()
{

  //CODE FOR HUMIDITY/TEMP SENSOR
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  delay(1000);

  //CODE FOR TILT AND BUZZER SENSOR
  if (digitalRead(Mercury_tilt)) {//if up tilt
    
    digitalWrite(Buzzer,LOW); //ring the Buzzer
  }
    else {//if not press
      digitalWrite(Buzzer, HIGH);  //turn off the Buzzer
    }


shockVal = digitalRead (shockPin) ; // read the value from our sensor
  
  if (shockVal == LOW) // If we're in an alarm state
  {
    lastShockTime = millis(); // record the time of the shock
    // The following is so you don't scroll on the output screen
    if (!bAlarm){
      Serial.println("Shock Alarm");
      bAlarm = true;
    }
  }
  else
  {
    if( (millis()-lastShockTime) > shockAlarmTime  &&  bAlarm){
      Serial.println("no alarm\n");
      
      bAlarm = false;
    }
  }
 

}
