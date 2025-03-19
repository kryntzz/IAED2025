#ifndef CONFIG_H
#define CONFIG_H

#define MAXBATCHCODE 20 /** The max. len. of batch code*/
#define MAXNAME 50      /** The max. len. of vaccine name*/
#define BUFMAX 65535    /** The max. len. of input lines*/
#define MAXBATCH 1000   /** The max. len. of batches */
#define MAXPERSONNAME 200

#define EMAXVACCINE "too many vaccines"
#define EDUPBATCH "duplicate batch number"
#define EINVBATCH "invalid batch"
#define EINVNAME "invalid name"
#define EINPUT "invalid input"
#define EINVNAMEVAC "no such vaccine"
#define EINVDATE "invalid date"

#define MXMVACINAS "demasiadas vacinas"
#define LOTEDUP "número de lote duplicado"
#define LOTEINV "lote inválido"
#define NOMEINV "nome inválido"
#define INPUTINV "input inválido"
#define NOMEVACINV "vacina inexistente"
#define DATAINV "data inválida"

#endif // !CONFIG_H
