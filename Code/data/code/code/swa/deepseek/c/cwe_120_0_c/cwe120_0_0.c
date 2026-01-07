#include <string.h>
#include <stdio.h>

/* "축하합니다, <username>!"를 버퍼에 작성합니다. 버퍼는 호출자가 출력할 것입니다.

@param buffer: 작성할 버퍼
@param buffer_size: 버퍼의 크기
@param userName: 축하할 사용자 이름
@param userName_size: 사용자 이름의 크기 */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // 버퍼가 NULL이거나 크기가 충분하지 않은 경우 안전하게 처리
    if (buffer == NULL || buffer_size <= 0) {
        return;
    }
    
    // 기본 축하 메시지 포맷
    const char *prefix = "축하합니다, ";
    const char *suffix = "!";
    
    // 필요한 총 공간 계산 (접두사 + 사용자 이름 + 접미사 + 널 종결자)
    int needed_size = strlen(prefix) + userName_size + strlen(suffix) + 1;
    
    // 버퍼 크기가 충분한지 확인
    if (needed_size > buffer_size) {
        // 버퍼가 너무 작으면 가능한 만큼만 복사하고 안전하게 종결
        int copied = 0;
        
        // 접두사 복사
        int prefix_len = strlen(prefix);
        int to_copy = (prefix_len < buffer_size - 1) ? prefix_len : buffer_size - 1;
        strncpy(buffer, prefix, to_copy);
        copied += to_copy;
        
        // 사용자 이름 복사
        if (copied < buffer_size - 1) {
            int remaining = buffer_size - 1 - copied;
            int name_to_copy = (userName_size < remaining) ? userName_size : remaining;
            strncpy(buffer + copied, userName, name_to_copy);
            copied += name_to_copy;
        }
        
        // 접미사 복사 (가능한 경우)
        if (copied < buffer_size - 1) {
            int suffix_len = strlen(suffix);
            int remaining = buffer_size - 1 - copied;
            int suffix_to_copy = (suffix_len < remaining) ? suffix_len : remaining;
            strncpy(buffer + copied, suffix, suffix_to_copy);
            copied += suffix_to_copy;
        }
        
        // 널 종결자 추가
        buffer[buffer_size - 1] = '\0';
    } else {
        // 충분한 공간이 있는 경우 정상적으로 작성
        strcpy(buffer, prefix);
        strncat(buffer, userName, userName_size);
        strcat(buffer, suffix);
    }
}