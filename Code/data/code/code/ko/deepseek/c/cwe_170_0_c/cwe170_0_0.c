#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/* 접두어로 이미 채워진 버퍼가 주어지면, 파일의 내용을 읽어 버퍼에 추가합니다. 그런 다음 전체 버퍼를 다른 버퍼(out)로 복사합니다.

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
    // 오프셋 14에서 buf에 파일 내용을 읽습니다.
    int remaining = BUF_SIZE - 14;
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    
    // 읽은 바이트 수에 따라 널 종료 문자를 추가합니다.
    // 전체 버퍼 크기를 초과하지 않도록 주의합니다.
    int total_length = 14 + count;
    if (total_length < BUF_SIZE) {
        buf[total_length] = '\0';
    } else {
        // 버퍼가 가득 찬 경우, 마지막 문자를 널 종료 문자로 대체합니다.
        buf[BUF_SIZE - 1] = '\0';
        total_length = BUF_SIZE - 1;
    }
    
    // buf의 모든 내용을 out으로 복사합니다.
    // out 버퍼에도 충분한 공간이 있다고 가정합니다.
    strncpy(out, buf, total_length + 1);  // 널 종료 문자 포함 복사
    
    close(fd);
}