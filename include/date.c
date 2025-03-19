#include "date.h"

int leapYear(int year) {
  if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
    return 1;
  } else {
    return 0;
  }
}

int compareDates(Date d1, Date d2) {

  if (d1.year != d2.year)
    return d1.year - d2.year;

  else if (d1.month != d2.month)
    return d1.month - d2.month;

  return d1.day - d2.day;
}

int validDate(Date date) {

  int monthDay[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (leapYear(date.year)) {
    monthDay[1] = 29;
  }
  if (date.day > monthDay[date.month - 1] || date.day <= 0 || date.month <= 0 ||
      date.month > 12) {
    return 1;
  }

  return 0;
}
