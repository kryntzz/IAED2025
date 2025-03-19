#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inoculation.h"
#include "date.h"

void displayInoc(Inoculation inoculation) {
  Date date = inoculation.date;
  printf("%s %s %02d-%02d-%02d\n", inoculation.name, inoculation.batch,
         date.day, date.month, date.year);
}

Node *createNewNode(const char *name, const char *batch, Date date,
                    const char *vacname) {
  Node *newNode = malloc(sizeof(Node));

  newNode->inoc.name = (char *)malloc(strlen(name) + 1);
  strcpy(newNode->inoc.name, name);
  strncpy(newNode->inoc.batch, batch, MAXBATCHCODE);
  newNode->inoc.batch[MAXBATCHCODE] = '\0';
  newNode->inoc.date = date;
  strcpy(newNode->inoc.vacName, vacname);

  newNode->next = NULL;
  return newNode;
}

void initializeHashMap(hashMap *map) {

  map->size = 100;
  map->count = 0;

  map->arr = (Node **)malloc(sizeof(Node *) * map->size);

  for(int i = 0; i < map->size; i++) {
    map->arr[i] = NULL;
  }

  return;
}

int hashFunc(hashMap *map, char *key) {
  unsigned int hash = 0;
  while (*key) {
    hash =
        (hash * 31) + *key; // 31 is a prime number often used in hash functions
    key++;
  }
  return hash % map->size;
}

void insertHash(hashMap *map, char *key, Inoculation inoc) {
  int index = hashFunc(map, key);

  Node *newNode = createNewNode(inoc.name, inoc.batch, inoc.date, inoc.vacName);

  if (map->arr[index] == NULL) {
    map->arr[index] = newNode;
  } else {
    Node *current = map->arr[index];
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = newNode;
  }
  return;
}

int isVaccinated(hashMap *map, char *name, char *vacName, Date date) {
  int index = hashFunc(map, name);

  Node *head = map->arr[index];
  while (head != NULL) {

    if (strcmp(head->inoc.name, name) == 0 && strcmp(head->inoc.vacName, vacName) == 0 && compareDates(head->inoc.date, date)==0) {
      return 1; // Already vaccinated
    }
    head = head->next;
  }
  return 0; // Not vaccinated
}
void freeHashMap(hashMap *map) {
  for (int i = 0; i < map->size; i++) {
    Node *current = map->arr[i];
    while (current != NULL) {
      Node *temp = current;
      current = current->next;
      free(temp->inoc.name);
      free(temp);
    }
  }
  free(map->arr);
  free(map);
}