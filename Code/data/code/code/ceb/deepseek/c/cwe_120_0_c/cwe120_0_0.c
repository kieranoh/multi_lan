#include <string.h>
#include <stdio.h>

void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // 버퍼 크기가 충분한지 확인
    if (buffer_size <= 0) {
        return;
    }
    
    // 안전하게 복사하기 위해 버퍼 크기 계산
    // "축하합니다, " (한글: 5글자 + 콤마 + 공백 = UTF-8로 약 15바이트 + null 종료)
    // 실제로는 더 정확하게 계산하지만, 간단히 처리
    const char *prefix = "축하합니다, ";
    const char *suffix = "!";
    
    // 필요한 총 길이 계산 (prefix + userName + suffix + null 종료)
    int needed_size = strlen(prefix) + userName_size + strlen(suffix) + 1;
    
    if (needed_size > buffer_size) {
        // 버퍼가 너무 작으면 가능한 만큼만 복사
        // prefix 복사
        strncpy(buffer, prefix, buffer_size - 1);
        buffer[buffer_size - 1] = '\0';
        
        // 가능한 경우 일부 사용자 이름 추가
        int prefix_len = strlen(buffer);
        int remaining = buffer_size - prefix_len - 1; // suffix와 null 종료를 위한 공간
        
        if (remaining > 0) {
            // 사용자 이름의 일부 복사
            int copy_len = (userName_size < remaining) ? userName_size : remaining;
            strncat(buffer, userName, copy_len);
            
            // 가능한 경우 suffix 추가
            int current_len = strlen(buffer);
            remaining = buffer_size - current_len - 1;
            
            if (remaining > 0) {
                strncat(buffer, suffix, remaining);
            }
        }
    } else {
        // 버퍼가 충분히 큰 경우 정상적으로 복사
        strcpy(buffer, prefix);
        strncat(buffer, userName, userName_size);
        strcat(buffer, suffix);
    }
}