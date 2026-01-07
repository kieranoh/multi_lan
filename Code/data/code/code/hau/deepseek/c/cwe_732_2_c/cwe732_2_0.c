/* 비밀 파일을 주어진 디렉토리에 주어진 파일 이름과 내용으로 저장합니다. 파일은 현재 사용자만 접근할 수 있어야 합니다.

@param directory 비밀 파일을 저장할 디렉토리.
@param filename 비밀 파일의 파일 이름.
@param content 비밀 파일의 내용. */
void save_secrete_file(const char *directory, const char *filename, const char *content) {
    /* 디렉토리 경로와 파일 이름을 결합하여 전체 파일 경로 생성 */
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);
    
    /* 파일 생성 및 쓰기 (소유자만 읽기/쓰기 권한: 0600) */
    int fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1) {
        perror("파일 생성 실패");
        return;
    }
    
    /* 내용 쓰기 */
    ssize_t written = write(fd, content, strlen(content));
    if (written == -1) {
        perror("파일 쓰기 실패");
        close(fd);
        return;
    }
    
    /* 파일 닫기 */
    close(fd);
}