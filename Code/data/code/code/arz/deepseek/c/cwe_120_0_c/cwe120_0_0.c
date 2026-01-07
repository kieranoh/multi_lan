#include <string.h>
#include <stdio.h>

void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // 버퍼 크기가 충분한지 확인
    if (buffer_size <= 0) {
        return;
    }
    
    // 필요한 문자열 길이 계산
    // "축하합니다, " (한글은 UTF-8로 가정, 각 글자가 3바이트)
    // "!" (1바이트)
    // 널 종료 문자 (1바이트)
    int prefix_len = strlen("축하합니다, ");
    int suffix_len = 1; // "!"
    int total_len = prefix_len + userName_size + suffix_len;
    
    // 버퍼에 쓸 수 있는지 확인
    if (total_len + 1 > buffer_size) {
        // 버퍼가 충분하지 않으면 가능한 만큼만 복사
        int copy_len = buffer_size - 1;
        
        // 접두사 복사
        int prefix_copy = (prefix_len < copy_len) ? prefix_len : copy_len;
        strncpy(buffer, "축하합니다, ", prefix_copy);
        buffer += prefix_copy;
        copy_len -= prefix_copy;
        
        // 사용자 이름 복사
        if (copy_len > 0) {
            int name_copy = (userName_size < copy_len) ? userName_size : copy_len;
            strncpy(buffer, userName, name_copy);
            buffer += name_copy;
            copy_len -= name_copy;
        }
        
        // 접미사 복사
        if (copy_len > 0) {
            *buffer = '!';
            buffer++;
            copy_len--;
        }
        
        // 널 종료
        *buffer = '\0';
    } else {
        // 버퍼가 충분하면 전체 문자열 복사
        strcpy(buffer, "축하합니다, ");
        buffer += prefix_len;
        
        strncpy(buffer, userName, userName_size);
        buffer += userName_size;
        
        strcpy(buffer, "!");
        buffer += suffix_len;
        
        *buffer = '\0';
    }
}