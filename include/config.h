/*
 * Projecto de IAED2025
 * @file config.h
 * @author ist1113637 (Simão Lavos)
 */

#ifndef CONFIG_H
#define CONFIG_H

/**
 * @brief The maximum length of a batch code.
 */
#define MAXBATCHCODE 20

/**
 * @brief The maximum length of a vaccine name.
 */
#define MAXNAME 50

/**
 * @brief The maximum length of input lines.
 */
#define BUFMAX 65535

/**
 * @brief The maximum number of batches.
 */
#define MAXBATCH 1000

/**
 * @brief The maximum length of a person's name.
 */
#define MAXPERSONNAME 200

/**
 * @brief Error message for too many vaccines.
 */
#define EMAXVACCINE "too many vaccines"

/**
 * @brief Error message for duplicate batch number.
 */
#define EDUPBATCH "duplicate batch number"

/**
 * @brief Error message for invalid batch.
 */
#define EINVBATCH "invalid batch"

/**
 * @brief Error message for invalid name.
 */
#define EINVNAME "invalid name"

/**
 * @brief Error message for invalid input.
 */
#define EINPUT "invalid input"

/**
 * @brief Error message for no such vaccine.
 */
#define EINVNAMEVAC "no such vaccine"

/**
 * @brief Error message for invalid date.
 */
#define EINVDATE "invalid date"

/**
 * @brief Error message for no stock;
 */
#define NOSTOCK "no stock"

/*
 * @brief Error message for invalid quantity
 */
#define INVQUANT_EN "invalid quantity"

/*
 * @brief Error message for no memory
 */

#define NOMEMORY "no memory"
/**
 * @brief Error message in Portuguese for too many vaccines.
 */
#define MXMVACINAS "demasiadas vacinas"

/**
 * @brief Error message in Portuguese for duplicate batch number.
 */
#define LOTEDUP "número de lote duplicado"

/**
 * @brief Error message in Portuguese for invalid batch.
 */
#define LOTEINV "lote inválido"

/**
 * @brief Error message in Portuguese for invalid name.
 */
#define NOMEINV "nome inválido"

/**
 * @brief Error message in Portuguese for invalid input.
 */
#define INPUTINV "input inválido"

/**
 * @brief Error message in Portuguese for no such vaccine.
 */
#define NOMEVACINV "vacina inexistente"

/**
 * @brief Error message in Portuguese for invalid date.
 */
#define DATAINV "data inválida"

/*
 * @brief Error message in Portuguese for no stock.
 */
#define ESGOTADO "esgotado"

/*
 * @brief Error message in Portuguese for invalid quantity
 */
#define INVQUANT "quantidade inválida"

/*
 * @brief Error message in Portuguese for no memory
 */
#define SEMMEMORIA "sem memória"

#endif // !CONFIG_H
