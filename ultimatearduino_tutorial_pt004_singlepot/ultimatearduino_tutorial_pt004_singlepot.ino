#define NB 7
//BUTTONS
////Momentary button vars
int bp[NB] = { 2, 3, 4, 5, 6, 7, 16 }; //arduino input pin numbers
boolean bg[NB] = {true, true, true, true, true, true, true};
//Toggle button vars
int btv[NB] = {0, 0, 0, 0, 0, 0, 0};
int btamt[NB] = {2, 2, 2, 2, 2, 7, 10};
boolean btg[NB] = {true, true, true, true, true, true, true};

//POTS
int p = A3;
int pv;
int ppv = 0;


void setup() {
  Serial.begin(9600);
  for (int i = 0; i < NB; i++) pinMode(bp[i], INPUT_PULLUP);
}

void loop() {

  //POTS
  pv = analogRead(p);
  if ( pv < (ppv - 2) || pv > (ppv + 2) ) {
    Serial.print("p0:");
    Serial.println(pv);
  }

  ppv = pv;


  //BUTTONS
  for (int i = 0; i < NB; i++) {

    if ( digitalRead(bp[i]) == LOW) { //button pushed

      //momentary
      if (bg[i]) {
        bg[i] = false;
        Serial.print("b");
        Serial.print(String(i));
        Serial.print(":");
        // Serial.print( "b" + String(i) + ":");
        Serial.println(1);
      }

      //toggle
      if (btg[i]) {
        btg[i] = false;
        btv[i] = (btv[i] + 1) % btamt[i];
        Serial.print( "bt" + String(i) + ":");
        Serial.println(btv[i]);
      }


    }
    else { //button released

      //momentary
      if (!bg[i]) {
        bg[i] = true;
        Serial.print( "b" + String(i) + ":");
        Serial.println(1);
      }

      //toggle
      if (!btg[i]) {
        btg[i] = true;
      }


    }

  }
  delay(30);
}
