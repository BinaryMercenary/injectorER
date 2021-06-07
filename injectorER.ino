
/////
// SAFETY WARNING: no gas! yes PPE! high PSI -- high pressure injection injuries which can results in amputation or death!!!
// && having no arms to hug // Dying dead is upsetting to ppl who :heart: you.
////

//// ATTN: not all pumps/injectors are 12v.  Do your own research.
//// NOTE: you can use different boards to pass the 12v signal to the injectors
//SSR (drives high)
//Switch (drives low)
////PS these drive HIGH on board reset for D1 Mini (and NodeMcu)

////Relay note:
//3 ms min shut, 2 ms min open at 90% duty cycle
////vs SSR can have a faster switch rate
//BUT I've bought some bad ones on ebay...

const uint8_t numColumns = 3;

float InjChart[][numColumns] = {
  {124,   3,     12}, //IDLE      950   rpms
  {88,    7.2,   10}, //ROLL     1200   rpms
  {50,    12.5,  16}, //DORK     1920   rpms
  {28,    14,    24}, //CRUISE 2850     rpms
  {18,    18,    28}, //FWY        3333 rpms
  {11.67, 21.67, 60}, //TORQ     3600   rpms
  {3.75,  21.25, 16}, //REV        4800 rpms
  {2,     19,    10}, //RelayLIMIT       5715   rpms
  {3,     19,    10}, //RED        5455 rpms
//{1,     19,    10}, //RealLIMIT               rpms //Most arduino relays can't do this. NOT Safe (may damage injectors).
};

const uint8_t numRows = sizeof(InjChart) / sizeof(InjChart[0]);

void setup() {
  //working pins - may actually be D2-D7 on some boards)
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);

  //This section does setup
  //BUT I use it to manually fire injectors
  //By pushing the reset button

  //condition all switches
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  delay(20);

  //release
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(D5, HIGH);
  digitalWrite(D6, HIGH);
  delay(1200);

}

//NOT attempting to splay, so not 100% realistic - threads/millis for that
//This section is a lot like a 0-60 DBW launch.
void loop() {

  for (int i=0;i<numRows;i++){
    for (int j=0;j<InjChart[i][2];j++){
      delay(InjChart[i][0]);
      digitalWrite(D1, LOW);
      digitalWrite(D2, LOW);
      digitalWrite(D3, LOW);
      digitalWrite(D4, LOW);
      digitalWrite(D5, LOW);
      digitalWrite(D6, LOW);

      delay(InjChart[i][1]);
      digitalWrite(D1, HIGH);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, HIGH);
      digitalWrite(D4, HIGH);
      digitalWrite(D5, HIGH);
      digitalWrite(D6, HIGH);
    }
  }

}

//// I've tested various denso fuel injectors:
//23209-0A020 highlander
//12204-20060 is300
//23209-46090 supra
//// so far only one reman company has let me down (drizzle at moderate/high speeds)
