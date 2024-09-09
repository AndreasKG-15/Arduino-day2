// C++ code
//
#define red 6
#define green 5
#define yellow 4
#define trigger 12
#define echo 13
int distanceThreshold = 0;

int cm = 0;

int inches = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  Serial.begin(9600);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
}

void loop()
{
  // set threshold distance to activate LEDs
  distanceThreshold = 30;
  // measure the ping time in cm
  cm = 0.01723 * readUltrasonicDistance(trigger, echo);
  // convert to inches by dividing by 2.54
  inches = (cm / 2.54);
  Serial.print(cm);
  Serial.print("cm, ");
  Serial.print(inches);
  Serial.println("in");
  if (cm > distanceThreshold) {
    turnOffLED(red);
    turnOffLED(green);
    turnOffLED(yellow);
  }
  if (cm <= distanceThreshold && cm > distanceThreshold - 10) {
    turnOnLED(red);
    turnOffLED(green);
    turnOffLED(yellow);
  }
  if (cm <= distanceThreshold - 10 && cm > distanceThreshold - 20) {
    turnOnLED(red);
    turnOnLED(green);
    turnOffLED(yellow);
  }
  if (cm <= distanceThreshold - 20 && cm > distanceThreshold - 25) {
    turnOnLED(red);
    turnOnLED(green);
    turnOnLED(yellow);
  }
  if (cm <= distanceThreshold - 25) {
    turnOnLED(red);
    turnOnLED(green);
    turnOnLED(yellow);
  }
  delay(100); // Wait for 100 millisecond(s)
}

void turnOffLED(int LED)
{
  digitalWrite(LED, LOW);
}
void turnOnLED(int LED)
{
  digitalWrite(LED, HIGH);
}
