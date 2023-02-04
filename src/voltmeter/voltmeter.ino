int v0, v1, v2, v3;

void setup() {
  // put your setup code here, to run once:
  analogReference(DEFAULT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  v0 = analogRead(A0);
  v1 = analogRead(A1);
  v2 = analogRead(A2);
  v3 = analogRead(A3);
  Serial.println("V1: " + String(v0));
  Serial.println("V2: " + String(v1));
  Serial.println("V3: " + String(v2));
  Serial.println("V4: " + String(v3));
  delay(500);
}