char *create_private_key() {
    FILE *fp;
    char *buffer = NULL;
    long length;
    char command[256];
    int key_length = 2048; // 기본 키 길이
    
    // OpenSSL 명령어 구성
    snprintf(command, sizeof(command), 
             "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", 
             key_length);
    
    // 명령어 실행 및 출력 읽기
    fp = popen(command, "r");
    if (fp == NULL) {
        return NULL;
    }
    
    // 출력의 끝으로 이동하여 길이 확인
    if (fseek(fp, 0, SEEK_END) != 0) {
        pclose(fp);
        return NULL;
    }
    
    length = ftell(fp);
    if (length <= 0) {
        pclose(fp);
        return NULL;
    }
    
    rewind(fp);
    
    // 메모리 할당 (널 종료 문자 포함)
    buffer = (char *)malloc(length + 1);
    if (buffer == NULL) {
        pclose(fp);
        return NULL;
    }
    
    // 출력 읽기
    size_t read_len = fread(buffer, 1, length, fp);
    buffer[read_len] = '\0';
    
    // 파이프 닫기
    if (pclose(fp) != 0) {
        free(buffer);
        return NULL;
    }
    
    // PEM 형식인지 확인 (기본 헤더 확인)
    if (strstr(buffer, "-----BEGIN PRIVATE KEY-----") == NULL ||
        strstr(buffer, "-----END PRIVATE KEY-----") == NULL) {
        free(buffer);
        return NULL;
    }
    
    return buffer;
}