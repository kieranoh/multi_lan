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
    
    // "File content: " 문자열을 버퍼 시작 부분에 복사
    strcpy(buf, "File content: ");
    
    // 남은 공간 계산 (널 종결자를 위한 공간 포함)
    int remaining = BUF_SIZE - 15;  // 14바이트 문자열 + 1바이트 널 종결자
    
    if (remaining > 0) {
        int count = read(fd, buf + 14, remaining);
        if (count < 0) {
            perror("Error reading file");
            close(fd);
            return;
        }
        
        // 읽은 데이터 다음에 널 종결자 추가
        if (count < remaining) {
            buf[14 + count] = '\0';
        } else {
            // 버퍼가 가득 찬 경우 마지막 바이트를 널 종결자로 설정
            buf[BUF_SIZE - 1] = '\0';
        }
    } else {
        // 버퍼가 너무 작은 경우
        buf[14] = '\0';
    }
    
    close(fd);
    
    // buf의 모든 내용을 out으로 복사
    strcpy(out, buf);
}