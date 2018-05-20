void sw_morning_evening() {                                       //check sw_morning & sw_evening
  if ( sw_morning == "\"on\"" && time_current == time_tm ) {
    if (t_sec == 1) {
      my_Serial();
      //Serial.println("working");
      t_sec = 0;
    }
  }
  if ( sw_evening == "\"on\"" && time_current == time_te) {
    if (t_sec == 1) {
      my_Serial();
      // Serial.println("working");
      t_sec = 0;
    }
  }
}

void check_sw_day_sw_h() {                                                              //check witch hu && time
  String set_h1 = Firebase.getString("/Set_Temperrature_Humidity/set_humidity/");
  String sub_h1 = set_h1.substring(1, set_h1.length() - 1);
  float set_h = sub_h1.toFloat();
  if (set_h >=  h && sw_morning == "\"on\"" && time_current == time_tm) {
    my_Serial();
    // Serial.println("working_sw_h morning");
  }
  if (set_h >=  h && sw_evening  == "\"on\"" && time_current == time_te) {
    my_Serial();
    //Serial.println("working_sw_h evening");
  }
}

void check_sw_day_sw_t() {                                                              //check witch tem && time
  String set_t1 = Firebase.getString("/Set_Temperrature_Humidity/set_temperrature/");
  String sub_t1 = set_t1.substring(1, set_t1.length() - 1);
  float set_t = sub_t1.toFloat();
  if (set_t <= t && sw_morning == "\"on\"" && time_current == time_tm) {
    my_Serial();
    // Serial.println("working_sw_t morning");
  }
  if (set_t <= t && sw_evening  == "\"on\"" && time_current == time_te) {
    my_Serial();
    // Serial.println("working_sw_t evening");
  }
}

void check_allDay_h() {                                                                   //check hu all day
  String set_h1 = Firebase.getString("/Set_Temperrature_Humidity/set_humidity/");
  String sub_h1 = set_h1.substring(1, set_h1.length() - 1);
  float set_h = sub_h1.toFloat();
  if (set_h >=  h) {
    my_Serial();
    //Serial.println("working all day hu");
  }
}

void check_allDay_t() {                                                                   //check tem all day
  String set_t1 = Firebase.getString("/Set_Temperrature_Humidity/set_temperrature/");
  String sub_t1 = set_t1.substring(1, set_t1.length() - 1);
  float set_t = sub_t1.toFloat();
  if (set_t <= t) {
    my_Serial();
    // Serial.println("working all day tem");
  }
}

