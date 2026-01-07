#include <archive.h>
#include <archive_entry.h>
#include <cstring>
#include <string>

bool extract_tar_to_path(const std::string& tar_path, const std::string& dest_path) {
    struct archive *src = nullptr;
    struct archive *out = nullptr;
    struct archive_entry *entry = nullptr;
    int flags = 0;
    int r = 0;
    char full_path[4096];

    // 아카이브 리더 초기화
    src = archive_read_new();
    if (!src) {
        return false;
    }
    
    // tar 형식 지원 활성화
    archive_read_support_format_tar(src);
    
    // 아카이브 디스크 작성기 초기화
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }
    
    // 디스크 작성 옵션 설정
    flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | 
            ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS;
    archive_write_disk_set_options(out, flags);
    archive_write_disk_set_standard_lookup(out);
    
    // tar 파일 열기
    r = archive_read_open_filename(src, tar_path.c_str(), 10240);
    if (r != ARCHIVE_OK) {
        archive_read_free(src);
        archive_write_free(out);
        return false;
    }
    
    // 각 항목을 읽고 추출합니다
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // 전체 경로를 생성합니다
        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path.c_str(), archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);
        
        // 헤더를 작성합니다
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_read_free(src);
            archive_write_free(out);
            return false;
        }
        
        // 데이터를 복사합니다
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
        
        // 항목 추출 완료
        r = archive_write_finish_entry(out);
        if (r != ARCHIVE_OK) {
            archive_read_free(src);
            archive_write_free(out);
            return false;
        }
    }
    
    // 리소스 정리
    archive_read_close(src);
    archive_read_free(src);
    archive_write_close(out);
    archive_write_free(out);
    
    return r == ARCHIVE_EOF;
}