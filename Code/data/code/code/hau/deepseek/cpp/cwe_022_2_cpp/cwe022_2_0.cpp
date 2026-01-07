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
    
    // 대상 디렉토리 생성 (존재하지 않는 경우)
    struct stat st;
    if (stat(dest_path.c_str(), &st) != 0) {
        mkdir(dest_path.c_str(), 0755);
    }
    
    // 아카이브 읽기 객체 초기화
    src = archive_read_new();
    if (!src) {
        return false;
    }
    
    // tar 형식 지원 설정
    archive_read_support_format_tar(src);
    archive_read_support_filter_all(src);
    
    // tar 파일 열기
    r = archive_read_open_filename(src, tar_path.c_str(), 10240);
    if (r != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }
    
    // 아카이브 작성기 초기화
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }
    
    // 디스크 쓰기 옵션 설정
    flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | 
            ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS |
            ARCHIVE_EXTRACT_SECURE_SYMLINKS | ARCHIVE_EXTRACT_SECURE_NODOTDOT;
    archive_write_disk_set_options(out, flags);
    archive_write_disk_set_standard_lookup(out);
    
    // 각 항목을 읽고 추출
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // 전체 경로 생성
        std::string full_path = dest_path + "/" + archive_entry_pathname(entry);
        archive_entry_set_pathname(entry, full_path.c_str());
        
        // 헤더 작성
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
        
        // 데이터 복사 (일반 파일인 경우)
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
        
        // 항목 완료
        r = archive_write_finish_entry(out);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
    }
    
    // 정리
    archive_write_free(out);
    archive_read_free(src);
    
    // 성공 여부 반환
    return (r == ARCHIVE_EOF);
}