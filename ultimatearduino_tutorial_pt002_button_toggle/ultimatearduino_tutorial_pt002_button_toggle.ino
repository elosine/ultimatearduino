int bp = 2;
boolean bgate = true;
//toggle vars
int btogval = 0;
int btogamt = 10;
boolean btoggate = true;


void setup() {
  Serial.begin(9600);
  pinMode(bp, INPUT_PULLUP);
}

void loop() {

  if ( digitalRead(bp) == LOW) { //button pushed

    //momentary
    if (bgate) {
      bgate = false;
      Serial.print("b0:");
      Serial.println(1);
    }

    //toggle
    if (btoggate) {
      btoggate = false;
      btogval = (btogval + 1) % btogamt;
      Serial.print("bt0:");
      Serial.println(btogval);
    }


  }
  else { //button released

    //momentary
    if (!bgate) {
      bgate = true;
      Serial.print("b0:");
      Serial.println(0);
    }

    //toggle
    if (!btoggate) {
      btoggate = true;
    }


  }
  delay(30);
}
