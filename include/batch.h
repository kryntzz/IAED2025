/*
 * Projecto de IAED2025
 * @file all.h
 * @author ist1113637 (Simão Lavos)
 */

#ifndef BATCH_H
#define BATCH_H
#include "config.h"
#include "sys.h"

/**
 * @brief Compares two batches.
 *
 * @param b1 First batch to compare.
 * @param b2 Second batch to compare.
 * @return int 0 if the batches are equal, a positive number if b1 is greater
 * than b2, and a negative number if b1 is less than b2.
 */
int comparebatch(char b1[MAXBATCHCODE], char b2[MAXBATCHCODE]);

/**
 * @brief Checks if a batch exists in the system.
 *
 * @param sys Pointer to the system structure.
 * @param batch Batch code to check.
 * @return int 1 if the batch exists, 0 otherwise.
 */
int batchExists(Sys *sys, char batch[MAXBATCHCODE]);

/**
 * @brief Validates a batch code.
 *
 * @param batch Batch code to validate.
 * @return int 1 if the batch code is invalid, 0 otherwise.
 */
int validBatch(char batch[MAXBATCHCODE]);

#endif // !BATCH_H
