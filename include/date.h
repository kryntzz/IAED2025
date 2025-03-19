#ifndef DATE_H
#define DATE_H

typedef struct {
  int day, month, year;
} Date;

int leapYear(int year);
int compareDates(Date d1, Date d2);
int validDate(Date date);

#endif // DATE_H
