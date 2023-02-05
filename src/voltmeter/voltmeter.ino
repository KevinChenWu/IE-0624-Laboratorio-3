const uint8_t n = 60;
volatile uint16_t s0[n], s1[n], s2[n], s3[n];
volatile uint8_t s;
volatile uint16_t offset;
volatile uint8_t d0, d1, d2, d3;
volatile float v0, v1, v2, v3;
volatile uint8_t m0, m1, m2, m3;

ISR(TIMER1_COMPA_vect) {
  if (s < n) {
    if (!d0) {
      s0[s] = analogRead(A0);
      offset += s0[s];
    } else if (!d1) {
      s1[s] = analogRead(A1);
    } else if (!d2) {
      s2[s] = analogRead(A2);
    } else if (!d3) {
      s3[s] = analogRead(A3);
    }
    s++;
  }
}

void setup() {
  // put your setup code here, to run once:
  analogReference(DEFAULT);
  Serial.begin(9600);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);

  TCCR1A = 0x00;
  TCCR1B = 0 | (1 << WGM12) | (1 << CS11) | (1 << CS10);
  TCCR1C = 0x00;
  OCR1A = 0x1457;
  //ADMUX = 0 | (1 << REFS0);
  //ADCSRA |= (1 << ADEN);
  sei();
}

void loop() {
  // put your main code here, to run repeatedly:
  s = 0;
  v0 = 0;
  v1 = 0;
  v2 = 0;
  v3 = 0;
  d0 = 0;
  d1 = 0;
  d2 = 0;
  d3 = 0;
  offset = 0;
  TCNT1 = 0;
  TIMSK1 |= (1 << OCIE1A);
  //ADCSRA |= (1 << ADIE);
  while (s < n);
  d0 = 1;
  s = 0;
  while (s < n);
  d1 = 1;
  s = 0;
  while (s < n);
  d2 = 1;
  s = 0;
  while (s < n);
  d3 = 1;
  s = 0;
  TIMSK1 &= ~(1 << OCIE1A);
  offset /= n;
  for (uint8_t i = 0; i < n; i++) {
    float a0 = s0[i] * 5.0000/1023;
    a0 -= (offset * 5.0000/1023);
    v0 += a0 * a0;
    float a1 = s1[i] * 5.0000/1023;
    a1 -= 2.5000;
    v1 += a1 * a1;
    float a2 = s2[i] * 5.0000/1023;
    a2 -= 2.5000;
    v2 += a2 * a2;
    float a3 = s3[i] * 5.0000/1023;
    a3 -= 2.5000;
    v3 += a3 * a3;
  }
  v0 /= n;
  v1 /= n;
  v2 /= n;
  v3 /= n;
  Serial.println("v0 " + String(v0));
  v0 = sqrt(v0);
  v1 = sqrt(v1);
  v2 = sqrt(v2);
  v3 = sqrt(v3);
  m0 = digitalRead(A4);
  m1 = digitalRead(A5);
  m2 = digitalRead(2);
  m3 = digitalRead(3);
  if (m0) {
    Serial.println("VAC1: " + String(v0, 4));
  } else {
    Serial.println("VDC1: " + String(v0, 4));
  }
  if (m1) {
    Serial.println("VAC2: " + String(v1, 4));
  } else {
    Serial.println("VDC2: " + String(v1, 4));
  }
  if (m2) {
    Serial.println("VAC3: " + String(v2, 4));
  } else {
    Serial.println("VDC3: " + String(v2, 4));
  }
  if (m3) {
    Serial.println("VAC4: " + String(v3, 4));
  } else {
    Serial.println("VDC4: " + String(v3, 4));
  }
  delay(1000);
}