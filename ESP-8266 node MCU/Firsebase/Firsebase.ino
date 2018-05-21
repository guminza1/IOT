////////////////
//22 04 2561
//facebook :
///////////////
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <DHT.h>


#include <SoftwareSerial.h>
SoftwareSerial mySerial(D6, D7); //rx tx
// Config Firebase
#define FIREBASE_HOST "smartfarm-cg.firebaseio.com"
#define FIREBASE_AUTH "j6sQithe5Hf9xLtMK6y4wYx1kyxfa5TaYT1oP9gz"

// Config connect WiFi
#define WIFI_SSID "CG Academy Club"
#define WIFI_PASSWORD "cg24992399"

#define DHTTYPE DHT22
#define DHTPIN D5

#include "Wire.h"
#define PCF8591 (0x48)
byte adcvalue0, adcvalue1, adcvalue2, adcvalue3;

DHT dht(DHTPIN, DHTTYPE);
float h ; //readHumidity;
float t ; //readTemperature;
int t_sec = 1;

int check_net = 0;

unsigned long t_millis = 0;
int time_tm;
int time_te;

//variable manual
String s_m;
int a = D8;
int b = 1;// 1 tx D7
int c = 3;// 3 rx D6
// end varlaible manual

int LED = D0;
//status working//
String s_work;
//end status working//
//history//
String day_time;
String history_day, num_day, years;
String t_h_his, t_h_his1, t_h_his2;

//variable switch_morning_evening   && switch humidity &temperrature
String sw_morning, sw_evening, sw_h, sw_t;


//time current
int time_current;

void setup() {
  ////////////
  //pinMode Manual

  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);

  //end pinMode Manual
  ////////////
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  mySerial.begin(9600);
  Wire.begin();

  WiFi.mode(WIFI_STA);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  dht.begin();
  int t_sec = 1;
}

void loop() {
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Internet reconnecting ");
    delay(200);
    Serial.print(".");
    delay(200);
    Serial.print(".");
    delay(200);
    Serial.print(".");
    delay(200);
    Serial.print(".");
    delay(200);
    Serial.println(".");
    check_net = 1;
    delay(500);
  }
  if (check_net == 1) {
    Serial.println();
    Serial.print("connected: ");
    Serial.println(WiFi.localIP());
    check_net = 0;
  }
  if (millis() >= t_millis) {
    t_millis += 1000;
    tem_hu();
  }
  //Day and Time//
  day_time = Day();
  String day = day_time.substring(0, 3);
  String mont = day_time.substring(4, 7);
  years = day_time.substring(20, 24);
  Firebase.setString("Date_Time_Current/day", day);
  String hour = day_time.substring(11, 13);
  Firebase.setString("Date_Time_Current/hour", hour);
  String minute = day_time.substring(14, 16);
  Firebase.setString("Date_Time_Current/minute", minute);

  String minute_s;
  if (minute.charAt(0) == '0') {
    minute_s = minute.substring(1);
  }
  else {
    minute_s = minute;
  }

  String eq_time = hour + minute_s;
  time_current = eq_time.toInt();

  history_day = "\"\\\"" + day + " " + num_day + " " + mont + " " + years + "   Time " + hour + "." + minute + "\"\\\"";

  /////////////////////////////////////////////////
  // Manual
  s_m = Firebase.getString("/Manual/switch/");
  while (s_m == "1") {
    pinMode(a, OUTPUT);
    pinMode(b, OUTPUT);
    pinMode(c, OUTPUT);
    mySerial.end();
    String s_a = Firebase.getString("/Manual/left/");
    while (s_a == "1") {
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      s_a = Firebase.getString("/Manual/left/");
    }

    String s_d = Firebase.getString("/Manual/right/");
    while (s_d == "1") {
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, LOW);
      s_d = Firebase.getString("/Manual/right/");
    }
    String s_w = Firebase.getString("/Manual/forward/");
    while (s_w == "1") {
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      s_w = Firebase.getString("/Manual/forward/");

    }
    String s_s = Firebase.getString("/Manual/back/");
    while (s_s == "1") {
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, LOW);
      s_s = Firebase.getString("/Manual/back/");

    }
    String s_p = Firebase.getString("/Manual/pump/");
    while (s_p == "1") {
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      s_p = Firebase.getString("/Manual/pump/");
    }
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    s_m = Firebase.getString("/Manual/switch/");
    delayMicroseconds(200);
    if (s_m != "1") {
      mySerial.begin(9600);
    }
  }
  // end Manual
  ///////////////////////////////////////////////////

  if (Firebase.failed()) {
    Serial.print("set /number failed:");
    Serial.println(Firebase.error());
    return;
  }

  //status and history//
  String start = Firebase.getString("Start/start");
  int x = start.toInt();
  while (mySerial.available()) {
    s_work = mySerial.readString();
    Firebase.setString("Start/status", s_work);
    if (s_work == "1") {
      history_day1();
      history_hf();
    }

    if (s_work == "0") {
      history_ts();
    }
  }
  // end status and history//

  // Start when click
  if (x == 1) {
    my_Serial();
    Firebase.setString("Start/start", "0");
    return;
  }

  // Switch input humidity and time and day//
  sw_h = Firebase.getString("/Set_switch/switch_humidity/");
  sw_t = Firebase.getString("/Set_switch/switch_temperrature/");
  sw_morning = Firebase.getString("/Set_switch/switch_morning/");
  sw_evening = Firebase.getString("/Set_switch/switch_evening/");



  // Humidity work//

  if (sw_h == "\"on\"") {
    String set_h1 = Firebase.getString("/Set_Temperrature_Humidity/set_humidity/");
    String sub_h1 = set_h1.substring(1, set_h1.length() - 1);
    float set_h = sub_h1.toFloat();
    if (set_h >=  h) {
      my_Serial();
    }
  }
  if (sw_t == "\"on\"") {
    String set_t1 = Firebase.getString("/Set_Temperrature_Humidity/set_temperrature/");
    String sub_t1 = set_t1.substring(1, set_t1.length() - 1);
    float set_t = sub_t1.toFloat();
    if (set_t <= t) {
      my_Serial();
    }
  }
  // Day work//
  //__________________________________________________________________________________________________________________
  //Monday//
  if (day == "Mon") {
    String sw_mon = Firebase.getString("/Set_switch/switch_monday/");
    if (sw_mon == "\"on\"" && sw_h != "\"on\"" && sw_t != "\"on\"") {
      tm_te();
      sw_morning_evening();
    }
    if (sw_mon == "\"on\"" && sw_h == "\"on\"") {
      tm_te();
      check_sw_day_sw_h();
    }
    if (sw_mon == "\"on\"" && sw_t == "\"on\"") {
      tm_te();
      check_sw_day_sw_t();
    }
    if (sw_mon == "\"on\"" && sw_morning != "\"on\"" && sw_evening != "\"on\"" && sw_h == "\"on\"") {
      check_allDay_h();
    }
    if (sw_mon == "\"on\"" && sw_morning != "\"on\"" && sw_evening != "\"on\"" && sw_t == "\"on\"") {
      check_allDay_t();
    }
  }
  //__________________________________________________________________________________________________________________
  if (day == "Tue") {
    String sw_tue = Firebase.getString("/Set_switch/switch_tuesday/");
    if (sw_tue == "\"on\"" && sw_h != "\"on\"" && sw_t != "\"on\"") {
      tm_te();
      sw_morning_evening();
    }
    if (sw_tue == "\"on\"" && sw_h == "\"on\"") {
      tm_te();
      check_sw_day_sw_h();
    }
    if (sw_tue == "\"on\"" && sw_t == "\"on\"") {
      tm_te();
      check_sw_day_sw_t();
    }
    if (sw_tue == "\"on\"" && sw_morning != "\"on\"" && sw_evening != "\"on\"" && sw_h == "\"on\"") {
      check_allDay_h();
    }
    if (sw_tue == "\"on\"" && sw_morning != "\"on\"" && sw_evening != "\"on\"" && sw_t == "\"on\"") {
      check_allDay_t();
    }
  }
  //__________________________________________________________________________________________________________________
  if (day == "Wed") {
    String sw_wed = Firebase.getString("/Set_switch/switch_wednesday/");
    if (sw_wed == "\"on\"" && sw_h != "\"on\"" && sw_t != "\"on\"") {
      tm_te();
      sw_morning_evening();
    }
    if (sw_wed == "\"on\"" && sw_h == "\"on\"") {
      tm_te();
      check_sw_day_sw_h();
    }
    if (sw_wed == "\"on\"" && sw_t == "\"on\"") {
      tm_te();
      check_sw_day_sw_t();
    }
    if (sw_wed == "\"on\"" && sw_morning != "\"on\"" && sw_evening != "\"on\"" && sw_h == "\"on\"") {
      check_allDay_h();
    }
    if (sw_wed == "\"on\"" && sw_morning != "\"on\"" && sw_evening != "\"on\"" && sw_t == "\"on\"") {
      check_allDay_t();
    }
  }
  //__________________________________________________________________________________________________________________
  if (day == "Thu") {
    String sw_thu = Firebase.getString("/Set_switch/switch_thursday/");
    if (sw_thu == "\"on\"" && sw_h != "\"on\"" && sw_t != "\"on\"") {
      tm_te();
      sw_morning_evening();
    }
    if (sw_thu == "\"on\"" && sw_h == "\"on\"") {
      tm_te();
      check_sw_day_sw_h();
    }
    if (sw_thu == "\"on\"" && sw_t == "\"on\"") {
      tm_te();
      check_sw_day_sw_t();
    }
    if (sw_thu == "\"on\"" && sw_morning != "\"on\"" && sw_evening != "\"on\"" && sw_h == "\"on\"") {
      check_allDay_h();
    }
    if (sw_thu == "\"on\"" && sw_morning != "\"on\"" && sw_evening != "\"on\"" && sw_t == "\"on\"") {
      check_allDay_t();
    }
  }
  //__________________________________________________________________________________________________________________
  if (day == "Fri") {
    String sw_fri = Firebase.getString("/Set_switch/switch_friday/");
    if (sw_fri == "\"on\"" && sw_h != "\"on\"" && sw_t != "\"on\"") {
      tm_te();
      sw_morning_evening();
    }
    if (sw_fri == "\"on\"" && sw_h == "\"on\"") {
      tm_te();
      check_sw_day_sw_h();
    }
    if (sw_fri == "\"on\"" && sw_t == "\"on\"") {
      tm_te();
      check_sw_day_sw_t();
    }
    if (sw_fri == "\"on\"" && sw_morning != "\"on\"" && sw_evening != "\"on\"" && sw_h == "\"on\"") {
      check_allDay_h();
    }
    if (sw_fri == "\"on\"" && sw_morning != "\"on\"" && sw_evening != "\"on\"" && sw_t == "\"on\"") {
      check_allDay_t();
    }
  }
  //__________________________________________________________________________________________________________________
  if (day == "Sat") {
    String sw_sat = Firebase.getString("/Set_switch/switch_saturday/");
    if (sw_sat == "\"on\"" && sw_h != "\"on\"" && sw_t != "\"on\"") {
      tm_te();
      sw_morning_evening();
    }
    if (sw_sat == "\"on\"" && sw_h == "\"on\"") {
      tm_te();
      check_sw_day_sw_h();
    }
    if (sw_sat == "\"on\"" && sw_t == "\"on\"") {
      tm_te();
      check_sw_day_sw_t();
    }
    if (sw_sat == "\"on\"" && sw_morning != "\"on\"" && sw_evening != "\"on\"" && sw_h == "\"on\"") {
      check_allDay_h();
    }
    if (sw_sat == "\"on\"" && sw_morning != "\"on\"" && sw_evening != "\"on\"" && sw_t == "\"on\"") {
      check_allDay_t();
    }
  }
  //__________________________________________________________________________________________________________________
  if (day == "Sun") {
    String sw_sun = Firebase.getString("/Set_switch/switch_sunday/");
    if (sw_sun == "\"on\"" && sw_h != "\"on\"" && sw_t != "\"on\"") {
      tm_te();
      sw_morning_evening();
    }
    if (sw_sun == "\"on\"" && sw_h == "\"on\"") {
      tm_te();
      check_sw_day_sw_h();
    }
    if (sw_sun == "\"on\"" && sw_t == "\"on\"") {
      tm_te();
      check_sw_day_sw_t();
    }
    if (sw_sun == "\"on\"" && sw_morning != "\"on\"" && sw_evening != "\"on\"" && sw_h == "\"on\"") {
      check_allDay_h();
    }
    if (sw_sun == "\"on\"" && sw_morning != "\"on\"" && sw_evening != "\"on\"" && sw_t == "\"on\"") {
      check_allDay_t();
    }
  }
  //__________________________________________________________________________________________________________________
  //Clear t_sec
  if ((time_current != time_tm) && (time_current != time_te)) {
    t_sec = 1;
  }
  //__________________________________________________________________________________________________________________
}

void my_Serial() {
  String water = Firebase.getString("/Time_water/Time_water/");
  String pump = Firebase.getString("/Time_water/Time_pump/");
  String water_1 = water.substring(1, water.length() - 1);
  String pump1 = pump.substring(1, pump.length() - 1);
  String a = "q" "#" + water_1 + "#" + pump1;
  mySerial.println(a);
}

void tem_hu() {
  Wire.beginTransmission(PCF8591);
  Wire.write(0x04);
  Wire.endTransmission();
  Wire.requestFrom(PCF8591, 5);

  adcvalue0 = Wire.read();
  adcvalue0 = Wire.read();
  adcvalue1 = Wire.read();
  adcvalue2 = Wire.read();
  h = (adcvalue0 + adcvalue1 + adcvalue2) / 3;


  Wire.beginTransmission(PCF8591);
  Wire.write(0x40);
  Wire.write(adcvalue0);
  Wire.endTransmission();

  t = dht.readTemperature();
  if (isnan(t)) {
    Firebase.setString("/temperrature/temperrature/", "0" );
    //delay(500);
  }
  t_h_his1 = String(h);
  t_h_his2 = String(t);
  t_h_his = "\"\\\"" + t_h_his1 + "°" + "  " + t_h_his2 + "%\"" + "\"\\\"";
  Firebase.setFloat("/humidity/humidity/", h);
  Firebase.setFloat("/temperrature/temperrature/", t);
}

//__________________________________________________________________________________________________________________
//Time moring & evening
void tm_te() {
  String set_time_morning = Firebase.getString("/Time_setting/Time_morning/");
  String sub_tm = set_time_morning.substring(1, set_time_morning.length() - 1);
  time_tm = sub_tm.toInt();

  String set_time_evening = Firebase.getString("/Time_setting/Time_evening/");
  String sub_te = set_time_evening.substring(1, set_time_evening.length() - 1);
  time_te = sub_te.toInt();
}

