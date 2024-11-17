#ifndef LIST_TYPEDEFS_H_
#define LIST_TYPEDEFS_H_

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**My pretty constants**/
/*****************************************/
typedef int ListElem_t;                /**/
                                       /**/
const size_t StartHeadCellIndex  = 0;  /**/
const size_t StartTailCellIndex  = 0;  /**/
const size_t StartFreeCellIndex  = 1;  /**/
                                       /**/
const size_t StartListLength     = 1;  /**/
                                       /**/
const size_t NextOffset          = 1;  /**/
const size_t PreviousOffset      = 1;  /**/
const size_t AccountDummyElement = 1;  /**/
/*****************************************/
/**I love my constants**/

enum LIST_ELEMENT
{
    LIST_POISON   = -1,
    DUMMY_ELEMENT =  0,
};

enum LIST_ERROR
{
    LIST_NONE                              =  0,
    LIST_INVALID_CAPACITY                  =  1,
    LIST_ALLOCATION_ERROR                  =  2,
    LIST_DATA_ALLOCATION_ERROR             =  3,
    LIST_NEXT_ELEMENT_ALLOCATION_ERROR     =  4,
    LIST_PREVIOUS_ELEMENT_ALLOCATION_ERROR =  5,
    LIST_GOING_BEYOND_UP                   =  6,
    LIST_GOING_BEYOND_DOWN                 =  7,
    LIST_INSERT_ERROR                      =  8,
    LIST_DUMMY_ELEMENT_CALL                =  9,
    LIST_INVALID_ELEMENT_INDEX             = 10,
};

struct LIST
{
    LIST_ERROR  error;
    size_t      length;
    size_t      capacity;
    size_t      free;
    size_t      head;
    size_t      tail;
    ListElem_t* data;
    size_t*     next;
    size_t*     previous;
};

#endif
