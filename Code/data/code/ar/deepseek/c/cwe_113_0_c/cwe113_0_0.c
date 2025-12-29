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

// دالة للعثور على فهرس مفتاح في قاموس الرأس، تعيد -1 إذا لم يتم العثور عليه
int find_header_index(const HeaderDict *header, const char *key) {
    for (int i = 0; i < header->count; i++) {
        if (strcmp(header->entries[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

/* قم بتخزين المعلومات المقدمة في قاموس رأس الاستجابة الحالي تحت النوع المحدد. تعتبر هذه الدالة أنواع المعلومات التالية: 'lang'، 'encoding'، 'cache'. يتم تخزينها كمفاتيح 'Accept-Language'، 'Accept-Encoding'، و 'Cache-Control'، على التوالي. يتم قراءة محتوى المعلومات من طلبات المستخدم. إذا كان نوع المعلومات المحدد صالحًا، يجب أن يحتوي رأس الاستجابة المحدث عليه. إذا حدث أي خطأ، يجب أن تعيد الدالة قاموس الرأس الأصلي دون أي تغييرات.

@param info_type نوع المعلومات لتخزينها في الرأس.
@param info_content محتوى المعلومات لتخزينها في الرأس.
@param header قاموس رأس الاستجابة الحالي.

@return قاموس رأس الاستجابة المحدث مع المعلومات المخزنة. */
HeaderDict* store_info_in_header(const char *info_type, const char *info_content, HeaderDict *header) {
    // التحقق من المؤشرات
    if (info_type == NULL || info_content == NULL || header == NULL) {
        return header;
    }
    
    // تحديد مفتاح الرأس بناءً على نوع المعلومات
    const char *header_key = NULL;
    
    if (strcmp(info_type, "lang") == 0) {
        header_key = "Accept-Language";
    } else if (strcmp(info_type, "encoding") == 0) {
        header_key = "Accept-Encoding";
    } else if (strcmp(info_type, "cache") == 0) {
        header_key = "Cache-Control";
    } else {
        // نوع المعلومات غير صالح
        return header;
    }
    
    // التحقق من طول المحتوى
    if (strlen(info_content) >= 100) {
        return header;
    }
    
    // البحث عن المفتاح في القاموس
    int index = find_header_index(header, header_key);
    
    if (index != -1) {
        // المفتاح موجود، تحديث القيمة
        strncpy(header->entries[index].value, info_content, 99);
        header->entries[index].value[99] = '\0';
    } else {
        // المفتاح غير موجود، إضافة إدخال جديد
        if (header->count >= HEADER_SIZE) {
            // القاموس ممتلئ
            return header;
        }
        
        // إضافة الإدخال الجديد
        strncpy(header->entries[header->count].key, header_key, 49);
        header->entries[header->count].key[49] = '\0';
        
        strncpy(header->entries[header->count].value, info_content, 99);
        header->entries[header->count].value[99] = '\0';
        
        header->count++;
    }
    
    return header;
}