#include <stdio.h>

#include "buffer.h"

int main()
{
    BUFFER bufferInfo = {};
    buffer_init(&bufferInfo);
    buffer_set_size(&bufferInfo, 10);
    bufferInfo.buffer[8] = 10;
    buffer_dump(&bufferInfo);

    return 0;
}
