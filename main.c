/*
 * Projecto de IAED2025
 * @file Projecto.c
 * @author ist1113637 (Simão Lavos)
 */

#include "include/all.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void freeSystem(Node **head) {
  Node *current = *head;
  while (current != NULL) {
    Node *aux = current;
    current = current->next;
    free(aux->inoc.name);
    free(aux);
  }
  *head = NULL;
}

/** Checks if a name already exists in the system
 * @param sys> system to check the name
 * @param name> name to check
 * @return 1 if the name does not exist, 0 otherwise
 */
int nameExists(Sys *sys, char *name) {
  for (int i = 0; i < sys->count; i++) {
    if (!strcmp(name, sys->data[i].name)) {
      return 0;
    }
  }
  return 1;
}

int validName(char name[MAXNAME]) {
  int len = strlen(name);
  if (len > MAXNAME) {
    return 1;
  }
  for (int i = 0; i < len; i++) {
    char c = name[i];
    if (c == ' ' || c == '\n' || c == '\t') {
      return 1;
    }
  }
  return 0;
}

void changeDate(Sys *sys, char *input, int pt) {
  Date date;
  if (sscanf(input, "%*s %d-%d-%d", &date.day, &date.month, &date.year) <= 1) {
    printf("%02d-%02d-%02d\n", sys->currentDate.day, sys->currentDate.month,
           sys->currentDate.year);
  } else {
    if (validDate(date) == 1 || compareDates(sys->currentDate, date) > 0) {
      if (pt == 0)
        puts(DATAINV);
      else
        puts(EINVDATE);
      return;
    }
    sys->currentDate = date;
    printf("%02d-%02d-%02d\n", date.day, date.month, date.year);
  }
}

void createVaccine(Sys *sys, char *input, int pt) {
  Vaccine vaccine;
  char input2[BUFMAX];
  strcpy(input2, input);
  Date date;
  if (sys->count + 1 > MAXBATCH) {
    if (pt == 0)
      puts(MXMVACINAS);
    else
      puts(EMAXVACCINE);
    return;
  }
  char *token = strtok(input2, " ");
  token = strtok(NULL, " ");
  if (strlen(token) > MAXBATCHCODE) {
    if (pt == 0)
      puts(LOTEINV);
    else
      puts(EINVBATCH);
    return;
  }
  token = strtok(NULL, " ");
  token = strtok(NULL, " ");
  token = strtok(NULL, " ");
  if (strlen(token) > MAXNAME) {
    if (pt == 0)
      puts(NOMEINV);
    else
      puts(EINVNAME);
    return;
  }

  sscanf(input, "%*s %s %d-%d-%d %d %s", vaccine.batch, &date.day, &date.month,
         &date.year, &vaccine.stock, vaccine.name);

  vaccine.date = date;

  if (batchExists(sys, vaccine.batch) == 0) {
    if (pt == 0)
      puts(LOTEDUP);
    else
      puts(EDUPBATCH);
    return;
  }

  if (validBatch(vaccine.batch) == 1) {
    if (pt == 0)
      puts(LOTEINV);
    else
      puts(EINVBATCH);
    return;
  }

  if (validName(vaccine.name) == 1) {
    if (pt == 0)
      puts(NOMEINV);
    else
      puts(EINVNAME);
    return;
  }
  if (validDate(date) == 1 || compareDates(sys->currentDate, date) > 0) {
    if (pt == 0)
      puts(DATAINV);
    else
      puts(EINVDATE);
    return;
  }

  if (vaccine.stock < 0) {
    if (pt == 0)
      printf("quantidade inválida\n");
    else
      printf("invalid quantity\n");
    return;
  }
  vaccine.appDoses = 0;
  sys->data[sys->count] = vaccine;
  sys->count++;
  vaccineSort(sys->data, sys->count);
  printf("%s\n", vaccine.batch);
}

void listVaccine(Sys *sys, char *input, int pt) {
  char name[MAXNAME];

  if (sscanf(input, "%*s %s", name) < 1) {
    Vaccine vaccines[sys->count];
    for (int i = 0; i < sys->count; i++) {
      vaccines[i] = sys->data[i];
    }
    for (int i = 0; i < sys->count; i++) {
      dispayVaccine(vaccines[i]);
      putchar('\n');
    }

  } else {
    char *token = strtok(input, " ");
    token = strtok(NULL, " \n");

    while (token != NULL) {
      strcpy(name, token);

      if (nameExists(sys, name) == 1) {
        printf("%s: ", name);
        if (pt == 0)
          puts(NOMEVACINV);
        else
          puts(EINVNAMEVAC);
      } else {

        Vaccine vaccines[sys->count];
        int count = 0;

        for (int i = 0; i < sys->count; i++) {
          if (strcmp(name, sys->data[i].name) == 0) {
            vaccines[count++] = sys->data[i];
          }
        }

        for (int i = 0; i < count; i++) {
          dispayVaccine(vaccines[i]);
          putchar('\n');
        }
      }
      token = strtok(NULL, " \n");
    }
  }
}

void applyInoculation(Sys *sys, char *input, int pt) {
  char *name;
  char vacName[MAXNAME];
  unsigned long nameLen = 0;

  input = strchr(input, ' ');
  input++;

  if (*input == '"') {
    input++;
    char *endQuote = strchr(input, '"');
    nameLen = endQuote - input;
    name = malloc(nameLen + 1);

    strncpy(name, input, nameLen);
    name[nameLen] = '\0';
    input = endQuote + 1;
  } else {
    char *endSpace = strchr(input, ' ');
    nameLen = endSpace - input;
    name = malloc(nameLen + 1);

    strncpy(name, input, nameLen);
    name[nameLen] = '\0';
    input = endSpace;
  }

  while (*input == ' ')
    input++;
  sscanf(input, "%s", vacName);

  Vaccine *selectedVaccine = NULL;

  for (int i = 0; i < sys->count; i++) {
    if (strcmp(vacName, sys->data[i].name) == 0 &&
        validDate(sys->data[i].date) == 0 &&
        compareDates(sys->currentDate, sys->data[i].date) < 0 &&
        sys->data[i].stock > 0) {
      selectedVaccine = &sys->data[i];
      break;
    }
  }

  if (selectedVaccine == NULL) {
    if (pt == 0)
      printf("esgotado\n");
    else
      printf("no stock\n");
    free(name);
    return;
  }

  // Check if the user is already vaccinated using the hash map
  if (isVaccinated(sys->map, name, vacName, sys->currentDate)) {
    if (pt == 0)
      printf("já vacinado\n");
    else
      printf("already vaccinated\n");
    free(name);
    return;
  }

  Node *newNode =
      createNewNode(name, selectedVaccine->batch, sys->currentDate, vacName);
  if (sys->data2 == NULL) {

    sys->data2 = newNode;
    sys->tail = newNode;
  } else {
    sys->tail->next = newNode;
    sys->tail = newNode;
  }

  printf("%s\n", selectedVaccine->batch);

  selectedVaccine->stock--;
  selectedVaccine->appDoses++;

  // Insert the new inoculation into the hash map
  insertHash(sys->map, name, newNode->inoc);

  free(name);
}

void listInoculation(Sys *sys, char *input, int pt) {
  int count = 0;
  unsigned long nameLen = 0;
  char *name;
  char *ptr = input;
  ptr = strchr(ptr, ' ');
  if (!ptr) {
    for (Node *current = sys->data2; current != NULL; current = current->next) {
      displayInoc(current->inoc);
    }
    return;
  }
  ptr++;

  if (*ptr == '"') {
    ptr++;
    char *endQuote = strchr(ptr, '"');

    nameLen = endQuote - ptr;
    name = malloc(nameLen + 1);
    if (name == NULL) {
      if (pt == 0)
        puts("erro de memória");
      else
        puts("memory error");
      return;
    }
    strncpy(name, ptr, nameLen);
    name[nameLen] = '\0';
    ptr = endQuote + 1;
  } else {
    char *endSpace = strchr(ptr, '\n');
    nameLen = endSpace - ptr;
    name = malloc(nameLen + 1);
    if (name == NULL) {
      if (pt == 0)
        puts("sem memória");
      else
        puts("no memory");
      return;
    }
    strncpy(name, ptr, nameLen);
    name[nameLen] = '\0';
    ptr = endSpace;
  }

  for (Node *current = sys->data2; current != NULL; current = current->next) {
    if (strcmp(name, current->inoc.name) == 0) {
      count++;
      displayInoc(current->inoc);
    }
  }

  if (count == 0) {
    if (pt == 0)
      printf("%s: utente inexistente\n", name);
    else
      printf("%s: no such user\n", name);
    free(name);
    return;
  }

  free(name);
}

void removeDisp(Sys *sys, char *input, int pt) {
  char batch[MAXBATCHCODE];
  sscanf(input, "%*s %s", batch);

  for (int i = 0; i < sys->count; i++) {
    if (strcmp(batch, sys->data[i].batch) == 0) {
      printf("%d\n", sys->data[i].appDoses);
      if (sys->data[i].appDoses == 0) {
        // Remove the batch if no doses have been applied
        for (int j = i; j < sys->count - 1; j++) {
          sys->data[j] = sys->data[j + 1];
        }
        sys->count--;
      } else {
        // Set stock to applied doses if there have been inoculations
        sys->data[i].stock = 0;
      }
      return;
    }
  }
  if (pt == 0)
    printf("%s: lote inexistente\n", batch);
  else
    printf("%s: no such batch\n", batch);
}

void removeInoc(Sys *sys, char *input, int pt) {
  int count = 0;
  char batch[MAXBATCHCODE];
  unsigned long nameLen = 0;
  char *name;
  Date date;
  char *ptr = input;
  ptr = strchr(ptr, ' ');

  ptr++;

  if (*ptr == '"') {
    ptr++;
    char *endQuote = strchr(ptr, '"');

    nameLen = endQuote - ptr;
    name = malloc(nameLen + 1);
    if (name == NULL) {
      if (pt == 0)
        puts("sem memória");
      else
        puts("no memory");
      return;
    }
    strncpy(name, ptr, nameLen);
    name[nameLen] = '\0';
    ptr = endQuote + 1;
  } else {
    char *endSpace = strchr(ptr, ' ');
    if (endSpace == NULL) {
      endSpace = strchr(ptr, '\n');
    }
    nameLen = endSpace - ptr;
    name = malloc(nameLen + 1);
    if (name == NULL) {
      if (pt == 0)
        puts("sem memória");
      else
        puts("no memory");
      return;
    }
    strncpy(name, ptr, nameLen);
    name[nameLen] = '\0';
    ptr = endSpace;
  }

  int countName = 0;
  for (Node *current = sys->data2; current != NULL; current = current->next) {
    if (strcmp(name, current->inoc.name) == 0) {
      countName++;
      break;
    }
  }
  if (countName == 0) {
    if (pt == 0)
      printf("%s: utente inexistente\n", name);
    else
      printf("%s: no such user\n", name);
    free(name);
    return;
  }
  int inp = 0;
  int countBatch = 0;

  if ((inp = sscanf(input, "%*s %*s %d-%d-%d %s", &date.day, &date.month,
                    &date.year, batch)) == 3) {
    if (compareDates(sys->currentDate, date) < 0 || validDate(date) == 1) {
      if (pt == 0)
        puts(DATAINV);
      else
        puts(EINVDATE);
      free(name);
      return;
    }
    Node *current = sys->data2;
    Node *prev = NULL;
    while (current != NULL) {
      if (strcmp(name, current->inoc.name) == 0 &&
          compareDates(date, current->inoc.date) == 0) {
        count++;
        if (prev == NULL) {
          sys->data2 = current->next;
        } else {
          prev->next = current->next;
        }
        Node *temp = current;
        current = current->next;
        free(temp->inoc.name);
        free(temp);
      } else {
        prev = current;
        current = current->next;
      }
    }
  } else if (inp == 4) {
    Node *current = sys->data2;
    Node *prev = NULL;
    while (current != NULL) {
      if (strcmp(batch, current->inoc.batch) == 0) {
        countBatch++;
      }
      if (strcmp(name, current->inoc.name) == 0 &&
          strcmp(batch, current->inoc.batch) == 0 &&
          compareDates(date, current->inoc.date) == 0) {
        count++;
        if (prev == NULL) {
          sys->data2 = current->next;
        } else {
          prev->next = current->next;
        }
        Node *temp = current;
        current = current->next;
        free(temp->inoc.name);
        free(temp);
      } else {
        prev = current;
        current = current->next;
      }
    }
    if (countBatch == 0) {
      if (pt == 0)
        printf("%s: lote inexistente\n", batch);
      else
        printf("%s: no such batch\n", batch);
      free(name);
      return;
    }
  } else {
    Node *current = sys->data2;
    Node *prev = NULL;
    while (current != NULL) {
      if (strcmp(name, current->inoc.name) == 0) {
        count++;
        if (prev == NULL) {
          sys->data2 = current->next;
        } else {
          prev->next = current->next;
        }
        Node *temp = current;
        current = current->next;
        free(temp->inoc.name);
        free(temp);
      } else {
        prev = current;
        current = current->next;
      }
    }
  }

  free(name);
  printf("%d\n", count);
}

int main(int argc, char **argv) {
  char pt = 1;
  char buf[BUFMAX];
  Sys sys;
  sys.currentDate.day = 1;
  sys.currentDate.month = 1;
  sys.currentDate.year = 2025;

  sys.count = 0;
  sys.data2 = NULL;
  sys.tail = sys.data2;

  sys.map = (hashMap *)malloc(sizeof(hashMap)); // Allocate memory for sys.map
  initializeHashMap(sys.map);

  if (argc > 1 && strcmp(argv[1], "pt") == 0)
    pt = 0;

  while (fgets(buf, BUFMAX, stdin)) {
    switch (buf[0]) {
    case 'q':
      freeSystem(&sys.data2);
      freeHashMap(sys.map); // Free the hash map
      return 0;
    case 'c':
      createVaccine(&sys, buf, pt);
      break;
    case 'l':
      listVaccine(&sys, buf, pt);
      break;
    case 'a':
      applyInoculation(&sys, buf, pt);
      break;
    case 't':
      changeDate(&sys, buf, pt);
      break;
    case 'u':
      listInoculation(&sys, buf, pt);
      break;
    case 'r':
      removeDisp(&sys, buf, pt);
      break;
    case 'd':
      removeInoc(&sys, buf, pt);
      break;
    }
  }
  return 0;
}
