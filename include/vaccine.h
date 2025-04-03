#ifndef VACCINE_H
#define VACCINE_H
#include "config.h"
#include "date.h"

/** node for a linked list of vaccines*/
typedef struct {
  char name[MAXNAME];           /** vaccine name  */
  char batch[MAXBATCHCODE + 1]; /** vaccine batch */
  Date date;                    /** vaccine date  */
  int stock;                    /** vaccine's available doses */
  int appDoses;
} Vaccine;

/**
 * @brief Swaps the value of two vaccines.
 *
 * @param a Pointer to the first vaccine.
 * @param b Pointer to the second vaccine.
 */
void swap(Vaccine *a, Vaccine *b);

/**
 * @brief Checks if a name exists in the system.
 *
 * @param sys Pointer to the system structure.
 * @param name Name to check.
 * @return int 1 if the name exists, 0 otherwise.
 */

int nameExists(Vaccine *sys, char *name, int count);

/**
 * @brief Validates the input for creating a vaccine.
 *
 * @param input Input string containing the vaccine details.
 * @param pt Language flag (0 for Portuguese, 1 for English).
 * @return int 0 if the input is invalid, 1 otherwise.
 */
int validateVaccineInput(char *input, int pt);

/**
 * @brief Validates a name.
 *
 * @param name Name to validate.
 * @return int 0 if the name is invalid, 1 otherwise.
 */
int validName(char name[MAXNAME]);

/**
 * @brief Merges two subarrays of vaccines.
 *
 * @param arr Array of vaccines.
 * @param l Left index.
 * @param m Middle index.
 * @param r Right index.
 */
void merge(Vaccine arr[], int l, int m, int r);

/**
 * @brief Sorts an array of vaccines using merge sort.
 *
 * @param arr Array of vaccines.
 * @param l Left index.
 * @param r Right index.
 */
void mergeSort(Vaccine arr[], int l, int r);

/**
 * @brief Sorts an array of vaccines.
 *
 * @param vaccines Array of vaccines.
 * @param n Number of vaccines.
 */
void vaccineSort(Vaccine vaccines[], int n);

/**
 * @brief Displays a vaccine.
 *
 * @param vaccine Vaccine to display.
 */
void dispayVaccine(Vaccine vaccine);

/**
 * @brief Extracts a name from the input string.
 *
 * @param input Pointer to the input string.
 * @param nameLen Pointer to store the length of the extracted name.
 * @return char* Pointer to the extracted name.
 */
char *extractName(char **input, unsigned long *nameLen);

/**
 * @brief Finds a vaccine by name.
 *
 * @param sys Pointer to the system structure.
 * @param vacName Name of the vaccine to find.
 * @return Vaccine* Pointer to the found vaccine, or NULL if not found.
 */
Vaccine *findVaccine(Vaccine *sys, char *vacName, int count, Date date);

#endif // !VACCINE_H
