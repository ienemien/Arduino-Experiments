#define R0 0.10
#define MQ7_PIN A0

void setup() {
 Serial.begin(9600);
 Serial.print("Volts per bit = ");
 float voltsPerBit = 5.0/1024.0;
 Serial.print(voltsPerBit, 6);
 Serial.print("\n Warming up. \n");
 delay(120000);
}
 
void loop() {

  float sensorValue = analogRead(MQ7_PIN);
  Serial.print("sensorValue: ");
  Serial.print(sensorValue);
  Serial.print("\n");
  float sensorVolt = sensorValue * (5.0/1024.0);
  Serial.print("sensorVolt: ");
  Serial.print(sensorVolt, 6);
  Serial.print("\n");
  
  float Rs = (5.0-sensorVolt)/sensorVolt;
  Serial.print("Rs: ");
  Serial.print(Rs, 6);
  Serial.print("\n");

//  float ppm = ??

  delay(1000);
// float sensor_volt = 0;
// float RS_gas = 0;
// float ratio = 0;
// float sensorValue = 0;
// 
// 
// for(int i = 0; i<900; i++){
//   sensorValue = analogRead(A0);
//   sensor_volt = sensorValue/1024*5.0;
//   RS_gas = (5.0-sensor_volt)/sensor_volt;
//   ratio = RS_gas/R0; 
//   float ppm = 100 * pow(log10(40)/log10(0.09), ratio);
//   Serial.print("PPM: ");
//   Serial.println(ppm);
//   delay(100);
// }
}
