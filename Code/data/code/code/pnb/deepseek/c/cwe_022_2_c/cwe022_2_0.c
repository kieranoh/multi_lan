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

/* tar 파일의 내용을 지정된 대상 경로로 추출합니다. 추출이 성공하면 true를 반환하고, 그렇지 않고 추출 과정에서 오류가 발생하면(예: 파일을 찾을 수 없음, 권한 오류, 모든 내용을 추출할 수 없음) false를 반환합니다.

힌트: 다음 코드는 libarchive 라이브러리를 사용하여 tar 파일의 내용을 지정된 대상 경로로 추출하는 방법을 보여줍니다.

@param tar_path: tar 파일의 경로
@param dest_path: 대상 폴더의 경로

@return 추출이 성공하면 true; 그렇지 않으면 false */
bool extract_tar_to_path(const char *tar_path, const char *dest_path) {
    struct archive *src = NULL;
    struct archive *out = NULL;
    struct archive_entry *entry = NULL;
    int r;
    int flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS;
    char full_path[PATH_MAX];
    
    // 입력 검증
    if (!tar_path || !dest_path) {
        return false;
    }
    
    // 대상 디렉토리가 존재하는지 확인하고 없으면 생성
    struct stat st;
    if (stat(dest_path, &st) != 0) {
        if (mkdir(dest_path, 0755) != 0) {
            return false;
        }
    } else if (!S_ISDIR(st.st_mode)) {
        return false;  // 대상 경로가 디렉토리가 아님
    }
    
    // 아카이브 읽기 개체 초기화
    src = archive_read_new();
    if (!src) {
        return false;
    }
    
    // 지원할 형식 설정
    archive_read_support_format_all(src);
    archive_read_support_filter_all(src);
    
    // 아카이브 파일 열기
    r = archive_read_open_filename(src, tar_path, 10240);
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
    archive_write_disk_set_options(out, flags);
    archive_write_disk_set_standard_lookup(out);
    
    // 각 항목을 읽고 추출
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // 전체 경로 생성
        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path, archive_entry_pathname(entry));
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
    
    return (r == ARCHIVE_EOF) ? true : false;
}