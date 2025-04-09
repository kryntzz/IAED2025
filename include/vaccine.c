/*
 * Projecto de IAED2025
 * @file vaccine.c
 * @author ist1113637 (Simão Lavos)
 */

#include "vaccine.h"
#include "batch.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nameExists(Vaccine *sys, char *name, int count) {
  // Iterates through all the vaccines
  for (int i = 0; i < count; i++) {

    // Compares the name
    if (!strcmp(name, sys[i].name)) {
      return 1;
    }
  }
  return 0;
}

int validateVaccineInput(char *input, int pt) {
  char input2[BUFMAX];

  // Creates a copy of the input because strtok
  // changes it, then it gets the word by searching
  // for the ' ' at the end of the name
  strcpy(input2, input);
  char *token = strtok(input2, " ");
  token = strtok(NULL, " ");

  if (strlen(token) > MAXBATCHCODE) {
    puts(pt ? EINVBATCH : LOTEINV);
    return 0;
  }

  token = strtok(NULL, " ");
  token = strtok(NULL, " ");
  token = strtok(NULL, " ");

  if (strlen(token) > MAXNAME) {
    puts(pt ? EINVNAME : NOMEINV);
    return 0;
  }

  return 1;
}

int validName(char name[MAXNAME]) {
  int len = strlen(name);

  if (len > MAXNAME) {
    return 0;
  }
  for (int i = 0; i < len; i++) {
    char c = name[i];

    if (c == ' ' || c == '\n' || c == '\t') {
      return 0;
    }
  }
  return 1;
}

void merge(Vaccine arr[], int l, int m, int r) {
  int n1 = m - l + 1, n2 = r - m;

  Vaccine L[n1], R[n2];

  // Iterates through the left part of the array
  for (int i = 0; i < n1; i++)
    L[i] = arr[l + i];

  // Iterates through the right part of the array
  for (int j = 0; j < n2; j++)
    R[j] = arr[m + 1 + j];

  int i = 0, j = 0, k = l;

  // Compares the dates and swaps them when needed
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

  // Finishes goint through the array, adding it to the right part
  while (i < n1) {
    arr[k] = L[i];
    i++, k++;
  }

  //  Finishes goint through the array, adding it to the left part
  while (j < n2) {
    arr[k] = R[j];
    j++, k++;
  }
}

void mergeSort(Vaccine arr[], int l, int r) {
  if (l < r) {
    int m = l + (r - l) / 2;

    // Recursively goes to through the right part of the array
    //  and the left part of the array
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

char *extractName(char **input, unsigned long *nameLen) {
  char *start = strchr(*input, ' ') + 1, *name;
  *input = start;

  // Checks if the name is between quotes
  if (*start == '"') {
    start++;
    char *end = strchr(start, '"');
    *nameLen = end - start;
    name = malloc(*nameLen + 1);
    strncpy(name, start, *nameLen), name[*nameLen] = '\0';
    *input = end + 1;

    // If the name isn't between quotes
  } else {
    char *end = strchr(start, ' ');
    *nameLen = end - start;
    name = malloc(*nameLen + 1);
    strncpy(name, start, *nameLen), name[*nameLen] = '\0';
    *input = end;
  }
  return name;
}

Vaccine *findVaccine(Vaccine *sys, char *vacName, int count, Date date) {

  for (int i = 0; i < count; i++)

    if (!strcmp(vacName, sys[i].name) && validDate(sys[i].date) &&
        compareDates(date, sys[i].date) < 0 && sys[i].stock > 0)
      return &sys[i];

  return NULL;
}
