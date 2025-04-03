#include "vaccine.h"
#include "batch.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Swaps the value of two vaccines.
 *
 * @param a Pointer to the first vaccine.
 * @param b Pointer to the second vaccine.
 */
void swap(Vaccine *a, Vaccine *b) {
  Vaccine temp = *a;

  *a = *b;
  *b = temp;
}

/**
 * @brief Checks if a name exists in the system.
 *
 * @param sys Pointer to the system structure.
 * @param name Name to check.
 * @return int 1 if the name exists, 0 otherwise.
 */

int nameExists(Vaccine *sys, char *name, int count) {
  for (int i = 0; i < count; i++) {

    if (!strcmp(name, sys[i].name)) {
      return 1;
    }
  }
  return 0;
}

/**
 * @brief Validates the input for creating a vaccine.
 *
 * @param input Input string containing the vaccine details.
 * @param pt Language flag (0 for Portuguese, 1 for English).
 * @return int 0 if the input is invalid, 1 otherwise.
 */
int validateVaccineInput(char *input, int pt) {
  char input2[BUFMAX];

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

/**
 * @brief Validates a name.
 *
 * @param name Name to validate.
 * @return int 0 if the name is invalid, 1 otherwise.
 */
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

/**
 * @brief Merges two subarrays of vaccines.
 *
 * @param arr Array of vaccines.
 * @param l Left index.
 * @param m Middle index.
 * @param r Right index.
 */
void merge(Vaccine arr[], int l, int m, int r) {
  int n1 = m - l + 1, n2 = r - m;

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
    i++, k++;
  }

  while (j < n2) {
    arr[k] = R[j];
    j++, k++;
  }
}

/**
 * @brief Sorts an array of vaccines using merge sort.
 *
 * @param arr Array of vaccines.
 * @param l Left index.
 * @param r Right index.
 */
void mergeSort(Vaccine arr[], int l, int r) {
  if (l < r) {
    int m = l + (r - l) / 2;

    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);

    merge(arr, l, m, r);
  }
}

/**
 * @brief Sorts an array of vaccines.
 *
 * @param vaccines Array of vaccines.
 * @param n Number of vaccines.
 */
void vaccineSort(Vaccine vaccines[], int n) { mergeSort(vaccines, 0, n - 1); }

/**
 * @brief Displays a vaccine.
 *
 * @param vaccine Vaccine to display.
 */
void dispayVaccine(Vaccine vaccine) {
  Date date = vaccine.date;
  printf("%s %s %02d-%02d-%02d %d %d", vaccine.name, vaccine.batch, date.day,
         date.month, date.year, vaccine.stock, vaccine.appDoses);
}

/**
 * @brief Extracts a name from the input string.
 *
 * @param input Pointer to the input string.
 * @param nameLen Pointer to store the length of the extracted name.
 * @return char* Pointer to the extracted name.
 */
char *extractName(char **input, unsigned long *nameLen) {
  char *start = strchr(*input, ' ') + 1, *name;
  *input = start;

  if (*start == '"') {
    start++;
    char *end = strchr(start, '"');
    *nameLen = end - start;
    name = malloc(*nameLen + 1);
    strncpy(name, start, *nameLen), name[*nameLen] = '\0';
    *input = end + 1;

  } else {
    char *end = strchr(start, ' ');
    *nameLen = end - start;
    name = malloc(*nameLen + 1);
    strncpy(name, start, *nameLen), name[*nameLen] = '\0';
    *input = end;
  }
  return name;
}

/**
 * @brief Finds a vaccine by name.
 *
 * @param sys Pointer to the system structure.
 * @param vacName Name of the vaccine to find.
 * @return Vaccine* Pointer to the found vaccine, or NULL if not found.
 */
Vaccine *findVaccine(Vaccine *sys, char *vacName, int count, Date date) {
  for (int i = 0; i < count; i++)

    if (!strcmp(vacName, sys[i].name) && validDate(sys[i].date) &&
        compareDates(date, sys[i].date) < 0 && sys[i].stock > 0)
      return &sys[i];

  return NULL;
}
