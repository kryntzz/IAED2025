/*
 * Projecto de IAED2025
 * @file inoculation.c
 * @author ist1113637 (Simão Lavos)
 */

#include "inoculation.h"
#include "date.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void freeSystem(Node **head) {
  Node *current = *head;

  //  Goes through all the linked list
  //  freeing each node in the way
  while (current != NULL) {

    Node *aux = current;
    current = current->next;
    free(aux->inoc.name);
    free(aux);
  }
  *head = NULL;
}

void displayInoc(Inoculation inoculation) {
  Date date = inoculation.date;

  printf("%s %s %02d-%02d-%02d\n", inoculation.name, inoculation.batch,
         date.day, date.month, date.year);
}

Node *createNewNode(const char *name, const char *batch, Date date,
                    const char *vacname) {
  // Allocate memory for the new node
  Node *newNode = malloc(sizeof(Node));

  // Allocate memory for the name and copy it
  newNode->inoc.name = (char *)malloc(strlen(name) + 1);
  strcpy(newNode->inoc.name, name);

  // Copy the batch code and ensure null termination
  strncpy(newNode->inoc.batch, batch, MAXBATCHCODE);
  newNode->inoc.batch[MAXBATCHCODE] = '\0';

  // Assign the date and vaccine name
  newNode->inoc.date = date;
  strcpy(newNode->inoc.vacName, vacname);

  // Initialize the next pointer to NULL
  newNode->next = NULL;

  return newNode;
}

void initializeHashMap(hashMap *map) {
  // Set the initial size and count of the hash map
  map->size = 100;
  map->count = 0;

  // Allocate memory for the array of node pointers
  map->arr = (Node **)malloc(sizeof(Node *) * map->size);

  // Initialize all array elements to NULL
  for (int i = 0; i < map->size; i++) {
    map->arr[i] = NULL;
  }

  return;
}

int hashFunc(hashMap *map, char *key) {
  unsigned int hash = 0;
  // Compute the hash value using a prime multiplier
  while (*key) {
    hash = (hash * 31) + *key;
    key++;
  }
  // Return the index within the bounds of the hash map size
  return hash % map->size;
}

void insertHash(hashMap *map, char *key, Inoculation inoc) {

  int index = hashFunc(map, key);

  Node *newNode = createNewNode(inoc.name, inoc.batch, inoc.date, inoc.vacName);

  // If the index is empty, insert the node directly
  if (map->arr[index] == NULL) {
    map->arr[index] = newNode;
  } else {
    // Otherwise, go through the linked list and append the new node
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

  // Goes through the linked list
  while (head != NULL) {
    // Check if the name, vaccine name, and date match
    if (strcmp(head->inoc.name, name) == 0 &&
        strcmp(head->inoc.vacName, vacName) == 0 &&
        compareDates(head->inoc.date, date) == 0) {
      return 1; // Already vaccinated
    }
    head = head->next;
  }
  return 0; // Not vaccinated
}

void removeInocByNameAndDate(Node **sys, char *name, Date date, int *count) {
  Node *current = *sys;
  Node *prev = NULL;

  // Goes through the linked list
  while (current != NULL) {

    if (!strcmp(name, current->inoc.name) &&
        !compareDates(date, current->inoc.date)) {
      (*count)++;
      if (prev == NULL) {
        *sys = current->next;

      } else {
        prev->next = current->next;
      }

      Node *temp = current;
      current = current->next;

      free(temp->inoc.name);    // Free the dynamically allocated name 
      free(temp);               // Free the node itself

    } else {
      prev = current;
      current = current->next;
    }
  }
}

void removeInocByNameBatchAndDate(Node **sys, char *name, char *batch,
                                  Date date, int *count, int *countBatch) {
  Node *current = *sys;
  Node *prev = NULL;

  // Goes through the linked list
  while (current != NULL) {

    if (!strcmp(batch, current->inoc.batch)) {
      (*countBatch)++;
    }

    if (!strcmp(name, current->inoc.name) &&
        !strcmp(batch, current->inoc.batch) &&
        !compareDates(date, current->inoc.date)) {
      // counter to do some verifications in the main
      (*count)++;

      if (prev == NULL) {
        *sys = current->next;

      } else {
        prev->next = current->next;
      }

      Node *temp = current;
      current = current->next;

      free(temp->inoc.name);    // Free the dynamically allocated name
      free(temp);               // Free the node itself


    } else {
      prev = current;
      current = current->next;
    }
  }
}

void removeInocByName(Node **sys, char *name, int *count) {
  Node *current = *sys;
  Node *prev = NULL;

  // Goes through the linked list
  while (current != NULL) {

    if (!strcmp(name, current->inoc.name)) {
      // counter to do some verifications in the main
      (*count)++;

      if (prev == NULL) {
        *sys = current->next;

      } else {
        prev->next = current->next;
      }

      Node *temp = current;
      current = current->next;

      free(temp->inoc.name);  // Free the dynamically allocated name
      free(temp);             // Free the node itself


    } else {
      prev = current;
      current = current->next;
    }
  }
}

int inocVerify(char *name, Node *sys, int pt) {
  int countName = 0;

  // Goes through the linked list
  for (Node *current = sys; current != NULL; current = current->next) {

    if (!strcmp(name, current->inoc.name)) {
      countName++;
      break;
    }
  }
  if (countName == 0) {
    printf(pt ? "%s: no such user\n" : "%s: utente inexistente\n", name);
    return 0;
  }
  return 1;
}

void freeHashMap(hashMap *map) {

  // Iterate through each index in the hash map
  for (int i = 0; i < map->size; i++) {

    Node *current = map->arr[i];
    // Free all nodes in the linked list
    while (current != NULL) {

      Node *temp = current;
      current = current->next;

      free(temp->inoc.name); // Free the dynamically allocated name
      free(temp);            // Free the node itself
    }
  }
  // Free the array and the hash map structure
  free(map->arr);
  free(map);
}

void removeHashByNameBatchAndDate(hashMap *map, char *name, char *batch,
                                  Date date) {

  int index = hashFunc(map, name);
  Node *current = map->arr[index];
  Node *prev = NULL;

  // Goes through the linked list
  while (current != NULL) {
    // Check if the name, batch, and date match
    if (strcmp(name, current->inoc.name) == 0 &&
        strcmp(batch, current->inoc.batch) == 0 &&
        compareDates(date, current->inoc.date) == 0) {
      // Remove the node from the linked list

      if (prev == NULL) {
        map->arr[index] = current->next;
      } else {
        prev->next = current->next;
      }

      Node *temp = current;
      current = current->next;

      free(temp->inoc.name); // Free the dynamically allocated name
      free(temp);            // Free the node itself

    } else {
      prev = current;
      current = current->next;
    }
  }
}

void removeHashByNameAndDate(hashMap *map, char *name, Date date) {

  int index = hashFunc(map, name);
  Node *current = map->arr[index];
  Node *prev = NULL;

  // Goes through the linked list
  while (current != NULL) {
    // Check if the name and date match
    if (strcmp(name, current->inoc.name) == 0 &&
        compareDates(date, current->inoc.date) == 0) {
      // Remove the node from the linked list

      if (prev == NULL) {
        map->arr[index] = current->next;

      } else {
        prev->next = current->next;
      }

      Node *temp = current;
      current = current->next;

      free(temp->inoc.name); // Free the dynamically allocated name
      free(temp);            // Free the node itself

    } else {
      prev = current;
      current = current->next;
    }
  }
}

int extractNameFromInput(char **input, char **name, int pt) {
  char *ptr = *input;
  // Find end of name: closing quote for quoted strings, space/newline otherwise
  char *end = (*ptr == '"') ? strchr(ptr + 1, '"') : 
                strchr(ptr, ' ') ?: strchr(ptr, '\n');

  // Calculate length
  size_t nameLen = (*ptr == '"') ? (end - ptr - 1) : (end - ptr);

  *name = malloc(nameLen + 1);

  if (!*name) {
    puts(pt ? NOMEMORY : SEMMEMORIA);
    return 1;
  }

  // Copies the sting into the allocated space
  strncpy(*name, (*ptr == '"') ? ptr + 1 : ptr, nameLen);
  (*name)[nameLen] = '\0';

  // Update input pointer to position after extracted name
  *input = (*ptr == '"') ? end + 1 : end;

  return 0;
}
