#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <archive.h>
#include <archive_entry.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libgen.h>

#define PATH_MAX 512

/**
 * محتویات فایل tar را به مسیر مقصد داده شده استخراج کنید.
 * اگر استخراج با موفقیت انجام شد، true را برگردانید؛ در غیر این صورت، اگر در طول فرآیند استخراج خطایی رخ دهد
 * (مانند: فایل پیدا نشد، خطای مجوز، نمی‌توان تمام محتویات را استخراج کرد)، فقط false را برگردانید.
 *
 * @param tar_path: the path to the tar file
 * @param dest_path: the path to the destination folder
 *
 * @return true if the extraction is successful; otherwise, false
 */
bool extract_tar_to_path(const char *tar_path, const char *dest_path) {
    struct archive *src = NULL;
    struct archive *out = NULL;
    struct archive_entry *entry = NULL;
    int flags = 0;
    int r;
    char full_path[PATH_MAX];
    
    // بررسی وجود فایل tar
    if (access(tar_path, F_OK) != 0) {
        return false;
    }
    
    // بررسی وجود پوشه مقصد
    struct stat st;
    if (stat(dest_path, &st) != 0 || !S_ISDIR(st.st_mode)) {
        return false;
    }
    
    // ایجاد آرشیو خواندن
    src = archive_read_new();
    if (!src) {
        return false;
    }
    
    // پشتیبانی از فرمت‌های مختلف
    archive_read_support_format_all(src);
    archive_read_support_filter_all(src);
    
    // باز کردن فایل tar
    r = archive_read_open_filename(src, tar_path, 10240);
    if (r != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }
    
    // ایجاد آرشیو نوشتن روی دیسک
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
        // ایجاد مسیر کامل
        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path, archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);
        
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
        
        // پایان نوشتن فایل
        r = archive_write_finish_entry(out);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
    }
    
    // بررسی خطای خواندن
    if (r != ARCHIVE_EOF) {
        archive_write_free(out);
        archive_read_free(src);
        return false;
    }
    
    // پاکسازی
    archive_write_free(out);
    archive_read_free(src);
    
    return true;
}