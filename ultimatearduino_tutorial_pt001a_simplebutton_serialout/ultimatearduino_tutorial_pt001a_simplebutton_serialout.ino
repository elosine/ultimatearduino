int bp = 2;
int bval;

void setup() {
  Serial.begin(9600);
  pinMode(bp, INPUT_PULLUP);
}

void loop() {
  if( digitalRead(bp) == HIGH){
    Serial.print("b0:");
    Serial.println(0);
  }
  else{
    Serial.print("b0:");
    Serial.println(1);
  }
  delay(30);
}
