/*
 * Projecto de IAED2025
 * @file batch.c
 * @author ist1113637 (Simão Lavos)
 */

#include "batch.h"
#include <string.h>

int comparebatch(char b1[MAXBATCHCODE], char b2[MAXBATCHCODE]) {

  for (int i = 0; i < MAXBATCHCODE; i++) {
    int c1 = b1[i];
    int c2 = b2[i];
    if (c1 != c2)
      return c1 - c2;
  }
  return 0;
}

int batchExists(Sys *sys, char batch[MAXBATCHCODE]) {
  //Goes through all the batches stored
  for (int i = 0; i < sys->count; i++) {

    if (!strcmp(batch, sys->data[i].batch))
      return 0;
  }
  return 1;
}

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
