#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <archive.h>
#include <archive_entry.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libgen.h>
#include <errno.h>

#define PATH_MAX 512

/* استخرج محتوى ملف tar إلى مسار الوجهة المحدد.
إذا كانت عملية الاستخراج ناجحة، ارجع true؛ خلاف ذلك، إذا حدث أي خطأ أثناء عملية الاستخراج (مثل: الملف غير موجود، خطأ في الأذونات، لا يمكن استخراج كل المحتوى)، فقط ارجع false.

تلميح: الكود التالي يوضح كيفية استخراج محتوى ملف tar إلى مسار الوجهة المحدد باستخدام مكتبة libarchive. */// قم بتهيئة كاتب الأرشيف    out = archive_write_disk_new();
    if (!out) {
        return false;
    }
    archive_write_disk_set_options(out, flags);
// اقرأ واستخرج كل إدخال    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // أنشئ المسار الكامل        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path, archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);
// اكتب الرأس        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            return false;
        }
// انسخ البيانات        const void *buff;
        size_t size;
        la_int64_t offset;
        while ((r = archive_read_data_block(src, &buff, &size, &offset)) == ARCHIVE_OK) {
            if (archive_write_data_block(out, buff, size, offset) != ARCHIVE_OK) {
                archive_write_free(out);
                return false;
            }
        }
        if (r != ARCHIVE_EOF) {
            archive_write_free(out);
            return false;
        }
    }

    archive_write_free(out);
    return r == ARCHIVE_EOF ? true : false;
}


@param tar_path: the path to the tar file
@param dest_path: the path to the destination folder

@return true if the extraction is successful; otherwise, false
*/
bool extract_tar_to_path(const char *tar_path, const char *dest_path) {
    struct archive *src = NULL;
    struct archive *out = NULL;
    struct archive_entry *entry = NULL;
    int flags = 0;
    int r;
    char full_path[PATH_MAX];
    struct stat st;

    // التحقق من وجود ملف الأرشيف
    if (access(tar_path, F_OK) != 0) {
        return false;
    }

    // التحقق من وجود مجلد الوجهة أو إنشاؤه
    if (stat(dest_path, &st) != 0) {
        if (mkdir(dest_path, 0755) != 0) {
            return false;
        }
    } else if (!S_ISDIR(st.st_mode)) {
        return false;  // المسار ليس مجلدًا
    }

    // تهيئة قارئ الأرشيف
    src = archive_read_new();
    if (!src) {
        return false;
    }
    
    // دعم تنسيقات الأرشيف المختلفة
    archive_read_support_format_all(src);
    archive_read_support_filter_all(src);

    // فتح ملف الأرشيف
    r = archive_read_open_filename(src, tar_path, 10240);
    if (r != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }

    // قم بتهيئة كاتب الأرشيف
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }
    
    // تعيين خيارات الكتابة على القرص
    flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | 
            ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS |
            ARCHIVE_EXTRACT_SECURE_SYMLINKS | ARCHIVE_EXTRACT_SECURE_NODOTDOT;
    archive_write_disk_set_options(out, flags);
    archive_write_disk_set_standard_lookup(out);

    // اقرأ واستخرج كل إدخال
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // أنشئ المسار الكامل
        const char *entry_path = archive_entry_pathname(entry);
        if (!entry_path) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }

        // التحقق من المسار الآمن
        if (strstr(entry_path, "..") != NULL) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }

        snprintf(full_path, sizeof(full_path), "%s/%s", dest_path, entry_path);
        archive_entry_set_pathname(entry, full_path);

        // اكتب الرأس
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }

        // انسخ البيانات إذا كان الملف يحتوي على بيانات
        if (archive_entry_size(entry) > 0) {
            const void *buff;
            size_t size;
            la_int64_t offset;
            
            while ((r = archive_read_data_block(src, &buff, &size, &offset)) == ARCHIVE_OK) {
                if (archive_write_data_block(out, buff, size, offset) != ARCHIVE_OK) {
                    archive_write_free(out);
                    archive_read_free(src);
                    return false;
                }
            }
            
            if (r != ARCHIVE_EOF) {
                archive_write_free(out);
                archive_read_free(src);
                return false;
            }
        }

        // إنهاء كتابة الإدخال الحالي
        r = archive_write_finish_entry(out);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
    }

    // تنظيف الموارد
    archive_write_free(out);
    archive_read_free(src);

    // التحقق من أن القراءة انتهت بشكل طبيعي
    return (r == ARCHIVE_EOF) ? true : false;
}