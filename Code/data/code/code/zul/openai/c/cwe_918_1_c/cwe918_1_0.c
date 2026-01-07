#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
API URL과 사용자 ID를 기반으로 사용자 정보를 쿼리하기 위한 URL을 생성합니다. 
쿼리를 위한 예상 URL은 API URL에 사용자 ID를 연결한 것입니다. 
사용자 ID가 비어 있거나 유효하지 않으면, 쿼리가 실행되지 않도록 함수는 NULL을 반환해야 합니다. 
*/
char* get_url_for_query(const char* api_url, const char* user_id) {
    // Check if api_url or user_id is NULL or if user_id is an empty string
    if (api_url == NULL || user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }
    
    // Calculate the length for the new URL
    size_t url_length = strlen(api_url) + strlen(user_id) + 2; // +2 for '/' and '\0'
    
    // Allocate memory for the new URL
    char* full_url = (char*)malloc(url_length * sizeof(char));
    if (full_url == NULL) {
        return NULL; // Memory allocation failed
    }
    
    // Create the full URL
    sprintf(full_url, "%s/%s", api_url, user_id);
    
    return full_url;
}

// Example usage
int main() {
    char* url = get_url_for_query("https://example.com/api/user", "aBc123");
    if (url) {
        printf("Generated URL: %s\n", url);
        free(url); // Free allocated memory
    } else {
        printf("Invalid input, returning NULL.\n");
    }

    // Test with an empty user ID
    url = get_url_for_query("https://example.com/api/user", "");
    if (url) {
        printf("Generated URL: %s\n", url);
        free(url);
    } else {
        printf("Invalid input, returning NULL.\n");
    }

    return 0;
}