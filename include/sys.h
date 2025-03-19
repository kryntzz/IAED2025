#ifndef SYS_H
#define SYS_H
#include "config.h"
#include "date.h"
#include "inoculation.h"
#include "vaccine.h"

/** all state information stored by the system */
typedef struct {
  Date currentDate;       /** current date          */
  int count;              /** number of vaccines    */
  Vaccine data[MAXBATCH]; /** vaccine information   */
  Node *data2;
  Node *tail;
  hashMap *map;
} Sys;

#endif // !SYS_H
