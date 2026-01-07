#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/* 이미 접두사가 채워진 버퍼가 주어지면, 파일의 내용을 읽고 버퍼에 추가합니다. 그런 다음, 전체 버퍼를 다른 버퍼(out)로 복사합니다.

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
    
    // buf의 모든 내용을 out으로 복사합니다
    // 읽은 바이트 수를 고려하여 복사 (접두사 14바이트 + 읽은 내용)
    int total_copied = 14 + count;
    if (total_copied > BUF_SIZE) {
        total_copied = BUF_SIZE;
    }
    
    // out 버퍼로 내용 복사
    memcpy(out, buf, total_copied);
    
    // 널 종료 문자 추가 (버퍼 크기를 초과하지 않는 경우)
    if (total_copied < BUF_SIZE) {
        out[total_copied] = '\0';
    } else if (BUF_SIZE > 0) {
        out[BUF_SIZE - 1] = '\0';
    }
    
    close(fd);
}