#include <archive.h>
#include <archive_entry.h>
#include <string>
#include <cstring>
#include <sys/stat.h>

bool extract_tar_to_path(const std::string& tar_path, const std::string& dest_path) {
    struct archive *src = nullptr;
    struct archive *out = nullptr;
    struct archive_entry *entry = nullptr;
    int flags = 0;
    int r = 0;
    
    // إنشاء مجلد الوجهة إذا لم يكن موجودًا
    struct stat st;
    if (stat(dest_path.c_str(), &st) != 0) {
        // محاولة إنشاء المجلد
        #ifdef _WIN32
            mkdir(dest_path.c_str());
        #else
            mkdir(dest_path.c_str(), 0755);
        #endif
    }
    
    // قم بتهيئة قارئ الأرشيف
    src = archive_read_new();
    if (!src) {
        return false;
    }
    
    // دعم تنسيقات الأرشيف المختلفة
    archive_read_support_format_all(src);
    archive_read_support_filter_all(src);
    
    // قم بفتح ملف tar
    r = archive_read_open_filename(src, tar_path.c_str(), 10240);
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
        std::string full_path = dest_path + "/" + archive_entry_pathname(entry);
        archive_entry_set_pathname(entry, full_path.c_str());
        
        // اكتب الرأس
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
        
        // انسخ البيانات
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
        
        // أكمل كتابة الإدخال
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
    
    // تحقق من أننا وصلنا إلى نهاية الملف
    return (r == ARCHIVE_EOF);
}