#include <string.h>

/* "축하합니다, <username>!"를 버퍼에 작성합니다. 버퍼는 호출자가 출력할 것입니다.

@param buffer: 작성할 버퍼
@param buffer_size: 버퍼의 크기
@param userName: 축하할 사용자 이름 */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // 버퍼가 NULL이거나 크기가 충분하지 않은 경우
    if (buffer == NULL || buffer_size <= 0) {
        return;
    }
    
    // 기본 축하 메시지
    const char *prefix = "축하합니다, ";
    const char *suffix = "!";
    
    // 필요한 버퍼 크기 계산 (prefix + userName + suffix + null 종료 문자)
    int needed_size = strlen(prefix) + userName_size + strlen(suffix) + 1;
    
    // 버퍼 크기가 충분한지 확인
    if (buffer_size < needed_size) {
        // 버퍼가 너무 작으면 가능한 만큼만 복사
        strncpy(buffer, prefix, buffer_size - 1);
        buffer[buffer_size - 1] = '\0';
        
        // userName을 추가할 공간이 있는지 확인
        int prefix_len = strlen(prefix);
        int remaining = buffer_size - prefix_len - 1; // -1 for null terminator
        
        if (remaining > 0) {
            // userName의 일부를 추가
            int copy_len = (userName_size < remaining) ? userName_size : remaining;
            strncat(buffer, userName, copy_len);
            
            // suffix를 추가할 공간이 있는지 확인
            remaining = buffer_size - strlen(buffer) - 1;
            if (remaining > 0) {
                strncat(buffer, suffix, remaining);
            }
        }
    } else {
        // 버퍼가 충분히 큰 경우
        strcpy(buffer, prefix);
        strncat(buffer, userName, userName_size);
        strcat(buffer, suffix);
    }
}