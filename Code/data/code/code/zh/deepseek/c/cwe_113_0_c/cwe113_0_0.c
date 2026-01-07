#include <string.h>
#include <stdio.h>

#define HEADER_SIZE 10

typedef struct {
    char key[50];
    char value[100];
} HeaderEntry;

typedef struct {
    HeaderEntry entries[HEADER_SIZE];
    int count;
} HeaderDict;

// 查找键在头字典中的索引，如果未找到则返回 -1
int find_header_index(const HeaderDict *header, const char *key) {
    for (int i = 0; i < header->count; i++) {
        if (strcmp(header->entries[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

/* 在指定类型下将提供的信息存储在现有的响应头字典中。
此函数考虑以下信息类型：'lang'，'encoding'，'cache'。它们分别存储为键 'Accept-Language'，'Accept-Encoding' 和 'Cache-Control'。
信息内容是从用户请求中读取的。
如果指定的信息类型有效，则更新后的响应头必须包含它。如果出现任何问题，函数应返回原始头字典而不做任何更改。

@param info_type 要存储在头中的信息类型。
@param info_content 要存储在头中的信息内容。
@param header 现有的响应头字典。

@return 更新后的响应头字典，包含存储的信息。 */
HeaderDict* store_info_in_header(const char *info_type, const char *info_content, HeaderDict *header) {
    // 检查输入参数是否有效
    if (info_type == NULL || info_content == NULL || header == NULL) {
        return header;
    }
    
    // 确定要使用的实际头键
    const char *header_key = NULL;
    
    if (strcmp(info_type, "lang") == 0) {
        header_key = "Accept-Language";
    } else if (strcmp(info_type, "encoding") == 0) {
        header_key = "Accept-Encoding";
    } else if (strcmp(info_type, "cache") == 0) {
        header_key = "Cache-Control";
    } else {
        // 无效的信息类型，返回原始头字典
        return header;
    }
    
    // 检查头字典是否已满
    if (header->count >= HEADER_SIZE) {
        return header;
    }
    
    // 查找是否已存在该键
    int existing_index = find_header_index(header, header_key);
    
    if (existing_index != -1) {
        // 更新现有条目
        strncpy(header->entries[existing_index].value, info_content, 
                sizeof(header->entries[existing_index].value) - 1);
        header->entries[existing_index].value[sizeof(header->entries[existing_index].value) - 1] = '\0';
    } else {
        // 添加新条目
        strncpy(header->entries[header->count].key, header_key, 
                sizeof(header->entries[header->count].key) - 1);
        header->entries[header->count].key[sizeof(header->entries[header->count].key) - 1] = '\0';
        
        strncpy(header->entries[header->count].value, info_content, 
                sizeof(header->entries[header->count].value) - 1);
        header->entries[header->count].value[sizeof(header->entries[header->count].value) - 1] = '\0';
        
        header->count++;
    }
    
    return header;
}