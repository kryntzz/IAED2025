#ifndef VACCINE_H
#define VACCINE_H
#include "config.h"
#include "date.h"

/** node for a linked list of vaccines*/
typedef struct {
  char name[MAXNAME];           /** vaccine name  */
  char batch[MAXBATCHCODE + 1]; /** vaccine batch */
  Date date;                    /** vaccine date  */
  int stock;                    /** vaccine's available doses */
  int appDoses;
} Vaccine;

void swap(Vaccine *a, Vaccine *b);
void merge(Vaccine arr[], int l, int m, int r);
void mergeSort(Vaccine arr[], int l, int r);
void vaccineSort(Vaccine vaccines[], int n);
void dispayVaccine(Vaccine vaccine);

#endif // !VACCINE_H
