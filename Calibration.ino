/*
 * This code is for calibration of EMG sensors
 */

float read_0 = 0.0;
float thresh_0 = 450;
int out00 = 0;
int out01 = 0;
int out02 = 0;
int signal0 = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(A3, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  read_0 = analogRead(A3);

  out02 = out01;
  out01 = out00;
  out00 = 0;
  if (read_0 > thresh_0) {
    out00 = 1;
  }
  signal0 = 0;
  if ((out00 + out01 + out02) >= 1 ) {
    signal0 = 1;
  }
  Serial.println(read_0);

  delay(5);

}
