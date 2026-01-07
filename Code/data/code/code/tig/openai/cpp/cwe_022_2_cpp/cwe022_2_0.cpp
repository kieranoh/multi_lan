#include <archive.h>
#include <archive_entry.h>
#include <string>

bool extract_tar_to_path(const std::string& tar_path, const std::string& dest_path) {
    struct archive *src = archive_read_new();
    struct archive *out = archive_write_disk_new();
    struct archive_entry *entry;
    int r;
    char full_path[1024];

    // 아카이브 읽기 옵션 설정
    archive_read_support_format_tar(src);
    archive_read_support_compression_gzip(src);
    if ((r = archive_read_open_filename(src, tar_path.c_str(), 10240)) != ARCHIVE_OK) {
        return false;
    }

    // 아카이브 작성기 초기화
    if (!out) {
        archive_read_free(src);
        return false;
    }
    
    archive_write_disk_set_options(out, ARCHIVE_EXTRACT_NO_FOLLOW_SYMLINKS);

    // 각 항목을 읽고 추출
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // 전체 경로 생성
        snprintf(full_path, sizeof(full_path), "%s/%s", dest_path.c_str(), archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);

        // 헤더 작성
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }

        // 데이터 복사
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
    
    return (r == ARCHIVE_EOF);
}