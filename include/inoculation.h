#ifndef INOCULATION_H
#define INOCULATION_H
#include "config.h"
#include "date.h"
#include "vaccine.h"

/**
 * @brief Structure to represent a Inoculation.
 */
typedef struct {
  char *name;                   /** Name of the person inoculated */
  char batch[MAXBATCHCODE + 1]; /** Batch code of the vaccine     */
  Date date;                    /** Date of inoculation           */
  char vacName[MAXNAME];        /** Name of the vaccine           */
} Inoculation;

/**
 * @brief Structure to represent a Node for a linked list.
 */
typedef struct Node {
  Inoculation inoc;  /** Inoculation data         */
  struct Node *next; /** Pointer to the next node */
} Node;

/**
 * @brief Structure to represent a  list.
 */
typedef struct {
  int count;  /** Number of elements in the hash map     */
  int size;   /** Size of the hash map                   */
  Node **arr; /** Array of pointers to linked list nodes */
} hashMap;

/**
 * @brief Frees the memory allocated for the system's linked list.
 *
 * @param head Pointer to the head of the linked list.
 */
void freeSystem(Node **head);

/**
 * @brief Displays the details of an inoculation.
 *
 * @param inoculation The inoculation to display.
 */
void displayInoc(Inoculation inoculation);

/**
 * @brief Creates a new node with the given inoculation details.
 *
 * @param name The name of the person.
 * @param batch The batch code of the vaccine.
 * @param date The date of inoculation.
 * @param vacname The name of the vaccine.
 * @return Node* Pointer to the newly created node.
 */
Node *createNewNode(const char *name, const char *batch, Date date,
                    const char *vacname);

/**
 * @brief Initializes the hash map.
 *
 * @param map Pointer to the hash map to initialize.
 */
void initializeHashMap(hashMap *map);

/**
 * @brief Hash function to generate an index for a given key.
 *
 * @param map Pointer to the hash map.
 * @param key The key to hash.
 * @return int The generated index.
 */
int hashFunc(hashMap *map, char *key);

/**
 * @brief Inserts an inoculation into the hash map.
 *
 * @param map Pointer to the hash map.
 * @param key The key associated with the inoculation.
 * @param inoc The inoculation to insert.
 */
void insertHash(hashMap *map, char *key, Inoculation inoc);

/**
 * @brief Checks if a person is vaccinated with a specific vaccine on a specific
 * date.
 *
 * @param map Pointer to the hash map.
 * @param name The name of the person.
 * @param vacName The name of the vaccine.
 * @param date The date of inoculation.
 * @return int 1 if vaccinated, 0 otherwise.
 */
int isVaccinated(hashMap *map, char *name, char *vacName, Date date);

/**
 * @brief Removes inoculations by name and date.
 *
 * @param sys Pointer to the system structure.
 * @param name Name of the user.
 * @param date Date of the inoculation.
 * @param count Pointer to store the count of removed inoculations.
 */
void removeInocByNameAndDate(Node **sys, char *name, Date date, int *count);

/**
 * @brief Removes inoculations by name, batch, and date.
 *
 * @param sys Pointer to the system's linked list head.
 * @param name Name of the user.
 * @param batch Batch code of the vaccine.
 * @param date Date of the inoculation.
 * @param count Pointer to store the count of removed inoculations.
 * @param countBatch Pointer to store the count of removed batches.
 */
void removeInocByNameBatchAndDate(Node **sys, char *name, char *batch,
                                  Date date, int *count, int *countBatch);

/**
 * @brief Removes inoculations by name.
 *
 * @param sys Pointer to the system's linked list head.
 * @param name Name of the user.
 * @param count Pointer to store the count of removed inoculations.
 */
void removeInocByName(Node **sys, char *name, int *count);

/**
 * @brief Verifies if user exists
 *
 * @param name Pointer to the name.
 * @param sys Pointer to the system's linked list head.
 * @param pt Language flag (0 for Portuguese, 1 for English).
 */
int inocVerify(char *name, Node *sys, int pt);

/**
 * @brief Frees the memory allocated for the hash map.
 *
 * @param map Pointer to the hash map to free.
 */
void freeHashMap(hashMap *map);

/**
 * @brief Removes an inoculation from the hash map by name, batch, and date.
 *
 * @param map Pointer to the hash map.
 * @param name The name of the person.
 * @param batch The batch code of the vaccine.
 * @param date The date of inoculation.
 */
void removeHashByNameBatchAndDate(hashMap *map, char *name, char *batch,
                                  Date date);

/**
 * @brief Removes an inoculation from the hash map by name and date.
 *
 * @param map Pointer to the hash map.
 * @param name The name of the person.
 * @param date The date of inoculation.
 */
void removeHashByNameAndDate(hashMap *map, char *name, Date date);

/**
 * @brief Extracts a name from the input string and validates memory allocation.
 *
 * @param input Pointer to the input string.
 * @param name Pointer to store the extracted name.
 * @param pt Language flag (0 for Portuguese, 1 for English).
 * @return int 0 if successful, 1 if memory allocation fails.
 */
int extractNameFromInput(char **input, char **name, int pt);

#endif // !INOCULATION_H
