#include <string.h>
#include <stdlib.h>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <ctype.h>

char* decode_json_web_token(const char* token, const char* key) {
    // 빈 토큰 또는 키 체크
    if (!token || !key || strlen(token) == 0 || strlen(key) == 0) {
        char* empty_json = malloc(3);
        if (empty_json) {
            strcpy(empty_json, "{}");
        }
        return empty_json;
    }
    
    // Base64 디코딩 헬퍼 함수
    unsigned char* base64_decode(const char* input, int* out_len) {
        BIO* bio = BIO_new(BIO_f_base64());
        BIO* bmem = BIO_new_mem_buf((void*)input, strlen(input));
        bio = BIO_push(bio, bmem);
        BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
        
        unsigned char* buffer = malloc(strlen(input));
        if (!buffer) {
            BIO_free_all(bio);
            return NULL;
        }
        
        *out_len = BIO_read(bio, buffer, strlen(input));
        BIO_free_all(bio);
        
        return buffer;
    }
    
    // Base64 URL-safe 디코딩
    unsigned char* base64url_decode(const char* input, int* out_len) {
        // URL-safe Base64를 표준 Base64로 변환
        char* standard = malloc(strlen(input) + 4);
        if (!standard) {
            return NULL;
        }
        
        int j = 0;
        for (int i = 0; input[i] != '\0'; i++) {
            if (input[i] == '-') {
                standard[j++] = '+';
            } else if (input[i] == '_') {
                standard[j++] = '/';
            } else {
                standard[j++] = input[i];
            }
        }
        
        // 패딩 추가
        while (j % 4 != 0) {
            standard[j++] = '=';
        }
        standard[j] = '\0';
        
        unsigned char* result = base64_decode(standard, out_len);
        free(standard);
        return result;
    }
    
    // JWT 파싱 (헤더.페이로드.서명)
    char* token_copy = strdup(token);
    if (!token_copy) {
        char* empty_json = malloc(3);
        if (empty_json) {
            strcpy(empty_json, "{}");
        }
        return empty_json;
    }
    
    char* parts[3];
    int part_count = 0;
    char* saveptr = NULL;
    char* part = strtok_r(token_copy, ".", &saveptr);
    
    while (part != NULL && part_count < 3) {
        parts[part_count++] = part;
        part = strtok_r(NULL, ".", &saveptr);
    }
    
    // JWT 형식이 올바른지 확인 (3부분이 있어야 함)
    if (part_count != 3) {
        free(token_copy);
        char* empty_json = malloc(3);
        if (empty_json) {
            strcpy(empty_json, "{}");
        }
        return empty_json;
    }
    
    // 서명 검증
    // 헤더와 페이로드를 결합
    char header_payload[strlen(parts[0]) + strlen(parts[1]) + 2];
    sprintf(header_payload, "%s.%s", parts[0], parts[1]);
    
    // HMAC-SHA256으로 서명 생성
    unsigned char hmac_result[SHA256_DIGEST_LENGTH];
    unsigned int hmac_len;
    
    HMAC(EVP_sha256(), key, strlen(key), 
         (unsigned char*)header_payload, strlen(header_payload),
         hmac_result, &hmac_len);
    
    // 생성된 서명을 Base64 URL-safe로 인코딩
    char* expected_signature = parts[2];
    
    // 실제 서명 디코딩
    int sig_len;
    unsigned char* decoded_sig = base64url_decode(expected_signature, &sig_len);
    
    // 서명 비교
    int signature_valid = 1;
    if (!decoded_sig || hmac_len != (unsigned int)sig_len) {
        signature_valid = 0;
    } else {
        for (int i = 0; i < hmac_len; i++) {
            if (hmac_result[i] != decoded_sig[i]) {
                signature_valid = 0;
                break;
            }
        }
    }
    
    if (decoded_sig) {
        free(decoded_sig);
    }
    
    // 서명이 유효하지 않으면 빈 JSON 반환
    if (!signature_valid) {
        free(token_copy);
        char* empty_json = malloc(3);
        if (empty_json) {
            strcpy(empty_json, "{}");
        }
        return empty_json;
    }
    
    // 페이로드 디코딩
    int payload_len;
    unsigned char* decoded_payload = base64url_decode(parts[1], &payload_len);
    
    if (!decoded_payload || payload_len <= 0) {
        free(token_copy);
        if (decoded_payload) {
            free(decoded_payload);
        }
        char* empty_json = malloc(3);
        if (empty_json) {
            strcpy(empty_json, "{}");
        }
        return empty_json;
    }
    
    // 디코딩된 페이로드를 문자열로 변환
    char* payload_str = malloc(payload_len + 1);
    if (!payload_str) {
        free(token_copy);
        free(decoded_payload);
        char* empty_json = malloc(3);
        if (empty_json) {
            strcpy(empty_json, "{}");
        }
        return empty_json;
    }
    
    memcpy(payload_str, decoded_payload, payload_len);
    payload_str[payload_len] = '\0';
    
    // 결과 반환
    char* result = malloc(strlen(payload_str) + 1);
    if (result) {
        strcpy(result, payload_str);
    } else {
        result = malloc(3);
        if (result) {
            strcpy(result, "{}");
        }
    }
    
    // 메모리 정리
    free(token_copy);
    free(decoded_payload);
    free(payload_str);
    
    return result;
}