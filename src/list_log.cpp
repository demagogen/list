#include "list_log.h"

int compose_dotfile(LIST* listInfo)
{
    assert(listInfo);

    FILE* dotfile = fopen("log/dotfile.gv", "wb");

    fprintf(dotfile, "digraph G                         \n"
                     "{bgcolor=\"#696969\" rankdir = TB \n"
                     "splines = ortho;                  \n"
                     "edge[minlen = 3,                  \n"
                     "penwidth = 2;                     \n"
                     "color = blue];                  \n\n");

    fprintf(dotfile, "Info[shape=record,     \n"
                     "fillcolor=\"grey\",    \n"
                     "width=0.2,             \n"
                     "style=\"filled\",      \n"
                     "label=\" {Capacity: %d \n"
                     "| Size: %d             \n"
                     "| Free: %d             \n"
                     "| Front: %d            \n"
                     "| Back: %d}\"]       \n\n",
                     listInfo->capacity,
                     listInfo->length,
                     listInfo->free,
                     listInfo->head,
                     listInfo->tail);

    fprintf(dotfile, "{rank = max;         \n"
                     "node0[shape=record,  \n"
                     "width=0.2,           \n"
                     "style=\"filled\",    \n"
                     "fillcolor=\"pink\"   \n"
                     ",label=\"            \n"
                     "{id: ЗИРО            \n"
                     "| value: НУЛЛ        \n"
                     "| next: %d           \n"
                     "| prev: %d}\"]}    \n\n",
                     listInfo->next    [DUMMY_ELEMENT],
                     listInfo->previous[DUMMY_ELEMENT]);

    fprintf(dotfile, "{rank = same;\n");

    for (size_t index = 1; index < listInfo->capacity; index++)
    {
        if (listInfo->previous[index] == LIST_POISON)
        {
            fprintf(dotfile, "node%d[shape=record,         \n"
                             "width=0.2, style=\"filled\", \n"
                             "fillcolor=\"grey\",           \n"
                             "label=\" {id: %d             \n"
                             "| value: %s                  \n"
                             "| next: %d                   \n"
                             "| prev: %d}\"]             \n\n",
                             index,
                             index,
                             "POISON",
                             listInfo->next    [index],
                             listInfo->previous[index]);
        }
        else
        {
            fprintf(dotfile, "node%d[shape=record, \n"
                             "width=0.2,           \n"
                             "style=\"filled\",    \n"
                             "fillcolor=\"green\", \n"
                             "label=\" {id: %d     \n"
                             "| value: %d          \n"
                             "| next: %d           \n"
                             "| prev: %d}\"]     \n\n",
                             index,
                             index,
                             listInfo->data    [index],
                             listInfo->next    [index],
                             listInfo->previous[index]);
        }
    }

    fprintf(dotfile, "}\n");

    fprintf(dotfile, "Free[color=orange,  style=filled]");
    fprintf(dotfile, "Front[color=orange, style=filled]");
    fprintf(dotfile, "Back[color=orange,  style=filled]");
    fprintf(dotfile, "Free->node%d\n",    listInfo->free);
    fprintf(dotfile, "Front->node%d\n",   listInfo->head);
    fprintf(dotfile, "Back->node%d\n\n",  listInfo->tail);
    fprintf(dotfile, "edge[color=darkgreen, constraint = true]\n");

    fprintf(dotfile, "\n}");

    fclose(dotfile);

    return 0;
}
