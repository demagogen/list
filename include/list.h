#ifndef LIST_H_
#define LIST_H_

#include "list_typedefs.h"

LIST_ERROR list_ctor                          (LIST* listInfo, size_t capacity);
LIST_ERROR list_dtor                          (LIST* listInfo);
LIST_ERROR list_verify                        (LIST* listInfo);
size_t     list_return_head_index             (LIST* listInfo);
size_t     list_return_tail_index             (LIST* listInfo);
LIST_ERROR list_text_dump                     (LIST* listInfo);
size_t     list_return_next_element_index     (LIST* listInfo, size_t element_index);
size_t     list_return_previous_element_index (LIST* listInfo, size_t element_index);
size_t     list_insert_at_the_beginning       (LIST* listInfo, ListElem_t new_element);
size_t     list_insert_at_the_end             (LIST* listInfo, ListElem_t new_element);
ListElem_t list_return_element                (LIST* listInfo, size_t element_index);
LIST_ERROR list_remove_element                (LIST* listInfo, size_t remove_element_index);
size_t     list_add_element                   (LIST* listInfo, ListElem_t new_element, size_t new_element_index);
size_t     list_get_next                      (LIST* listInfo, size_t element_index);
size_t     list_get_previous                  (LIST* listInfo, size_t element_index);
size_t     list_find_element                  (LIST* listInfo, ListElem_t element);

#endif
