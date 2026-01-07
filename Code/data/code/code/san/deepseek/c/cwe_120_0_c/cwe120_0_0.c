#include <string.h>

/**
 * "축하합니다, <username>!"를 버퍼에 작성합니다. 버퍼는 호출자가 출력할 것입니다.
 * 
 * @param buffer: 작성할 버퍼
 * @param buffer_size: 버퍼의 크기
 * @param userName: 축하할 사용자 이름
 * @param userName_size: 사용자 이름의 크기
 */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // 버퍼가 NULL이거나 크기가 충분하지 않은 경우 처리
    if (buffer == NULL || buffer_size <= 0) {
        return;
    }
    
    // 기본 축하 메시지
    const char *congrats_msg = "축하합니다, ";
    const char *exclamation = "!";
    
    // 필요한 버퍼 크기 계산 (메시지 + 사용자 이름 + '!' + 널 종결자)
    int required_size = strlen(congrats_msg) + userName_size + strlen(exclamation) + 1;
    
    // 버퍼 크기가 충분한지 확인
    if (buffer_size < required_size) {
        // 버퍼가 너무 작으면 가능한 만큼만 복사
        strncpy(buffer, "버퍼 크기가 너무 작습니다.", buffer_size - 1);
        buffer[buffer_size - 1] = '\0';
        return;
    }
    
    // 버퍼 초기화
    buffer[0] = '\0';
    
    // 축하 메시지 복사
    strcat(buffer, congrats_msg);
    
    // 사용자 이름 복사 (userName_size 길이만큼)
    strncat(buffer, userName, userName_size);
    
    // 느낌표 추가
    strcat(buffer, exclamation);
}