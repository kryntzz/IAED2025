#include "vaccine.h"
#include "batch.h"
#include <stdio.h>

/** Swaps the value of two vaccines
 * @param vaccine1> first vaccine to swap
 * @param vaccine2> second vaccine to swap
 */
void swap(Vaccine *a, Vaccine *b) {
  Vaccine temp = *a;

  *a = *b;
  *b = temp;
}

void merge(Vaccine arr[], int l, int m, int r) {
  int n1 = m - l + 1;
  int n2 = r - m;

  Vaccine L[n1], R[n2];

  for (int i = 0; i < n1; i++)
    L[i] = arr[l + i];
  for (int j = 0; j < n2; j++)
    R[j] = arr[m + 1 + j];

  int i = 0, j = 0, k = l;
  while (i < n1 && j < n2) {
    if (compareDates(L[i].date, R[j].date) < 0 ||
        (compareDates(L[i].date, R[j].date) == 0 &&
         comparebatch(L[i].batch, R[j].batch) < 0)) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = R[j];
    j++;
    k++;
  }
}

void mergeSort(Vaccine arr[], int l, int r) {
  if (l < r) {
    int m = l + (r - l) / 2;

    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);

    merge(arr, l, m, r);
  }
}

void vaccineSort(Vaccine vaccines[], int n) { mergeSort(vaccines, 0, n - 1); }

void dispayVaccine(Vaccine vaccine) {
  Date date = vaccine.date;
  printf("%s %s %02d-%02d-%02d %d %d", vaccine.name, vaccine.batch, date.day,
         date.month, date.year, vaccine.stock, vaccine.appDoses);
}
