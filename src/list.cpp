#include <assert.h>
#include <stdio.h>

#include "list_log.h"
#include "list.h"

LIST_ERROR list_ctor(LIST* listInfo, size_t capacity)
{
    assert(listInfo && "null pointer on listInfo in list_ctor\n");

    if (capacity == 0)
    {
        listInfo->error = LIST_INVALID_CAPACITY;

        return LIST_INVALID_CAPACITY;
    }

    listInfo->error    = LIST_NONE;
    listInfo->length   = StartListLength;
    listInfo->capacity = capacity;

    listInfo->head  = StartHeadCellIndex;
    listInfo->tail  = StartTailCellIndex;
    listInfo->free  = StartFreeCellIndex;

    listInfo->data     = (ListElem_t* ) calloc(listInfo->capacity + AccountDummyElement, sizeof(ListElem_t));
    listInfo->next     = (size_t* )     calloc(listInfo->capacity + AccountDummyElement, sizeof(size_t));
    listInfo->previous = (size_t* )     calloc(listInfo->capacity + AccountDummyElement, sizeof(size_t));

    listInfo->data     [DUMMY_ELEMENT] = LIST_POISON;
    listInfo->next     [DUMMY_ELEMENT] = 0;
    listInfo->previous [DUMMY_ELEMENT] = 0;

    for (size_t list_index = 1; list_index < listInfo->capacity - 1; list_index++)
    {
        listInfo->next[list_index] = list_index + NextOffset;
    }
    listInfo->next[listInfo->capacity - 1] = DUMMY_ELEMENT;

    for (size_t list_index = 1; list_index < listInfo->capacity; list_index++)
    {
        listInfo->previous[list_index] = LIST_POISON;
    }

    return LIST_NONE;
}

LIST_ERROR list_dtor(LIST* listInfo)
{
    assert(listInfo && "null pointer on listInfo in list_dtor\n");

    free(listInfo->data);
    free(listInfo->next);

    listInfo->data     = NULL;
    listInfo->next     = NULL;
    listInfo->previous = NULL;

    listInfo->length = 0;
    listInfo->free   = 0;
    listInfo->head   = 0;

    listInfo->error = LIST_NONE;

    return LIST_NONE;
}

LIST_ERROR list_verify(LIST* listInfo)
{
    if (!listInfo)
    {
        listInfo->error = LIST_ALLOCATION_ERROR;
    }
    if (!listInfo->data)
    {
        listInfo->error = LIST_DATA_ALLOCATION_ERROR;
    }
    if (!listInfo->next)
    {
        listInfo->error = LIST_NEXT_ELEMENT_ALLOCATION_ERROR;
    }

    return listInfo->error;
}

size_t list_return_head_index(LIST* listInfo)
{
    assert(listInfo && "null pointer on listInfo in list_return_head_index\n");

    return listInfo->head;
}

size_t list_return_tail_index(LIST* listInfo)
{
    assert(listInfo && "null pointer on listInfo in list_return_tail_index\n");

    return listInfo->tail;
}

size_t list_return_next_element_index(LIST* listInfo, size_t element_index)
{
    assert(listInfo && "null pointer on listInfo in list_return_next_index\n");

    return listInfo->next[element_index];
}

size_t list_return_previous_element_index(LIST* listInfo, size_t element_index)
{
    assert(listInfo && "null pointer on listInfo in list_return_previous_index\n");

    return listInfo->previous[element_index];
}

size_t list_insert_at_the_beginning(LIST* listInfo, ListElem_t new_element)
{
    assert(listInfo);

    return list_add_element(listInfo, new_element, listInfo->head);
}

size_t list_insert_at_the_end(LIST* listInfo, ListElem_t new_element)
{
    assert(listInfo);

    return list_add_element(listInfo, new_element, listInfo->next[listInfo->tail]);
}

ListElem_t list_return_element (LIST* listInfo, size_t element_index)
{
    assert(listInfo && "null pointer on listInfo in list_return_element\n");

    size_t list_element_index = DUMMY_ELEMENT;

    if (element_index > listInfo->length || element_index == DUMMY_ELEMENT)
    {
        listInfo->error = LIST_INVALID_ELEMENT_INDEX;

        return LIST_POISON;
    }

    return listInfo->data[element_index];
}

/* add element after element_index */
size_t list_add_element (LIST* listInfo, ListElem_t new_element, size_t element_index)
{
    assert(listInfo);

    if (element_index > listInfo->capacity || listInfo->length + 1 >= listInfo->capacity)
    {
        listInfo->error = LIST_INVALID_ELEMENT_INDEX;

        return LIST_POISON;
    }

    size_t old_free          = listInfo->free;
    listInfo->data[old_free] = new_element;

    if (listInfo->length == 1)
    {
        listInfo->next    [old_free] = DUMMY_ELEMENT;
        listInfo->previous[old_free] = DUMMY_ELEMENT;
        listInfo->next    [DUMMY_ELEMENT] = old_free;
        listInfo->previous[DUMMY_ELEMENT] = old_free;

        listInfo->head = old_free;
        listInfo->tail = old_free;

        listInfo->length++;
    }
    else
    {
        listInfo->next    [old_free]                          = element_index;
        listInfo->previous[old_free]                          = listInfo->previous[element_index];
        listInfo->next    [listInfo->previous[element_index]] = old_free;
        listInfo->previous[element_index]                     = old_free;
    }

    listInfo->head = listInfo->next    [DUMMY_ELEMENT];
    listInfo->tail = listInfo->previous[DUMMY_ELEMENT];

    listInfo->length++;

    return old_free;
}

LIST_ERROR list_remove_element (LIST* listInfo, size_t remove_element_index)
{
    assert(listInfo);

    if (remove_element_index > listInfo->length || remove_element_index == DUMMY_ELEMENT)
    {
        listInfo->error = LIST_INVALID_CAPACITY;

        return LIST_INVALID_CAPACITY;
    }

    if (listInfo->next[remove_element_index] == DUMMY_ELEMENT)
    {
        listInfo->tail = listInfo->previous[remove_element_index];
    }

    listInfo->data    [remove_element_index]                     = LIST_POISON;
    listInfo->next    [listInfo->previous[remove_element_index]] = listInfo->next[remove_element_index];
    listInfo->previous[listInfo->next[remove_element_index]]     = listInfo->previous[remove_element_index];

    size_t old_free = listInfo->free;

    listInfo->free                     = remove_element_index;
    listInfo->previous[listInfo->free] = listInfo->free;
    listInfo->next    [listInfo->free] = old_free;

    listInfo->head = listInfo->next[DUMMY_ELEMENT];
    listInfo->tail = listInfo->previous[DUMMY_ELEMENT];

    listInfo->length--;

    return LIST_NONE;
}

size_t list_get_next (LIST* listInfo, size_t element_index)
{
    assert(listInfo);

    if (element_index > listInfo->capacity)
    {
        listInfo->error = LIST_INVALID_ELEMENT_INDEX;

        return -1;
    }
    else
    {
        return listInfo->next[element_index];
    }
}

size_t list_get_previous (LIST* listInfo, size_t element_index)
{
    assert(listInfo);

    if (element_index > listInfo->capacity)
    {
        listInfo->error = LIST_INVALID_ELEMENT_INDEX;

        return -1;
    }
    else
    {
        return listInfo->previous[element_index];
    }
}

size_t list_find_element(LIST* listInfo, ListElem_t element)
{
    assert(listInfo);

    size_t tmp_index = listInfo->next[listInfo->head];

    for (size_t list_index = 0; list_index < listInfo->length - 1; list_index++)
    {
        if (element == listInfo->data[tmp_index])
        {
            return tmp_index;
        }
    }

    return 0;
}
