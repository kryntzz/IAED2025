/*
 * Projecto de IAED2025
 * @file Projecto.c
 * @author ist1113637 (Simão Lavos)
 */

#include "all.h"
#include "inoculation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Changes the current date of the system.
 *
 * @param sys Pointer to the system structure.
 * @param input Input string containing the new date.
 * @param pt Language flag (0 for Portuguese, 1 for English).
 */
void changeDate(Sys *sys, char *input, int pt) {
  Date date;
  if (sscanf(input, "%*s %d-%d-%d", &date.day, &date.month, &date.year) <= 1) {
    printDate(sys->currentDate);
  } else {
    if (!validDate(date) || compareDates(sys->currentDate, date) > 0) {
      puts(pt ? EINVDATE : DATAINV);
      return;
    }
    sys->currentDate = date;
    printDate(date);
  }
}

/**
 * @brief Verifies if a vaccine is valid.
 *
 * @param sys Pointer to the system structure.
 * @param vaccine Vaccine structure to verify.
 * @param pt Language flag (0 for Portuguese, 1 for English).
 * @return int 1 if the vaccine is valid, 0 otherwise.
 */
int verifyVaccine(Sys *sys, Vaccine vaccine, int pt) {

  if (!batchExists(sys, vaccine.batch)) {
    puts(pt ? EDUPBATCH : LOTEDUP);
    return 0;
  }

  if (!validBatch(vaccine.batch)) {
    puts(pt ? EINVBATCH : LOTEINV);
    return 0;
  }

  if (!validName(vaccine.name)) {
    puts(pt ? EINVNAME : NOMEINV);
    return 0;
  }

  if (!validDate(vaccine.date) ||
      compareDates(sys->currentDate, vaccine.date) > 0) {
    puts(pt ? EINVDATE : DATAINV);
    return 0;
  }

  if (vaccine.stock < 0) {
    puts(pt ? INVQUANT_EN : INVQUANT);
    return 0;
  }
  return 1;
}

/**
 * @brief Creates a new vaccine and adds it to the system.
 *
 * @param sys Pointer to the system structure.
 * @param input Input string containing the vaccine details.
 * @param pt Language flag (0 for Portuguese, 1 for English).
 */
void createVaccine(Sys *sys, char *input, int pt) {
  Vaccine vaccine;
  Date date;

  if (sys->count + 1 > MAXBATCH) {
    puts(pt ? EMAXVACCINE : MXMVACINAS);
    return;
  }

  if (!validateVaccineInput(input, pt)) {
    return;
  }

  sscanf(input, "%*s %s %d-%d-%d %d %s", vaccine.batch, &date.day, &date.month,
         &date.year, &vaccine.stock, vaccine.name);

  vaccine.date = date;

  if (!verifyVaccine(sys, vaccine, pt))
    return;

  vaccine.appDoses = 0;
  sys->data[sys->count] = vaccine;
  sys->count++;
  vaccineSort(sys->data, sys->count);
  printf("%s\n", vaccine.batch);
}

/**
 * @brief Lists all vaccines or vaccines with a specific name.
 *
 * @param sys Pointer to the system structure.
 * @param input Input string containing the name of the vaccine.
 * @param pt Language flag (0 for Portuguese, 1 for English).
 */
void listVaccine(Sys *sys, char *input, int pt) {
  char name[MAXNAME];

  if (sscanf(input, "%*s %s", name) < 1) {
    for (int i = 0; i < sys->count; i++) {
      dispayVaccine(sys->data[i]);
      putchar('\n');
    }
  } else {

    // Get all the names
    char *token = strtok(input, " ");
    token = strtok(NULL, " \n");

    while (token != NULL) {
      strcpy(name, token);

      if (!nameExists(sys->data, name, sys->count)) {
        printf("%s: ", name);
        puts(pt ? EINVNAMEVAC : NOMEVACINV);
      } else {
        for (int i = 0; i < sys->count; i++) {
          if (!strcmp(name, sys->data[i].name)) {
            dispayVaccine(sys->data[i]);
            putchar('\n');
          }
        }
      }
      token = strtok(NULL, " \n");
    }
  }
}

/**
 * @brief Appends a new node to the system's linked list.
 *
 * @param sys Pointer to the system structure.
 * @param newNode Pointer to the new node to append.
 */
void appendNode(Sys *sys, Node *newNode) {
  if (!sys->data2)
    sys->data2 = sys->tail = newNode;
  else
    sys->tail->next = newNode, sys->tail = newNode;
}

/**
 * @brief Applies an inoculation to a user.
 *
 * @param sys Pointer to the system structure.
 * @param input Input string containing the inoculation details.
 * @param pt Language flag (0 for Portuguese, 1 for English).
 */
void applyInoculation(Sys *sys, char *input, int pt) {
  unsigned long nameLen;
  char *name = extractName(&input, &nameLen);
  while (*input == ' ')
    input++;
  char vacName[MAXNAME];
  sscanf(input, "%s", vacName);

  Vaccine *vaccine =
      findVaccine(sys->data, vacName, sys->count, sys->currentDate);
  if (!vaccine) {
    puts(pt ? NOSTOCK : ESGOTADO);
    free(name);
    return;
  }

  // Verify if the pacient as already been vaccinated
  // for the same vaccine that day
  if (isVaccinated(sys->map, name, vacName, sys->currentDate)) {
    printf(pt ? "already vaccinated\n" : "já vacinado\n");
    free(name);
    return;
  }

  Node *newNode =
      createNewNode(name, vaccine->batch, sys->currentDate, vacName);
  appendNode(sys, newNode);
  printf("%s\n", vaccine->batch);
  vaccine->stock--, vaccine->appDoses++;
  insertHash(sys->map, name, newNode->inoc);
  free(name);
}

/**
 * @brief Lists all inoculations or inoculations for a specific user.
 *
 * @param sys Pointer to the system structure.
 * @param input Input string containing the user's name.
 * @param pt Language flag (0 for Portuguese, 1 for English).
 */
void listInoculation(Sys *sys, char *input, int pt) {
  int count = 0;
  char *name, *ptr = input;
  ptr = strchr(ptr, ' ');

  // Standart case
  if (!ptr) {
    for (Node *current = sys->data2; current != NULL; current = current->next) {
      displayInoc(current->inoc);
    }
    return;
  }
  ptr++;

  // Get the name
  char *end = (*ptr == '"') ? strchr(ptr + 1, '"') : strchr(ptr, ' ') ?: strchr(ptr, '\n');
  size_t nameLen = (*ptr == '"') ? (end - ptr - 1) : (end - ptr);
  name = malloc(nameLen + 1);
  if (name == NULL) {
    puts(pt ? NOMEMORY : SEMMEMORIA);
    return;
  }
  strncpy(name, (*ptr == '"') ? ptr + 1 : ptr, nameLen);
  name[nameLen] = '\0';

  for (Node *current = sys->data2; current != NULL; current = current->next) {
    if (!strcmp(name, current->inoc.name)) {
      count++;
      displayInoc(current->inoc);
    }
  }

  if (count == 0)
    printf(pt ? "%s: no such user\n" : "%s: utente inexistente\n", name);
  free(name);
}

/**
 * @brief Removes a vaccine batch from the system.
 *
 * @param sys Pointer to the system structure.
 * @param input Input string containing the batch code.
 * @param pt Language flag (0 for Portuguese, 1 for English).
 */
void removeVaccine(Sys *sys, char *input, int pt) {
  char batch[MAXBATCHCODE];
  sscanf(input, "%*s %s", batch);

  for (int i = 0; i < sys->count; i++) {
    if (strcmp(batch, sys->data[i].batch) == 0) {
      printf("%d\n", sys->data[i].appDoses);
      if (sys->data[i].appDoses == 0) {
        for (int j = i; j < sys->count - 1; j++) {
          sys->data[j] = sys->data[j + 1];
        }
        sys->count--;
      } else {
        sys->data[i].stock = 0;
      }
      return;
    }
  }
  printf(pt ? "%s: no such batch\n" : "%s: lote inexistente\n", batch);
}

/**
 * @brief Helper function to remove inoculations by name and date.
 *
 * @param sys Pointer to the system structure.
 * @param name Name of the user.
 * @param date Date of the inoculation.
 * @param count Pointer to store the count of removed inoculations.
 */
void removeInocByNameAndDateHelper(Sys *sys, char *name, Date date,
                                   int *count) {
  removeInocByNameAndDate(&sys->data2, name, date, count);
  removeHashByNameAndDate(sys->map, name, date);
}

/**
 * @brief Helper function to remove inoculations by name, batch, and date.
 *
 * @param sys Pointer to the system structure.
 * @param name Name of the user.
 * @param batch Batch code of the vaccine.
 * @param date Date of the inoculation.
 * @param count Pointer to store the count of removed inoculations.
 * @param countBatch Pointer to store the count of removed batches.
 * @param pt Language flag (0 for Portuguese, 1 for English).
 */
void removeInocByNameBatchHelper(Sys *sys, char *name, char *batch, Date date,
                                 int *count, int *countBatch, int pt) {
  removeInocByNameBatchAndDate(&sys->data2, name, batch, date, count,
                               countBatch);
  removeHashByNameBatchAndDate(sys->map, name, batch, date);
  if (*countBatch == 0) {
    printf(pt ? "%s: no such batch\n" : "%s: lote inexistente\n", batch);
  }
}

/**
 * @brief Helper function to handle the default case for removing inoculations.
 *
 * @param sys Pointer to the system structure.
 * @param name Name of the user.
 * @param count Pointer to store the count of removed inoculations.
 */
void removeInocDefaultCase(Sys *sys, char *name, int *count) {
  removeInocByName(&sys->data2, name, count);
  sys->map->arr[hashFunc(sys->map, name)] = NULL;
}

/**
 * @brief Removes inoculations based on the input string.
 *
 * This function handles the removal of inoculations from the system based on
 * the provided input. It supports different cases, such as removing by name
 * and date, by name, batch, and date, or by name only.
 *
 * @param sys Pointer to the system structure.
 * @param input Input string containing the removal details.
 * @param pt Language flag (0 for Portuguese, 1 for English).
 */
void removeInoc(Sys *sys, char *input, int pt) {
    int count = 0, inp = 0, countBatch = 0;
    char batch[MAXBATCHCODE], *name, *ptr = input;
    Date date;

    ptr = strchr(ptr, ' ');
    ptr++;
    if (extractNameFromInput(&ptr, &name, pt)) return;
    if (!inocVerify(name, sys->data2, pt)) { free(name); return; }

    inp = sscanf(input, "%*s %*s %d-%d-%d %s", &date.day, &date.month, &date.year, batch);
    
    switch (inp) {
        case 3:
            if (!validateDate(date, sys->currentDate, pt)) { free(name); return; }
            removeInocByNameAndDateHelper(sys, name, date, &count);
            break;
        case 4:
            removeInocByNameBatchHelper(sys, name, batch, date, &count, &countBatch, pt);
            if (countBatch == 0) { free(name); return; }
            break;
        default:
            removeInocDefaultCase(sys, name, &count);
            break;
    }
    free(name);
    printf("%d\n", count);
}

/**
 * @brief Initializes the system with default values.
 *
 * @param sys Pointer to the system structure.
 */
void initializeSystem(Sys *sys) {
  sys->currentDate.day = 1;
  sys->currentDate.month = 1; // Default: 01-01-2025
  sys->currentDate.year = 2025;
  sys->count = 0;
  sys->data2 = NULL;
  sys->tail = sys->data2;
  sys->map = (hashMap *)malloc(sizeof(hashMap));
  initializeHashMap(sys->map);
}

/**
 * @brief Main function of the program.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return int Exit status.
 */
int main(int argc, char **argv) {
  int pt = 1;
  char buf[BUFMAX];
  Sys sys;
  initializeSystem(&sys);

  if (argc > 1 && strcmp(argv[1], "pt") == 0)
    pt = 0; // Checks if the input is in Portuguese

  while (fgets(buf, BUFMAX, stdin)) {
    switch (buf[0]) {
    case 'q':
      freeSystem(&sys.data2); freeHashMap(sys.map); return 0;
    case 'c':
      createVaccine(&sys, buf, pt); break;
    case 'l':
      listVaccine(&sys, buf, pt); break;
    case 'a':
      applyInoculation(&sys, buf, pt); break;
    case 't':
      changeDate(&sys, buf, pt); break;
    case 'u':
      listInoculation(&sys, buf, pt); break;
    case 'r':
      removeVaccine(&sys, buf, pt); break;
    case 'd':
      removeInoc(&sys, buf, pt); break;
    }
  }
  return 0;
}
