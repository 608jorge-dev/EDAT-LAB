
/**
 * @file types.h
 * @author Profesores EDAT
 * @date February 2026
 * @brief ADT Boolean and Status
 *
 * @details Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by @.
 *
 * @see
 */

#ifndef TYPES_H_
#define TYPES_H_

#define MAX_MSC 4096
#define MAX_QUEUE 10
#define NO_MUSICPOSITION -1
#define NO_NUMMUSIC -1
#define NO_RELATIONS -1
#define STR_LENGTH 64           
#define NO_ID -1
#define ID_INIT 0
#define NO_DUR 0
#define DUR_INIT 0
#define DIF_CMP -1
#define ERROR_CMP -2
#define ERROR_PRINT -1
#define ERROR_INDEX -1

/**
 * @brief ADT Boolean
 */
typedef enum
{
    FALSE = 0, /*!< False value */
    TRUE = 1   /*!< True value  */
} Bool;

/**
 * @brief ADT Status
 */
typedef enum
{
    ERROR = 0, /*!< To codify an ERROR output */
    OK = 1     /*!< OK output */
} Status;

/**
 * @brief Typedef for a function pointer to compare elements
 */
typedef int (*P_ele_cmp)(const void *, const void *);

/**
 * @brief Typedef for a function pointer to print elements
 */
typedef int (*P_ele_print)(FILE *, const void *);

#endif /* TYPES_H_ */
