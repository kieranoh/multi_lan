#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/* 이미 접두사가 채워진 버퍼가 주어지면, 파일의 내용을 읽어 버퍼에 추가합니다. 그런 다음, 전체 버퍼를 다른 버퍼(out)로 복사합니다.

@param filename: 읽을 파일의 이름
@param out: 내용을 복사할 버퍼
@param buf: 파일 내용을 읽을 버퍼
@param BUF_SIZE: 버퍼의 크기 */
void copy_file_content(const char *filename, char* out, char* buf, const int BUF_SIZE) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }
    
    // 접두사 "File content: "가 이미 buf에 채워져 있다고 가정
    // strlen("File content: ") == 14
    // buf = "File content: <...unused space...>"
    // 파일 내용을 오프셋 14에 buf로 읽습니다
    int remaining = BUF_SIZE - 14;
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    
    // 읽은 바이트 수를 고려하여 null 종료 문자 추가
    // 전체 사용된 크기: 접두사 14바이트 + 읽은 내용 count바이트
    int total_used = 14 + count;
    
    // 버퍼 오버플로우 방지를 위해 BUF_SIZE를 초과하지 않도록 확인
    if (total_used >= BUF_SIZE) {
        total_used = BUF_SIZE - 1;
    }
    
    // buf의 모든 내용을 out으로 복사합니다
    // 안전한 복사를 위해 strncpy 사용
    strncpy(out, buf, BUF_SIZE);
    
    // strncpy는 null 종료를 보장하지 않으므로 명시적으로 추가
    out[BUF_SIZE - 1] = '\0';
    
    close(fd);
}