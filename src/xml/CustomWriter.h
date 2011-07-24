/**
 * @file  CustomWriter.h
 * @brief
 * @version
 * @author
 * @date    2011年7月22日
 */

#ifndef _CUSTOM_WRITER_H_
#define _CUSTOM_WRITER_H_

#include <pugixml/pugixml.hpp>
#include <string>
#include <string.h>
#include <stdio.h>

//[code_save_custom_writer
struct xml_string_writer: pugi::xml_writer
{
    std::string result;

    virtual void write(const void* data, size_t size)
    {
        result += std::string(static_cast<const char*>(data), size);
    }
};
//]

struct xml_memory_writer: pugi::xml_writer
{
    char* buffer;
    size_t capacity;

    size_t result;

    xml_memory_writer(): buffer(0), capacity(0), result(0)
    {
    }

    xml_memory_writer(char* buffer, size_t capacity): buffer(buffer), capacity(capacity), result(0)
    {
    }

    size_t written_size() const
    {
        return result < capacity ? result : capacity;
    }

    virtual void write(const void* data, size_t size)
    {
        if (result < capacity)
        {
            size_t chunk = (capacity - result < size) ? capacity - result : size;

            memcpy(buffer + result, data, chunk);
        }

        result += size;
    }
};

std::string node_to_string(pugi::xml_node node);
int node_to_buffer(pugi::xml_node node, char* buffer, size_t size);
char* node_to_buffer_heap(pugi::xml_node node);

pugi::xml_node XmlMessagePrepare(int n);
#endif /* _CUSTOM_WRITER_H_ */
