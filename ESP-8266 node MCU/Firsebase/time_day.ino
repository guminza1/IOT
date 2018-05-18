#include <time.h>
String Day() {
  int timezone = 7 * 3600;                    //Time zone Thailand
  int dst = 0;                                // Date Swing Time
  configTime(timezone, dst, "pool.ntp.org", "time.nist.gov");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(100);
  }
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
  ctime(&now);
  char *a[] = {ctime(&now)};
  String i = String(i + *a);
  num_day = p_tm->tm_mday;

  return i;
}

