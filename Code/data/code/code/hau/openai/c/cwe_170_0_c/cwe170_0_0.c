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

    // Set the prefix in the buffer
    const char* prefix = "File content: ";
    size_t prefix_len = strlen(prefix);
    memcpy(buf, prefix, prefix_len);

    // Prepare to read file content into buffer, starting after the prefix
    int remaining = BUF_SIZE - prefix_len;
    int count = read(fd, buf + prefix_len, remaining);

    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }

    // Null-terminate the buffer to make it a valid string
    buf[prefix_len + count] = '\0';

    // Copy the entire buffer to the output buffer
    memcpy(out, buf, BUF_SIZE);

    // Close the file descriptor
    close(fd);
}