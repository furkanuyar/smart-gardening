#define OPTIMUM 70
#define MAX 85

int waterPin = 8;
int coverPin = 9;

void setup() {
  Serial.begin(9600);
  pinMode(waterPin, OUTPUT);
}

void loop() {
  // watering system is inactive.
  digitalWrite(waterPin, HIGH);

  // sends to control function,
  if (Serial.available()) {
    control(Serial.read() - '0');
  }
  // reads humidity value from A0 pin as a voltage.  
  int humValue = analogRead(A0);

  // converts voltage value to percentage shape like 70%.
  int humidity = 100 - ((30.855 * (humValue / 204.6)) - 11.504);

  // if humidity sensor doesn't have connection with soil, takes default zero value.
  if (humidity < 0) {
    humidity = 0;
    Serial.print(humidity);
    Serial.println("%");
  }

  // otherwise it takes real measured value.
  else {
    Serial.print(humidity);
    Serial.println("%");
  }

  // if value is lower than optimum, watering is activated.
  if (humidity < OPTIMUM) {
    watering();
  }

  // if value is higher than optimum, closing cover is activated.
  // hard rain can cause to this situation.
  if (humidity > MAX) {
    closeCover();
  }
  delay(500);
}

void control(int n) {
  // if user triggers watering operation.
  if (n == 2) {
    watering();
  }
  // if user triggers closing cover operation.
  if (n == 3) {
    closeCover();
  }
  return;
}

// when watering operation is triggered, it is active during five seconds.
void watering() {
  digitalWrite(waterPin, LOW);
  delay(5000);
  digitalWrite(waterPin, HIGH);
  return;
}

// when closing cover operation is triggered, it is active during eight seconds.
void closeCover() {
  digitalWrite(coverPin, LOW);
  delay(8000);
  return;
}

// when opening cover operation is triggered, it is active during eight seconds.
void openCover() {
  digitalWrite(coverPin, HIGH);
  delay(8000);
  return;
}
