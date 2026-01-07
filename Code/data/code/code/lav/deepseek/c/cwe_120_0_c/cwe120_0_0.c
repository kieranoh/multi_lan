#include <string.h>
#include <stdio.h>

void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // 입력 유효성 검사
    if (buffer == NULL || userName == NULL || buffer_size <= 0) {
        return;
    }
    
    // 실제 사용자 이름 길이 계산 (userName_size가 0보다 작으면 null-terminated 문자열로 처리)
    int actual_userName_len;
    if (userName_size < 0) {
        actual_userName_len = strlen(userName);
    } else {
        // userName_size가 제공된 경우, null 문자를 포함하지 않는 길이로 처리
        actual_userName_len = userName_size;
    }
    
    // 필요한 버퍼 크기 계산: "축하합니다, " + 사용자 이름 + "!" + null 종결자
    int required_size = 12 + actual_userName_len + 1 + 1; // UTF-8 한글은 각 글자가 3바이트
    
    // 버퍼가 충분히 큰지 확인
    if (buffer_size < required_size) {
        // 버퍼가 부족하면 안전하게 처리
        if (buffer_size > 0) {
            buffer[0] = '\0';
        }
        return;
    }
    
    // 버퍼에 메시지 작성
    int written = 0;
    
    // "축하합니다, " 추가 (한글: 축하합니다)
    const char *prefix = "축하합니다, ";
    strcpy(buffer, prefix);
    written = strlen(prefix);
    
    // 사용자 이름 추가
    if (userName_size < 0) {
        // null-terminated 문자열인 경우
        strcpy(buffer + written, userName);
        written += strlen(userName);
    } else {
        // 고정 길이 문자열인 경우
        strncpy(buffer + written, userName, actual_userName_len);
        written += actual_userName_len;
        buffer[written] = '\0'; // 안전을 위해 null 종결
    }
    
    // "!" 추가
    buffer[written] = '!';
    written++;
    buffer[written] = '\0';
}