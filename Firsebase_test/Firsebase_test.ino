//gominCG

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <DHT.h>


#include <SoftwareSerial.h>
SoftwareSerial mySerial(D1, D2); //rx tx
// Config Firebase
#define FIREBASE_HOST "smartfarm-cg.firebaseio.com"
#define FIREBASE_AUTH "j6sQithe5Hf9xLtMK6y4wYx1kyxfa5TaYT1oP9gz"

// Config connect WiFi
#define WIFI_SSID "CG Academy Club"
#define WIFI_PASSWORD "cg24992399"

#define LED_PIN D0
#define DHTTYPE DHT22
#define DHTPIN D5
DHT dht(DHTPIN, DHTTYPE);
float h;   //readHumidity;
float t;  //readTemperature;
int t_sec = 1;
void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);

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
  //read humidity_tempperrature//

  h = dht.readHumidity();
  t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    Firebase.setString("/humidity/humidity/", "Error" );
    Firebase.setString("/temperrature/temperrature/", "Error" );
    delay(500);
    return;
  }
    Firebase.setFloat("/humidity/humidity/", h);
    Firebase.setFloat("/temperrature/temperrature/", t);
  
  if (Firebase.failed()) {
    Serial.print("set /number failed:");
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
    Serial.println(Firebase.error());
    return;
  }
  String start = Firebase.getString("Start/start");
  int x = start.toInt();
  if (x == 1) {
    my_Serial();
    Firebase.setString("Start/start", "0");
    return;
  }

  //Day and Time//
  String day_time = Day();
  String day = day_time.substring(0, 3);
  Firebase.setString("Date_Time_Current/day", day);
  String hour = day_time.substring(11, 13);
  Firebase.setString("Date_Time_Current/hour", hour);
  String minute = day_time.substring(14, 16);
  Firebase.setString("Date_Time_Current/minute", minute);
  String eq_time = hour + minute;
  int time_current = eq_time.toInt();


  // Switch input humidity and time and day//
  String sw_h = Firebase.getString("/Set_switch/switch_humidity/");
  String sw_t = Firebase.getString("/Set_switch/switch_temperrature/");

  String sw_morning = Firebase.getString("/Set_switch/switch_morning/");
  String sw_evening = Firebase.getString("/Set_switch/switch_evening/");

  String set_h1 = Firebase.getString("/Set_Temperrature_Humidity/set_humidity/");
  String sub_h1 = set_h1.substring(0, 5);
  float set_h = sub_h1.toFloat();

  String set_t1 = Firebase.getString("/Set_Temperrature_Humidity/set_temperrature/");
  String sub_t1 = set_t1.substring(0, 5);
  float set_t = sub_t1.toFloat();

  String set_time_morning = Firebase.getString("/Time_setting/Time_morning/");
  String sub_tm = set_time_morning.substring(1, set_time_morning.length() - 1);
  int time_tm = sub_tm.toInt();

  String set_time_evening = Firebase.getString("/Time_setting/Time_evening/");
  String sub_te = set_time_evening.substring(1, set_time_evening.length() - 1);
  int time_te = sub_te.toInt();


  // Humidity work//

  if (sw_h == "\"on\"") {
    if (set_h >=  h) {
      my_Serial();
    }
  }
  if (sw_t == "\"on\"") {
    if (set_t <= t) {
      my_Serial();
    }
  }
  // Day work//
  //__________________________________________________________________________________________________________________
  //Monday//
  if (day == "Mon") {
    String sw_mon = Firebase.getString("/Set_switch/switch_monday/");

    if (sw_mon == "\"on\"") {

      if ( sw_morning == "\"on\"" && time_current == time_tm ) {
        if (t_sec == 1) {
          my_Serial();
          t_sec = 0;
        }
      }

      if ( sw_evening == "\"on\"" && time_current == time_te) {
        if (t_sec == 1) {
          my_Serial();
          t_sec = 0;
        }
      }
    }
  }
  //__________________________________________________________________________________________________________________
  if (day == "Tue") {
    String sw_tue = Firebase.getString("/Set_switch/switch_tuesday/");

    if (sw_tue == "\"on\"") {

      if (sw_morning == "\"on\"" && time_current == time_tm) {
        if (t_sec == 1) {
          my_Serial();
          t_sec = 0;
        }
      }
      if ( sw_evening == "\"on\"" && time_current == time_te) {
        if (t_sec == 1) {
          my_Serial();
          t_sec = 0;
        }
      }
    }
  }
  //__________________________________________________________________________________________________________________
  if (day == "Wed") {
    String sw_wed = Firebase.getString("/Set_switch/switch_wednesday/");

    if (sw_wed == "\"on\"") {

      if (sw_morning == "\"on\"" && time_current == time_tm) {
        if (t_sec == 1) {
          my_Serial();
          t_sec = 0;
        }
      }
      if (sw_evening == "\"on\"" && time_current == time_te) {
        if (t_sec == 1) {
          my_Serial();
          t_sec = 0;
        }
      }
    }
  }
  //__________________________________________________________________________________________________________________
  if (day == "Thu") {
    String sw_thu = Firebase.getString("/Set_switch/switch_thursday/");

    if (sw_thu == "\"on\"") {

      if (sw_morning == "\"on\"" && time_current == time_tm) {
        if (t_sec == 1) {
          my_Serial();
          t_sec = 0;
        }
      }
      if (sw_evening == "\"on\"" && time_current == time_te) {
        if (t_sec == 1) {
          my_Serial();
          t_sec = 0;
        }
      }
    }
  }
  //__________________________________________________________________________________________________________________
  if (day == "Fri") {
    String sw_fri = Firebase.getString("/Set_switch/switch_friday/");

    if (sw_fri == "\"on\"") {


      if (sw_morning == "\"on\"" && time_current == time_tm) {
        if (t_sec == 1) {
          my_Serial();
          t_sec = 0;
        }
      }
      if (sw_evening == "\"on\"" && time_current == time_te) {
        if (t_sec == 1) {
          my_Serial();
          t_sec = 0;
        }
      }
    }
  }
  //__________________________________________________________________________________________________________________
  if (day == "Sat") {
    String sw_sat = Firebase.getString("/Set_switch/switch_saturday/");

    if (sw_sat == "\"on\"") {

      if (sw_morning == "\"on\"" && time_current == time_tm) {
        if (t_sec == 1) {
          my_Serial();
          t_sec = 0;
        }
      }
      if (sw_evening == "\"on\"" && time_current == time_te) {
        if (t_sec == 1) {
          my_Serial();
          t_sec = 0;
        }
      }
    }
  }
  //__________________________________________________________________________________________________________________
  if (day == "Sun") {
    String sw_sun = Firebase.getString("/Set_switch/switch_sunday/");

    if (sw_sun == "\"on\"") {

      if (sw_morning == "\"on\"" && time_current == time_tm  ) {
        if (t_sec == 1) {
          my_Serial();
          t_sec = 0;
        }

      }
      if (sw_evening == "\"on\"" && time_current == time_te) {
        if (t_sec == 1) {
          my_Serial();
          t_sec = 0;
        }
      }
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
  String water_1 = water.substring(1, water.length() - 1);
  String a = "q" + water_1;
  mySerial.println(a);
}

