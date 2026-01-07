void trim_spaces(char* str) {
    if (str == NULL) return;
    
    char* end = str;
    char* last_non_space = str;
    
    // 문자열 끝과 마지막 공백이 아닌 문자 위치 찾기
    while (*end != '\0') {
        if (*end != ' ' && *end != '\t' && *end != '\n' && *end != '\r') {
            last_non_space = end;
        }
        end++;
    }
    
    // 마지막 공백이 아닌 문자 다음에 널 종료 문자 삽입
    *(last_non_space + 1) = '\0';
}