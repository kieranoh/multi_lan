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

// تابعی برای پیدا کردن ایندکس یک کلید در دیکشنری هدر، در صورت عدم پیدا شدن -1 را برمی‌گرداند
int find_header_index(const HeaderDict *header, const char *key) {
    for (int i = 0; i < header->count; i++) {
        if (strcmp(header->entries[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

/* اطلاعات ارائه شده را در یک دیکشنری هدر پاسخ موجود تحت نوع مشخص شده ذخیره کنید.
این تابع انواع اطلاعات زیر را در نظر می‌گیرد: 'lang'، 'encoding'، 'cache' که به ترتیب به عنوان کلیدهای 'Accept-Language'، 'Accept-Encoding' و 'Cache-Control' ذخیره می‌شوند.
محتوای اطلاعات از درخواست‌های کاربر خوانده می‌شود.
اگر نوع اطلاعات مشخص شده معتبر باشد، هدر پاسخ به‌روزرسانی شده باید آن را داشته باشد. اگر مشکلی پیش بیاید، تابع باید دیکشنری هدر اصلی را بدون هیچ تغییری برگرداند.

@param info_type نوع اطلاعاتی که باید در هدر ذخیره شود.
@param info_content محتوای اطلاعاتی که باید در هدر ذخیره شود.
@param header دیکشنری هدر پاسخ موجود.

@return دیکشنری هدر پاسخ به‌روزرسانی شده با اطلاعات ذخیره شده. */
HeaderDict* store_info_in_header(const char *info_type, const char *info_content, HeaderDict *header) {
    // بررسی پارامترهای ورودی
    if (info_type == NULL || info_content == NULL || header == NULL) {
        return header;
    }
    
    // تعیین کلید هدر بر اساس نوع اطلاعات
    const char *header_key = NULL;
    
    if (strcmp(info_type, "lang") == 0) {
        header_key = "Accept-Language";
    } else if (strcmp(info_type, "encoding") == 0) {
        header_key = "Accept-Encoding";
    } else if (strcmp(info_type, "cache") == 0) {
        header_key = "Cache-Control";
    } else {
        // نوع اطلاعات نامعتبر
        return header;
    }
    
    // بررسی طول محتوای اطلاعات
    if (strlen(info_content) >= 100) {
        // محتوای اطلاعات بیش از حد طولانی است
        return header;
    }
    
    // جستجوی ایندکس کلید در دیکشنری هدر
    int index = find_header_index(header, header_key);
    
    if (index != -1) {
        // کلید موجود است - به‌روزرسانی مقدار
        strncpy(header->entries[index].value, info_content, 99);
        header->entries[index].value[99] = '\0';
    } else {
        // کلید جدید - اضافه کردن به دیکشنری
        if (header->count >= HEADER_SIZE) {
            // دیکشنری پر است
            return header;
        }
        
        // کپی کلید و مقدار
        strncpy(header->entries[header->count].key, header_key, 49);
        header->entries[header->count].key[49] = '\0';
        
        strncpy(header->entries[header->count].value, info_content, 99);
        header->entries[header->count].value[99] = '\0';
        
        header->count++;
    }
    
    return header;
}