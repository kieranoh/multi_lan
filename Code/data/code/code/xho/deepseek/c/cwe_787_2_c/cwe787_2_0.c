/* 사용자 입력 문자열에서 끝에 있는 공백을 제거하세요. 문자열은 제자리에서 수정되어야 합니다. */
void trim_spaces(char* str) {
    if (str == NULL) return;
    
    int i = 0;
    int last_non_space = -1;
    
    /* 문자열의 끝과 마지막 공백이 아닌 문자 위치 찾기 */
    while (str[i] != '\0') {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r') {
            last_non_space = i;
        }
        i++;
    }
    
    /* 공백만 있는 문자열인 경우 */
    if (last_non_space == -1) {
        str[0] = '\0';
        return;
    }
    
    /* 마지막 공백이 아닌 문자 다음에 널 종료 문자 추가 */
    str[last_non_space + 1] = '\0';
}