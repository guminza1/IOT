#include <SoftwareSerial.h>;
SoftwareSerial mySerialmega(5, 4); // rx tx
int clk_A = 13;
int cw_A = 12;
int clk_B = 11;
int cw_B  = 10;
int clk_C = 9;
int cw_C  = 8;
int pump = 15;
int switchy = 7;
int switchx = 6;
int statusx = 1;
int statusy = 1;
String input;
unsigned long relay;
unsigned long T_pump;
char y = 'y';
//////////////////////////
//varaible Manual

int a = 3;
int b = 2;
int c = 19;
int s_a, s_b, s_c;  // Read status a b c

//end varailable Manual
/////////////////////////

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  mySerialmega.begin(9600);
  pinMode(clk_A, OUTPUT);
  pinMode(cw_A, OUTPUT);
  pinMode(clk_B, OUTPUT);
  pinMode(cw_B, OUTPUT);
  pinMode(clk_C, OUTPUT);
  pinMode(cw_C, OUTPUT);
  pinMode(switchy, INPUT_PULLUP);
  pinMode(switchx, INPUT_PULLUP);
  pinMode (pump, OUTPUT);
  /////////////////////////////////////
  //pinMode Manual
  pinMode(a, INPUT_PULLUP);
  pinMode(b, INPUT_PULLUP);
  pinMode(c, INPUT_PULLUP);
  // end pinMode Manual
  ////////////////////////////////////
}

void loop() {
  // put your main code here, to run repeatedly:
  statusy = digitalRead(switchy);
  statusx = digitalRead(switchx);
  s_a = digitalRead(a);
  s_b = digitalRead(b);
  s_c = digitalRead(c);

  /////////////////////////////////////////////////////
  // input Serial//
  while (mySerialmega.available()) {
    String input1 = mySerialmega.readString();
    Serial.println(input1);

    Serial.println(input1);

    input = input1.substring(0, 1);
    int i_a = input1.indexOf("#");
    int i_b = input1.indexOf("#", i_a + 1);
    String relay1 = input1.substring(i_a + 1, i_b);
    String T_pump1 = input1.substring(i_b + 1, input1.length());
    relay = relay1.toInt() * 1000;
    T_pump = T_pump1.toInt() * 1000;


    statusy = digitalRead(switchy);
    statusx = digitalRead(switchx);

    if (input == "q") {
      mySerialmega.print("1");
      delay(1000);
      mySerialmega.end();
      back();
      digitalWrite(pump, HIGH);
      delay(T_pump);
      digitalWrite(pump, LOW);
      forward_right();
      forward_left();
      forward_rightv_2();
      forward_left();
      back2();
      back2();  
      mySerialmega.print("0");   
    }
    //back();
    mySerialmega.begin(9600);
    
  }
  //end input Serial//
  /////////////////////////////////////////////////////
  // forward
  if ( s_a == 0 && s_b == 0 && s_c == 1) {
    digitalWrite(cw_A, LOW);
    digitalWrite(cw_B, LOW);
    digitalWrite(clk_A, HIGH);
    digitalWrite(clk_B, LOW);
    delayMicroseconds(200);
    digitalWrite(clk_A, LOW);
    digitalWrite(clk_B, HIGH);
    delayMicroseconds(200);
    return;
  }

  // back
  if (s_a == 1 && s_b == 1 && s_c == 0 && statusy  != 0) {
    digitalWrite(cw_A, HIGH);
    digitalWrite(cw_B, HIGH);
    digitalWrite(clk_A, HIGH);
    digitalWrite(clk_B, LOW);
    delayMicroseconds(200);
    digitalWrite(clk_A, LOW);
    digitalWrite(clk_B, HIGH);
    delayMicroseconds(200);
    return;
  }

  // left
  if (s_a == 1 && s_b == 0 && s_c == 0 && statusx  != 0) {
    digitalWrite(cw_C, LOW);
    digitalWrite(clk_C, HIGH);
    delayMicroseconds(300);
    digitalWrite(clk_C, LOW);
    delayMicroseconds(300);
    return;
  }

  // right
  if (s_a == 0 && s_b == 1 && s_c == 0) {
    digitalWrite(cw_C, HIGH);
    digitalWrite(clk_C, HIGH);
    delayMicroseconds(300);
    digitalWrite(clk_C, LOW);
    delayMicroseconds(300);
    return;
  }
  if (s_a == 1 && s_b == 0 && s_c == 1) {
    digitalWrite(pump, HIGH);
    s_a = digitalRead(a);
    s_b = digitalRead(b);
    s_c = digitalRead(c);
    return;
  }
  else {
    digitalWrite(pump, LOW);
  }
}





