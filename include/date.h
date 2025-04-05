/*
 * Projecto de IAED2025
 * @file date.h
 * @author ist1113637 (Simão Lavos)
 */

#ifndef DATE_H
#define DATE_H
#include "config.h"

/**
 * @brief Structure to represent a date.
 */
typedef struct {
  int day;   /**  Day of the month   */
  int month; /**  Month of the year  */
  int year;  /**  Year               */
} Date;

/**
 * @brief Checks if a year is a leap year.
 *
 * @param year The year to check.
 * @return 1 if the year is a leap year, 0 otherwise.
 */
int leapYear(int year);

/**
 * @brief Prints a date in the format DD-MM-YYYY.
 *
 * @param date Date to print.
 */
void printDate(Date date);

/**
 * @brief Compares two dates.
 *
 * @param d1 The first date.
 * @param d2 The second date.
 * @return A negative value if d1 is earlier than d2, 0 if they are the same,
 * and a positive value if d1 is later than d2.
 */
int compareDates(Date d1, Date d2);

/**
 * @brief Validates a date.
 *
 * @param date The date to validate.
 * @return 1 if the date is valid, 0 otherwise.
 */
int validDate(Date date);

/**
 * @brief Validates a date for a specific case.
 *
 * @param date Date to validate.
 * @param sys Pointer to the system structure.
 * @param pt Language flag (0 for Portuguese, 1 for English).
 * @return int 1 if the date is valid, 0 otherwise.
 */
int validateDate(Date date, Date currentDate, int pt);

#endif // DATE_H
