int v0, v1, v2, v3;
int m0, m1, m2, m3;

void setup() {
  // put your setup code here, to run once:
  analogReference(DEFAULT);
  Serial.begin(9600);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  v0 = analogRead(A0);
  v1 = analogRead(A1);
  v2 = analogRead(A2);
  v3 = analogRead(A3);
  m0 = digitalRead(A4);
  m1 = digitalRead(A5);
  m2 = digitalRead(2);
  m3 = digitalRead(3);
  if (m0) {
    Serial.println("VAC1: " + String(v0));
  } else {
    Serial.println("VDC1: " + String(v0));
  }
  if (m1) {
    Serial.println("VAC2: " + String(v1));
  } else {
    Serial.println("VDC2: " + String(v1));
  }
  if (m2) {
    Serial.println("VAC3: " + String(v2));
  } else {
    Serial.println("VDC3: " + String(v2));
  }
  if (m3) {
    Serial.println("VAC4: " + String(v3));
  } else {
    Serial.println("VDC4: " + String(v3));
  }
  delay(500);
}