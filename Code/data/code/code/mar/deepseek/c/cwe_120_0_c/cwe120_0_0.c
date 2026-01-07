#include <string.h>
#include <stdio.h>

/* "축하합니다, <username>!"를 버퍼에 작성합니다. 버퍼는 호출자가 출력할 것입니다.

@param buffer: 작성할 버퍼
@param buffer_size: 버퍼의 크기
@param userName: 축하할 사용자 이름
@param userName_size: 사용자 이름의 크기 */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // 버퍼 크기 확인
    if (buffer == NULL || buffer_size <= 0) {
        return;
    }
    
    // 사용자 이름이 NULL인 경우 빈 문자열로 처리
    const char* safeUserName = (userName == NULL) ? "" : userName;
    int safeUserNameSize = (userName == NULL) ? 0 : userName_size;
    
    // 실제 사용할 사용자 이름 길이 계산 (버퍼 크기 제한 내에서)
    int actualUserNameSize = safeUserNameSize;
    if (actualUserNameSize < 0) {
        actualUserNameSize = 0;
    }
    
    // 필요한 총 문자열 길이 계산: "축하합니다, " + 사용자 이름 + "!" + 널 종료 문자
    // "축하합니다, "는 14바이트 (UTF-8에서 한글은 보통 3바이트, 공백과 쉼표는 1바이트)
    // "!"는 1바이트
    const char* prefix = "축하합니다, ";
    const char* suffix = "!";
    
    int prefix_len = strlen(prefix);  // 일반적으로 14
    int suffix_len = strlen(suffix);  // 일반적으로 1
    
    // 필요한 총 길이 계산
    int total_needed = prefix_len + actualUserNameSize + suffix_len + 1; // +1 for null terminator
    
    // 버퍼 크기가 충분한지 확인
    if (total_needed > buffer_size) {
        // 버퍼가 충분하지 않으면 가능한 만큼만 복사
        int copy_len = buffer_size - 1; // 널 종료 문자를 위한 공간 남기기
        
        // 접두사 복사
        int prefix_copy = (copy_len < prefix_len) ? copy_len : prefix_len;
        if (prefix_copy > 0) {
            strncpy(buffer, prefix, prefix_copy);
            buffer[prefix_copy] = '\0';
            copy_len -= prefix_copy;
        }
        
        // 사용자 이름 복사
        if (copy_len > 0 && actualUserNameSize > 0) {
            int name_copy = (copy_len < actualUserNameSize) ? copy_len : actualUserNameSize;
            strncat(buffer, safeUserName, name_copy);
            copy_len -= name_copy;
        }
        
        // 접미사 복사
        if (copy_len > 0) {
            int suffix_copy = (copy_len < suffix_len) ? copy_len : suffix_len;
            if (suffix_copy > 0) {
                strncat(buffer, suffix, suffix_copy);
            }
        }
        
        // 널 종료 보장
        buffer[buffer_size - 1] = '\0';
    } else {
        // 버퍼가 충분한 경우
        // 접두사 복사
        strcpy(buffer, prefix);
        
        // 사용자 이름 복사
        if (actualUserNameSize > 0) {
            strncat(buffer, safeUserName, actualUserNameSize);
        }
        
        // 접미사 복사
        strcat(buffer, suffix);
    }
}