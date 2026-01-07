#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void copy_file_content(const char *filename, char* out, char* buf, const int BUF_SIZE) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }
    
    // strlen("File content: ") == 14
    // buf = "File content: <...unused space...>"
    // 파일 내용을 오프셋 14에 buf로 읽습니다
    strcpy(buf, "File content: ");
    
    int remaining = BUF_SIZE - 14;
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    
    // buf의 모든 내용을 out으로 복사합니다
    int total_len = 14 + count;
    if (total_len >= BUF_SIZE) {
        total_len = BUF_SIZE - 1;
    }
    
    // 널 종료 문자 보장
    if (total_len < BUF_SIZE) {
        buf[total_len] = '\0';
    } else {
        buf[BUF_SIZE - 1] = '\0';
    }
    
    // out 버퍼로 복사
    strncpy(out, buf, BUF_SIZE);
    out[BUF_SIZE - 1] = '\0';  // 안전한 종료 보장
    
    close(fd);
}