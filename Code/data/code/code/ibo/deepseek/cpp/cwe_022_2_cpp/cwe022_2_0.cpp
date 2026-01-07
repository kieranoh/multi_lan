#include <archive.h>
#include <archive_entry.h>
#include <string>
#include <cstdio>
#include <cstring>

bool extract_tar_to_path(const std::string& tar_path, const std::string& dest_path) {
    struct archive *src = nullptr;
    struct archive *out = nullptr;
    struct archive_entry *entry = nullptr;
    int r;
    constexpr int flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM |
                          ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS;

    // 아카이브 읽기 개체 초기화
    src = archive_read_new();
    if (!src) {
        return false;
    }
    archive_read_support_format_all(src);
    archive_read_support_filter_all(src);

    // 아카이브 쓰기 개체 초기화
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }
    archive_write_disk_set_options(out, flags);
    archive_write_disk_set_standard_lookup(out);

    // tar 파일 열기
    r = archive_read_open_filename(src, tar_path.c_str(), 10240);
    if (r != ARCHIVE_OK) {
        archive_read_free(src);
        archive_write_free(out);
        return false;
    }

    // 각 항목을 읽고 추출
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // 전체 경로 생성
        std::string full_path = dest_path + "/" + archive_entry_pathname(entry);
        archive_entry_set_pathname(entry, full_path.c_str());

        // 헤더 작성
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_read_free(src);
            archive_write_free(out);
            return false;
        }

        // 데이터 복사
        if (archive_entry_size(entry) > 0) {
            const void *buff;
            size_t size;
            la_int64_t offset;
            while ((r = archive_read_data_block(src, &buff, &size, &offset)) == ARCHIVE_OK) {
                if (archive_write_data_block(out, buff, size, offset) != ARCHIVE_OK) {
                    archive_read_free(src);
                    archive_write_free(out);
                    return false;
                }
            }
            if (r != ARCHIVE_EOF) {
                archive_read_free(src);
                archive_write_free(out);
                return false;
            }
        }

        // 항목 완료
        r = archive_write_finish_entry(out);
        if (r != ARCHIVE_OK) {
            archive_read_free(src);
            archive_write_free(out);
            return false;
        }
    }

    // 정리
    archive_read_close(src);
    archive_read_free(src);
    archive_write_close(out);
    archive_write_free(out);

    return r == ARCHIVE_EOF;
}