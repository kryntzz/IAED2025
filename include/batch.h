#ifndef BATCH_H
#define BATCH_H
#include "config.h"
#include "sys.h"

int comparebatch(char b1[MAXBATCHCODE], char b2[MAXBATCHCODE]);
int batchExists(Sys *sys, char batch[MAXBATCHCODE]);
int validBatch(char batch[MAXBATCHCODE]);

#endif // !BATCH_H
