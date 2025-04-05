/*
 * Projecto de IAED2025
 * @file sys.h
 * @author ist1113637 (Simão Lavos)
 */

#ifndef SYS_H
#define SYS_H
#include "config.h"
#include "date.h"
#include "inoculation.h"
#include "vaccine.h"

/**
 * @brief Structure to represent everything stored.
 */
typedef struct {
  Date currentDate;       /** current date                             */
  int count;              /** number of vaccines                      */
  Vaccine data[MAXBATCH]; /** vaccine information                     */
  Node *data2;            /** pointer to the head of the linked list  */
  Node *tail;             /** pointer to the tail of the linked list  */
  hashMap *map;           /** pointer to the hasmap                   */
} Sys;

#endif // !SYS_H
