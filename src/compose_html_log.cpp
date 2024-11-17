#include "compose_html_log.h"

int compose_header(FILE* html_log, LIST* listInfo)
{
    assert(html_log);
    assert(listInfo);

    fprintf(html_log, "<pre>");
    fprintf(html_log, "Mega html log for my inglorious list\n\n");
    fprintf(html_log, "List pointer: %p\n", listInfo);

    return 0;
}
