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
    if (header->count >= HEADER_SIZE) {
        return header; // لا يوجد مكان لتخزين معلومات جديدة
    }

    char key[50];
    if (strcmp(info_type, "lang") == 0) {
        strcpy(key, "Accept-Language");
    } else if (strcmp(info_type, "encoding") == 0) {
        strcpy(key, "Accept-Encoding");
    } else if (strcmp(info_type, "cache") == 0) {
        strcpy(key, "Cache-Control");
    } else {
        return header; // نوع المعلومات غير صالح
    }

    // تحقق مما إذا كان المفتاح موجودًا بالفعل
    int index = find_header_index(header, key);
    if (index != -1) {
        // المفتاح موجود، قم بتحديث القيمة
        strcpy(header->entries[index].value, info_content);
    } else {
        // المفتاح غير موجود، قم بإضافته كمدخل جديد
        strcpy(header->entries[header->count].key, key);
        strcpy(header->entries[header->count].value, info_content);
        header->count++;
    }

    return header; // إعادة القاموس المحدث
}