#include "buffer.h"

BUFFER_ERROR buffer_init(BUFFER* bufferInfo)
{
    assert(bufferInfo && "null pointer on bufferInfo in asm_init_buffer\n");

    bufferInfo->argue   = 0;
    bufferInfo->ip      = 0;
    bufferInfo->buffer  = NULL;

    return BUFFER_NONE;;
}

BUFFER_ERROR buffer_set_size(BUFFER* bufferInfo, size_t length)
{
    assert(bufferInfo && "null pointer on bufferInfo in buffer_set_size\n");

    bufferInfo->buffer = (char* ) calloc(1, length);
    bufferInfo->length   = length;

    return BUFFER_NONE;
}

BUFFER_ERROR buffer_dump(BUFFER* bufferInfo)
{
    assert(bufferInfo && "null pointer on bufferInfo in buffer_dump\n");

    FILE* log_file = fopen("log/buffer_log_file.log", "wb");
    // FILE* log_file = stdout;
    if (!log_file)
    {
        printf("error error error in log_file opening\n");
    }

    fprintf(log_file, "Buffer dump   \n\n");
    fprintf(log_file, "Buffer length: %d \n", bufferInfo->ip);
    fprintf(log_file, "Buffer argue: %d\n", bufferInfo->argue);
    fprintf(log_file, "Buffer length: %d \n", bufferInfo->length);

    fprintf(log_file, "\nPrint buffer\n\n");
    fprintf(log_file, "\tbuffer cell\t\t\t  hex\t\t  bin\n");
    fprintf(log_file, "\t-------------------------------------\n");
    for (size_t buffer_element = 0; buffer_element < bufferInfo->length; buffer_element++)
    {
        fprintf(log_file, "\t| buffer[%3d] = %8x|", buffer_element, bufferInfo->buffer[buffer_element]);
        fprintf(log_file, "\t%8b|\n", bufferInfo->buffer[buffer_element]);
    }
    fprintf(log_file, "\t-------------------------------------\n");

    fprintf(log_file, "\nend buffer dump\n");

    fclose(log_file);

    return BUFFER_NONE;
}
