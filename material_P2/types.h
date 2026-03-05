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
 * @brief Typedef for a function pointer to compare a stack element at stream
 **/
typedef int (*P_stack_ele_cmp)(const void *, const void *);

#endif /* TYPES_H_ */
