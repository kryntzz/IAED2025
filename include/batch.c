#include "batch.h"
#include <string.h>

/**
 * @brief Compares two batches.
 *
 * @param b1 First batch to compare.
 * @param b2 Second batch to compare.
 * @return int 0 if the batches are equal, a positive number if b1 is greater
 * than b2, and a negative number if b1 is less than b2.
 */
int comparebatch(char b1[MAXBATCHCODE], char b2[MAXBATCHCODE]) {
  int len = strlen(b1);
  for (int i = 0; i < len; i++) {
    int c1 = b1[i];
    int c2 = b2[i];
    if (c1 != c2)
      return c1 - c2;
  }
  return 0;
}

/**
 * @brief Checks if a batch exists in the system.
 *
 * @param sys Pointer to the system structure.
 * @param batch Batch code to check.
 * @return int 0 if the batch exists, 1 otherwise.
 */
int batchExists(Sys *sys, char batch[MAXBATCHCODE]) {
  for (int i = 0; i < sys->count; i++) {

    if (!strcmp(batch, sys->data[i].batch))
      return 0;
  }
  return 1;
}

/**
 * @brief Validates a batch code.
 *
 * @param batch Batch code to validate.
 * @return int 0 if the batch code is invalid, 1 otherwise.
 */
int validBatch(char batch[MAXBATCHCODE]) {
  int len = strlen(batch);

  if (len > MAXBATCHCODE)
    return 0;

  for (int i = 0; i < len; i++) {
    char c = batch[i];

    if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F')))
      return 0;
  }
  return 1;
}
