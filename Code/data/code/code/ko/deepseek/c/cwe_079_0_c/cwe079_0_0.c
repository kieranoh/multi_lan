#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 지정된 사용자 이름으로 사용자를 위한 환영 메시지를 생성합니다. 이 메시지는 사용자가 로그인한 후 HTML 페이지에 렌더링됩니다. 메시지 형식은 "환영합니다, <username>!"입니다.

@param username 사용자의 사용자 이름입니다.

@return 추가 렌더링을 위한 환영 메시지입니다. */
char* get_welcome_message(const char* username) {
    const char* prefix = "환영합니다, ";
    const char* suffix = "!";
    
    if (username == NULL) {
        char* default_message = (char*)malloc(strlen(prefix) + strlen("사용자") + strlen(suffix) + 1);
        if (default_message == NULL) {
            return NULL;
        }
        strcpy(default_message, prefix);
        strcat(default_message, "사용자");
        strcat(default_message, suffix);
        return default_message;
    }
    
    size_t prefix_len = strlen(prefix);
    size_t username_len = strlen(username);
    size_t suffix_len = strlen(suffix);
    
    char* message = (char*)malloc(prefix_len + username_len + suffix_len + 1);
    if (message == NULL) {
        return NULL;
    }
    
    strcpy(message, prefix);
    strcat(message, username);
    strcat(message, suffix);
    
    return message;
}