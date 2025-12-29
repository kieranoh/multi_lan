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

/* Giải nén nội dung của tệp tar đến đường dẫn đích đã cho.
Nếu việc giải nén thành công, trả về true; ngược lại, nếu có bất kỳ lỗi nào xảy ra trong quá trình giải nén (ví dụ: tệp không tìm thấy, lỗi quyền, không thể giải nén toàn bộ nội dung), chỉ cần trả về false.

Gợi ý: Mã sau đây cho thấy cách giải nén nội dung của tệp tar đến đường dẫn đích đã cho với thư viện libarchive.

@param tar_path: đường dẫn đến tệp tar
@param dest_path: đường dẫn đến thư mục đích

@return true nếu việc giải nén thành công; ngược lại, false */
bool extract_tar_to_path(const char *tar_path, const char *dest_path) {
    struct archive *src = NULL;
    struct archive *out = NULL;
    struct archive_entry *entry = NULL;
    int flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | 
                ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS;
    int r;
    char full_path[PATH_MAX];
    
    // Kiểm tra tham số đầu vào
    if (!tar_path || !dest_path) {
        return false;
    }
    
    // Kiểm tra xem thư mục đích có tồn tại không
    struct stat st;
    if (stat(dest_path, &st) != 0 || !S_ISDIR(st.st_mode)) {
        return false;
    }
    
    // Khởi tạo trình đọc archive
    src = archive_read_new();
    if (!src) {
        return false;
    }
    
    // Cấu hình trình đọc cho định dạng tar
    archive_read_support_format_tar(src);
    archive_read_support_filter_all(src);
    
    // Mở tệp tar
    r = archive_read_open_filename(src, tar_path, 10240);
    if (r != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }
    
    // Khởi tạo trình ghi archive
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }
    archive_write_disk_set_options(out, flags);
    archive_write_disk_set_standard_lookup(out);
    
    // Đọc và giải nén từng mục
    bool success = true;
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Tạo đường dẫn đầy đủ
        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path, archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);
        
        // Ghi tiêu đề
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            success = false;
            break;
        }
        
        // Sao chép dữ liệu
        const void *buff;
        size_t size;
        la_int64_t offset;
        while ((r = archive_read_data_block(src, &buff, &size, &offset)) == ARCHIVE_OK) {
            if (archive_write_data_block(out, buff, size, offset) != ARCHIVE_OK) {
                success = false;
                break;
            }
        }
        
        if (r != ARCHIVE_EOF) {
            success = false;
            break;
        }
        
        // Hoàn tất việc ghi tệp
        r = archive_write_finish_entry(out);
        if (r != ARCHIVE_OK) {
            success = false;
            break;
        }
    }
    
    // Kiểm tra lỗi đọc
    if (r != ARCHIVE_EOF && r != ARCHIVE_OK) {
        success = false;
    }
    
    // Giải phóng tài nguyên
    archive_read_free(src);
    archive_write_free(out);
    
    return success;
}