#define NB 7
#define NP 7
#define NF 0
//BUTTONS
////Momentary button vars
int bp[NB] = {3,4,5,6,7,16 }; //arduino input pin numbers
boolean bg[NB] = {true, true, true, true, true, true, true};
//Toggle button vars
int btv[NB] = {0, 0, 0, 0, 0, 0, 0};
int btamt[NB] = {2, 2, 2, 2, 2, 7, 10};
boolean btg[NB] = {true, true, true, true, true, true, true};

//POTS
int p[NP] =  {3, A2,A1,A0,A8,A9,A10  }; //analog input pins
int pv[NP];
int ppv[NP] = {0, 0, 0, 0, 0, 0, 0}; //previous pot value

//FSRS
int fsr[NF] = {};
int fsrv[NF];
int fsrthresh[NF] = {};
boolean fsrpeakgate[NF] = {};
int fsrpv[NF] = {};


void setup() {
  Serial.begin(9600);
  for (int i = 0; i < NB; i++) pinMode(bp[i], INPUT_PULLUP);
}

void loop() {

  //FSRS
  for (int i = 0; i < NF; i++) {
    //Continuous Data
    fsrv[i] = analogRead(fsr[i]); //read analog pin connected to fsr
    //Peak Detection
    if (fsrv[i] > fsrthresh[i]) {
      Serial.print( "fsr" + String(i) + ":");
      Serial.println(fsrv[i]);
      if (fsrv[i] > fsrpv[i]) { //is it going up?
        fsrpv[i] = fsrv[i];
      }
      else { //its going down i.e., val<pval
        if (fsrpeakgate[i]) { //if gate is open
      Serial.print( "fsp" + String(i) + ":");
          Serial.println(fsrpv[i]); //this is our peak
          fsrpeakgate[i] = false; //close gate
        }
      }
    }
    else { //is below thresh
      if (!fsrpeakgate[i]) {
        fsrpeakgate[i] = true;
        fsrpv[i] = 0;
      }
    }
  }


  //POTS
  for (int i = 0; i < NP; i++) {
    pv[i] = analogRead(p[i]);
    if ( pv[i] < (ppv[i] - 2) || pv[i] > (ppv[i] + 2) ) {
      Serial.print( "p" + String(i) + ":");
      Serial.println(pv[i]);
    }
    ppv[i] = pv[i];
  }


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
