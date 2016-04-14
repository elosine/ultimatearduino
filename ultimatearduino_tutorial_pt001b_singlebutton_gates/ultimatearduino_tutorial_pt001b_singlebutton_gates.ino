int bp = 2;
int bval;
boolean bgate = true;

void setup() {
  Serial.begin(9600);
  pinMode(bp, INPUT_PULLUP);
}

void loop() {
  if ( digitalRead(bp) == HIGH) {
    if (bgate) {
      bgate = false;
      Serial.print("b0:");
      Serial.println(0);
    }

  }
  else { //button pushed
    if (!bgate) {
      bgate = true;
      Serial.print("b0:");
      Serial.println(1);
    }
  }
  delay(30);
}
