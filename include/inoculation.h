#ifndef INOCULATION_H
#define INOCULATION_H
#include "config.h"
#include "date.h"
#include "vaccine.h"


typedef struct {
  char *name;
  char batch[MAXBATCHCODE + 1];
  Date date;
  char vacName[MAXNAME];
} Inoculation;

typedef struct Node {
  Inoculation inoc;
  struct Node *next;
} Node;

typedef struct {
  int count, size;

  Node **arr;
} hashMap;

void displayInoc(Inoculation inoculation);
Node *createNewNode(const char *name, const char *batch, Date date,
                    const char *vacname);
void initializeHashMap(hashMap *map);
int hashFunc(hashMap *map, char *key);
void insertHash(hashMap *map, char *key, Inoculation inoc);
char *search(hashMap *map, char *key);
int isVaccinated(hashMap *map, char *name, char *vacName,Date date);
void freeHashMap(hashMap *map);

#endif // !INOCULATION_H
