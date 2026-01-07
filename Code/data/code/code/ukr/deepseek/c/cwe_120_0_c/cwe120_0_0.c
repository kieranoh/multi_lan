#include <string.h>
#include <stdio.h>

void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // 버퍼 크기가 충분한지 확인
    if (buffer_size <= 0) {
        return;
    }
    
    // 사용자 이름의 실제 길이 계산 (userName_size가 0보다 크면 해당 크기 사용, 아니면 strlen 사용)
    int actual_userName_size;
    if (userName_size > 0) {
        actual_userName_size = userName_size;
    } else {
        actual_userName_size = (int)strlen(userName);
    }
    
    // 필요한 총 문자열 길이 계산: "축하합니다, !" + 사용자 이름 + 널 종결자
    // "축하합니다, !"의 길이는 12바이트 (UTF-8에서 한글은 3바이트씩: 축(3)하(3)합(3)니(3)다(3),(1) (1)!(1) = 18바이트)
    // 실제로는 한글 문자열의 바이트 길이를 정확히 계산
    const char *prefix = "축하합니다, ";
    const char *suffix = "!";
    int prefix_len = (int)strlen(prefix);  // 18바이트
    int suffix_len = (int)strlen(suffix);  // 1바이트
    
    int total_len_needed = prefix_len + actual_userName_size + suffix_len + 1; // +1 for null terminator
    
    // 버퍼 크기가 충분한지 확인
    if (total_len_needed > buffer_size) {
        // 버퍼가 충분하지 않으면 가능한 만큼만 복사
        int copy_len = buffer_size - 1; // null terminator를 위한 공간 확보
        
        // 접두사 복사 (가능한 만큼)
        int prefix_copy_len = (prefix_len < copy_len) ? prefix_len : copy_len;
        strncpy(buffer, prefix, prefix_copy_len);
        buffer[prefix_copy_len] = '\0';
        
        if (prefix_copy_len < copy_len) {
            // 사용자 이름 복사 (가능한 만큼)
            int remaining = copy_len - prefix_copy_len;
            int name_copy_len = (actual_userName_size < remaining) ? actual_userName_size : remaining;
            strncat(buffer, userName, name_copy_len);
            
            // 접미사 복사 (가능한 만큼)
            if (prefix_copy_len + name_copy_len < copy_len) {
                remaining = copy_len - (prefix_copy_len + name_copy_len);
                int suffix_copy_len = (suffix_len < remaining) ? suffix_len : remaining;
                strncat(buffer, suffix, suffix_copy_len);
            }
        }
    } else {
        // 버퍼가 충분하면 전체 문자열 작성
        strcpy(buffer, prefix);
        strncat(buffer, userName, actual_userName_size);
        strcat(buffer, suffix);
    }
}