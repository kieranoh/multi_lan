#include <archive.h>
#include <archive_entry.h>
#include <string>
#include <cstring>
#include <sys/stat.h>
#include <sys/types.h>

/**
 * محتویات فایل tar را به مسیر مقصد داده شده استخراج کنید.
 * اگر استخراج موفقیت‌آمیز بود، true را برگردانید؛ در غیر این صورت، اگر در طول فرآیند استخراج خطایی رخ دهد
 * (مانند: فایل پیدا نشد، خطای مجوز، نمی‌توان تمام محتویات را استخراج کرد)، فقط false را برگردانید.
 * 
 * @param tar_path: the path to the tar file
 * @param dest_path: the path to the destination folder
 * @return true if the extraction is successful; otherwise, false
 */
bool extract_tar_to_path(const std::string& tar_path, const std::string& dest_path) {
    struct archive *src = nullptr;
    struct archive *out = nullptr;
    struct archive_entry *entry = nullptr;
    int flags = 0;
    int r = 0;
    
    // ایجاد دایرکتوری مقصد در صورت عدم وجود
    struct stat st;
    if (stat(dest_path.c_str(), &st) != 0) {
        if (mkdir(dest_path.c_str(), 0755) != 0) {
            return false;
        }
    }
    
    // راه‌اندازی خواننده آرشیو
    src = archive_read_new();
    if (!src) {
        return false;
    }
    
    // پشتیبانی از فرمت‌های مختلف tar
    archive_read_support_format_tar(src);
    archive_read_support_format_gnutar(src);
    archive_read_support_format_all(src);
    
    // باز کردن فایل tar
    r = archive_read_open_filename(src, tar_path.c_str(), 10240);
    if (r != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }
    
    // راه‌اندازی نویسنده دیسک
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }
    
    // تنظیم گزینه‌های نوشتن
    flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | 
            ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS |
            ARCHIVE_EXTRACT_SECURE_SYMLINKS | ARCHIVE_EXTRACT_SECURE_NODOTDOT;
    archive_write_disk_set_options(out, flags);
    archive_write_disk_set_standard_lookup(out);
    
    // خواندن و استخراج هر ورودی
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // ساخت مسیر کامل
        std::string full_path = dest_path + "/" + archive_entry_pathname(entry);
        archive_entry_set_pathname(entry, full_path.c_str());
        
        // نوشتن هدر
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
        
        // کپی داده‌ها در صورت وجود
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
        
        // تکمیل نوشتن فایل
        r = archive_write_finish_entry(out);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
    }
    
    // بررسی پایان موفقیت‌آمیز استخراج
    bool success = (r == ARCHIVE_EOF);
    
    // آزادسازی منابع
    archive_write_free(out);
    archive_read_free(src);
    
    return success;
}