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
 * Giải nén nội dung của tệp tar đến đường dẫn đích đã cho.
 * Nếu việc giải nén thành công, trả về true; ngược lại, nếu có bất kỳ lỗi nào xảy ra trong quá trình giải nén (ví dụ: tệp không tìm thấy, lỗi quyền, không thể giải nén toàn bộ nội dung), chỉ cần trả về false.
 *
 * @param tar_path: đường dẫn đến tệp tar
 * @param dest_path: đường dẫn đến thư mục đích
 *
 * @return true nếu việc giải nén thành công; ngược lại, false
 */
bool extract_tar_to_path(const char *tar_path, const char *dest_path) {
    struct archive *src, *out;
    struct archive_entry *entry;
    int r;
    char full_path[PATH_MAX];

    // Mở tệp tar
    src = archive_read_new();
    if (archive_read_support_format_tar(src) != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }
    if (archive_read_open_filename(src, tar_path, 10240) != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }

    // Khởi tạo trình ghi archive
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }

    // Đọc và giải nén từng mục
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Tạo đường dẫn đầy đủ
        snprintf(full_path, sizeof(full_path), "%s/%s",
                 dest_path, archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);

        // Ghi tiêu đề
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }

        // Sao chép dữ liệu
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

    archive_write_free(out);
    archive_read_free(src);
    return r == ARCHIVE_EOF ? true : false;
}