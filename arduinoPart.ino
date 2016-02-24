#define OPTIMUM 70   // optimum humidity level of tree as percentage.
#define MAX 85       // determined maximum humidity level of tree as percentage. 

int waterPin = 8;     


void setup(){
  
  Serial.begin(9600);
  pinMode(waterPin, OUTPUT);
}

void loop() { 
digitalWrite(waterPin, HIGH);     // watering system is inactive(in my system HIGH is inactive ).

if (Serial.available()) {         // for remote commands.
control(Serial.read() - '0');     // send to control function, because 2 and 3 commands can come.
}
  
int humValue = analogRead(A0);    // read humidity value from A0 pin as a voltage.


int humidity= 100 - ((30.855*(humValue/204.6))-11.504);  // convert voltage value to percentage shape like 70%.

if(humidity<0){

humidity = 0;             // if humidity sensor is at the outside, it takes huge values like 1235
                          // and the value is negative (etc. 100 - 1235), I assigned directly 0. 

Serial.print(humidity); Serial.println("%");
}

else { 
Serial.print(humidity); Serial.println("%");  // otherwise it takes normally values. 
}

if(humidity<OPTIMUM) {watering();}    // if value is lower than optimum, water.
if(humidity>MAX) {closeCover();}      // if value is higher than maximum 
                                     //(hard raining can cause to this situation), close cover.

delay(500); 
  
}

void control(int n){

  if(n==2) { watering(); }      // if user wants watering remotely, water.
  if(n==3) { closeCover(); }    // if user wants closing cover of garden, close.
  return;
}

void watering()
{
  digitalWrite(waterPin, LOW);      // watering is active (LOW = active)
  delay(5000);                      // five seconds water.
  digitalWrite(waterPin, HIGH);     // watering is inactive.
  return;
}

void closeCover()
{
                                    // the codes in closeCover() will be written soon :)
   return;
}

