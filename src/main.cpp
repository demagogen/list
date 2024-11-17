#include <stdio.h>

#include "list.h"
#include "buffer.h"
#include "list_log.h"
#include "compose_html_log.h"

int main()
{
    LIST listInfo = {};
    list_ctor(&listInfo, 10);

    printf("next dummy = %d\n", listInfo.next[DUMMY_ELEMENT]);
    printf("previous dummy = %d\n", listInfo.previous[DUMMY_ELEMENT]);

    list_add_element(&listInfo, 1200, 2);
    list_add_element(&listInfo, 1300, 3);
    list_insert_at_the_beginning(&listInfo, 2000);

    printf("listInfo->data[1] = %d\n", listInfo.data[1]);

    compose_dotfile(&listInfo);

    return 0;
}
