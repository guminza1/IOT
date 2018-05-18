void forward_right() {
  for (int i = 0; i < 1000; i++) {
    digitalWrite(cw_A, LOW);
    digitalWrite(cw_B, LOW);
    digitalWrite(cw_C, HIGH);
    digitalWrite(clk_A, HIGH);
    digitalWrite(clk_B, LOW);
    digitalWrite(clk_C, HIGH);
    delayMicroseconds(200);
    digitalWrite(clk_A, LOW);
    digitalWrite(clk_B, HIGH);
    digitalWrite(clk_C, LOW);
    delayMicroseconds(200);
  }
  digitalWrite(pump, HIGH);
  delay(relay);
  digitalWrite(pump, LOW);
  for (int i = 0; i < 2000 ; i++) {
    digitalWrite(cw_C, HIGH);
    digitalWrite(clk_C, HIGH);
    delayMicroseconds(200);
    digitalWrite(clk_C, LOW);
    delayMicroseconds(200);
  }
  digitalWrite(pump, HIGH);
  delay(relay);
  digitalWrite(pump, LOW);
  for (int i = 0; i < 2000 ; i++) {
    digitalWrite(cw_C, HIGH);
    digitalWrite(clk_C, HIGH);
    delayMicroseconds(200);
    digitalWrite(clk_C, LOW);
    delayMicroseconds(200);
  }
  digitalWrite(pump, HIGH);
  delay(relay);
  digitalWrite(pump, LOW);
}
void forward_left() {
  for (int i = 0; i < 3889; i++) {
    digitalWrite(cw_A, LOW);
    digitalWrite(cw_B, LOW);
    digitalWrite(clk_A, HIGH);
    digitalWrite(clk_B, LOW);
    delayMicroseconds(200);
    digitalWrite(clk_A, LOW);
    digitalWrite(clk_B, HIGH);

    delayMicroseconds(200);
  }
  digitalWrite(pump, HIGH);
  delay(relay);
  digitalWrite(pump, LOW);
  for (int i = 0; i < 2000 ; i++) {
    digitalWrite(cw_C, LOW);
    digitalWrite(clk_C, LOW);
    delayMicroseconds(200);
    digitalWrite(clk_C, HIGH);
    delayMicroseconds(200);
  }
  digitalWrite(pump, HIGH);
  delay(relay);
  digitalWrite(pump, LOW);
  for (int i = 0; i < 2000 ; i++) {
    digitalWrite(cw_C, LOW);
    digitalWrite(clk_C, LOW);
    delayMicroseconds(200);
    digitalWrite(clk_C, HIGH);
    delayMicroseconds(200);
  }
  digitalWrite(pump, HIGH);
  delay(relay);
  digitalWrite(pump, LOW);
}





void forward_rightv_2() {
  for (int i = 0; i < 3889; i++) {
    digitalWrite(cw_A, LOW);
    digitalWrite(cw_B, LOW);
    digitalWrite(clk_A, HIGH);
    digitalWrite(clk_B, LOW);
    delayMicroseconds(200);
    digitalWrite(clk_A, LOW);
    digitalWrite(clk_B, HIGH);
    delayMicroseconds(200);
  }
  digitalWrite(pump, HIGH);
  delay(relay);
  digitalWrite(pump, LOW);
  for (int i = 0; i < 2000 ; i++) {
    digitalWrite(cw_C, HIGH);
    digitalWrite(clk_C, HIGH);
    delayMicroseconds(200);
    digitalWrite(clk_C, LOW);
    delayMicroseconds(200);
  }
  digitalWrite(pump, HIGH);
  delay(relay);
  digitalWrite(pump, LOW);
  for (int i = 0; i < 2000 ; i++) {
    digitalWrite(cw_C, HIGH);
    digitalWrite(clk_C, HIGH);
    delayMicroseconds(200);
    digitalWrite(clk_C, LOW);
    delayMicroseconds(200);
  }
  digitalWrite(pump, HIGH);
  delay(relay);
  digitalWrite(pump, LOW);
}

void back() {
  statusy = digitalRead(switchy);
  statusx = digitalRead(switchx);
  for (statusx ; statusx != 0;) {
    digitalWrite(cw_C, LOW);
    digitalWrite(clk_C, HIGH);
    delayMicroseconds(200);
    digitalWrite(clk_C, LOW);
    delayMicroseconds(200);
    statusx = digitalRead(switchx);
  }
  delay(500);
  for (statusy ; statusy != 0;) {
    digitalWrite(cw_A, HIGH);
    digitalWrite(cw_B, HIGH);
    digitalWrite(clk_A, HIGH);
    digitalWrite(clk_B, LOW);
    delayMicroseconds(200);
    digitalWrite(clk_A, LOW);
    digitalWrite(clk_B, HIGH);
    delayMicroseconds(200);
    statusy = digitalRead(switchy);
  }
  statusy = digitalRead(switchy); 
  delay(500);
}
void back2() {
  statusy = digitalRead(switchy);
  statusx = digitalRead(switchx);
  for (statusx ; statusx != 0;) {
    digitalWrite(cw_C, LOW);
    digitalWrite(clk_C, HIGH);
    delayMicroseconds(200);
    digitalWrite(clk_C, LOW);
    delayMicroseconds(200);
    statusx = digitalRead(switchx);
  }
  delay(500);
  for (statusy ; statusy != 0;) {
    digitalWrite(cw_A, HIGH);
    digitalWrite(cw_B, HIGH);
    digitalWrite(clk_A, HIGH);
    digitalWrite(clk_B, LOW);
    delayMicroseconds(200);
    digitalWrite(clk_A, LOW);
    digitalWrite(clk_B, HIGH);
    delayMicroseconds(200);
    statusy = digitalRead(switchy);
  }
  statusy = digitalRead(switchy);
  delay(500);
}
