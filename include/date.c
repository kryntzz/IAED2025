/*
 * Projecto de IAED2025
 * @file date.c
 * @author ist1113637 (Simão Lavos)
 */

#include "date.h"
#include <stdio.h>

int leapYear(int year) {
  if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
    return 1;
  } else {
    return 0;
  }
}

void printDate(Date date) {
  printf("%02d-%02d-%02d\n", date.day, date.month, date.year);
}

int compareDates(Date d1, Date d2) {
  if (d1.year != d2.year)
    return d1.year - d2.year;

  else if (d1.month != d2.month)
    return d1.month - d2.month;

  return d1.day - d2.day;
}

int validDate(Date date) {

  //  monthDay is an array with the number of day
  //  for each month
  int monthDay[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (leapYear(date.year)) {
    monthDay[1] = 29;
  }
  if (date.day > monthDay[date.month - 1] || date.day <= 0 || date.month <= 0 ||
      date.month > 12) {
    return 0;
  }
  return 1;
}

int validateDate(Date date, Date currentDate, int pt) {
  if (compareDates(currentDate, date) < 0 || !validDate(date)) {
    puts(pt ? EINVDATE : DATAINV);
    return 0;
  }
  return 1;
}
