#include "date.h"
#include <stdio.h>

/**
 * @brief Checks if a year is a leap year.
 *
 * @param year The year to check.
 * @return 1 if the year is a leap year, 0 otherwise.
 */
int leapYear(int year) {
  if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
    return 1;
  } else {
    return 0;
  }
}

/**
 * @brief Prints a date in the format DD-MM-YYYY.
 *
 * @param date Date to print.
 */
void printDate(Date date) {
  printf("%02d-%02d-%02d\n", date.day, date.month, date.year);
}

/**
 * @brief Compares two dates.
 *
 * @param d1 The first date.
 * @param d2 The second date.
 * @return A negative value if d1 is earlier than d2, 0 if they are the same,
 * and a positive value if d1 is later than d2.
 */
int compareDates(Date d1, Date d2) {
  if (d1.year != d2.year)
    return d1.year - d2.year;
  else if (d1.month != d2.month)
    return d1.month - d2.month;
  return d1.day - d2.day;
}

/**
 * @brief Validates a date.
 *
 * @param date The date to validate.
 * @return 1 if the date is valid, 0 otherwise.
 */
int validDate(Date date) {
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

/**
 * @brief Validates a date against the system's current date.
 *
 * @param date Date to validate.
 * @param sys Pointer to the system structure.
 * @param pt Language flag (0 for Portuguese, 1 for English).
 * @return int 1 if the date is valid, 0 otherwise.
 */
int validateDate(Date date, Date currentDate, int pt) {
  if (compareDates(currentDate, date) < 0 || !validDate(date)) {
    puts(pt ? EINVDATE : DATAINV);
    return 0;
  }
  return 1;
}
