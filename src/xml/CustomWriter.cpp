#include "CustomWriter.h"

std::string node_to_string(pugi::xml_node node)
{
    xml_string_writer writer;
    node.print(writer);

    return writer.result;
}

int node_to_buffer(pugi::xml_node node, char* buffer, size_t size)
{
    if (size == 0) return 0;

    // leave one character for null terminator
    xml_memory_writer writer(buffer, size - 1);
    node.print(writer);

    // null terminate
    buffer[writer.written_size()] = 0;

    return writer.written_size();
}

char* node_to_buffer_heap(pugi::xml_node node)
{
    // first pass: get required memory size
    xml_memory_writer counter;
    node.print(counter);

    // allocate necessary size (+1 for null termination)
    char* buffer = new char[counter.result + 1];

    // second pass: actual printing
    xml_memory_writer writer(buffer, counter.result);
    node.print(writer);

    // null terminate
    buffer[writer.written_size()] = 0;

    return buffer;
}