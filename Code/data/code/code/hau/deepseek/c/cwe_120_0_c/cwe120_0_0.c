void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // 문자열 구성
    const char *prefix = "축하합니다, ";
    const char *suffix = "!";
    
    // 필요한 버퍼 크기 계산 (prefix + userName + suffix + null 종결자)
    int needed_size = strlen(prefix) + userName_size + strlen(suffix) + 1;
    
    // 버퍼 크기 검증
    if (buffer_size < needed_size) {
        // 버퍼가 충분하지 않으면 가능한 만큼만 복사하고 null 종결
        strncpy(buffer, prefix, buffer_size - 1);
        buffer[buffer_size - 1] = '\0';
        return;
    }
    
    // 문자열 조립
    strcpy(buffer, prefix);
    strncat(buffer, userName, userName_size);
    strcat(buffer, suffix);
}