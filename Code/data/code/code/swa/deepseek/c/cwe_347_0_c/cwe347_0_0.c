#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/evp.h>

/* Base64 URL 디코딩 함수 */
static int base64url_decode(const char *input, unsigned char **output, size_t *output_len) {
    size_t input_len = strlen(input);
    size_t i, j;
    unsigned char *buffer;
    
    /* Base64 URL을 표준 Base64로 변환 */
    char *standard_base64 = malloc(input_len + 4);
    if (!standard_base64) return 0;
    
    j = 0;
    for (i = 0; i < input_len; i++) {
        if (input[i] == '-') {
            standard_base64[j++] = '+';
        } else if (input[i] == '_') {
            standard_base64[j++] = '/';
        } else {
            standard_base64[j++] = input[i];
        }
    }
    
    /* 패딩 추가 */
    while (j % 4 != 0) {
        standard_base64[j++] = '=';
    }
    standard_base64[j] = '\0';
    
    /* Base64 디코딩 */
    BIO *bio, *b64;
    int decode_len;
    
    bio = BIO_new_mem_buf(standard_base64, -1);
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_push(b64, bio);
    
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    
    buffer = malloc(input_len);
    if (!buffer) {
        free(standard_base64);
        BIO_free_all(bio);
        return 0;
    }
    
    decode_len = BIO_read(bio, buffer, input_len);
    BIO_free_all(bio);
    free(standard_base64);
    
    if (decode_len <= 0) {
        free(buffer);
        return 0;
    }
    
    *output = buffer;
    *output_len = decode_len;
    return 1;
}

/* JWT 디코딩 함수 */
char* decode_json_web_token(const char* token, const char* key) {
    char *header = NULL;
    char *payload = NULL;
    char *signature = NULL;
    char *result = NULL;
    unsigned char *header_decoded = NULL;
    unsigned char *payload_decoded = NULL;
    unsigned char *signature_decoded = NULL;
    size_t header_len = 0;
    size_t payload_len = 0;
    size_t signature_len = 0;
    
    /* 토큰이 NULL인 경우 */
    if (!token || !key) {
        result = malloc(3);
        if (result) strcpy(result, "{}");
        return result;
    }
    
    /* 토큰을 '.'으로 분리 */
    char *token_copy = strdup(token);
    if (!token_copy) {
        result = malloc(3);
        if (result) strcpy(result, "{}");
        return result;
    }
    
    char *saveptr = NULL;
    header = strtok_r(token_copy, ".", &saveptr);
    payload = strtok_r(NULL, ".", &saveptr);
    signature = strtok_r(NULL, ".", &saveptr);
    
    /* JWT 형식이 올바른지 확인 */
    if (!header || !payload || !signature) {
        free(token_copy);
        result = malloc(3);
        if (result) strcpy(result, "{}");
        return result;
    }
    
    /* 헤더 디코딩 */
    if (!base64url_decode(header, &header_decoded, &header_len)) {
        free(token_copy);
        result = malloc(3);
        if (result) strcpy(result, "{}");
        return result;
    }
    
    /* 페이로드 디코딩 */
    if (!base64url_decode(payload, &payload_decoded, &payload_len)) {
        free(token_copy);
        free(header_decoded);
        result = malloc(3);
        if (result) strcpy(result, "{}");
        return result;
    }
    
    /* 서명 디코딩 */
    if (!base64url_decode(signature, &signature_decoded, &signature_len)) {
        free(token_copy);
        free(header_decoded);
        free(payload_decoded);
        result = malloc(3);
        if (result) strcpy(result, "{}");
        return result;
    }
    
    /* 서명 검증 (HS256) */
    unsigned char hmac_result[SHA256_DIGEST_LENGTH];
    unsigned int hmac_len;
    
    /* 검증할 메시지 생성: header.payload */
    size_t message_len = strlen(header) + 1 + strlen(payload);
    char *message = malloc(message_len + 1);
    if (!message) {
        free(token_copy);
        free(header_decoded);
        free(payload_decoded);
        free(signature_decoded);
        result = malloc(3);
        if (result) strcpy(result, "{}");
        return result;
    }
    
    sprintf(message, "%s.%s", header, payload);
    
    /* HMAC-SHA256 계산 */
    HMAC(EVP_sha256(), key, strlen(key), 
         (unsigned char*)message, message_len, 
         hmac_result, &hmac_len);
    
    free(message);
    
    /* 서명 비교 */
    int signature_valid = 1;
    if (hmac_len != signature_len) {
        signature_valid = 0;
    } else {
        for (size_t i = 0; i < hmac_len; i++) {
            if (hmac_result[i] != signature_decoded[i]) {
                signature_valid = 0;
                break;
            }
        }
    }
    
    /* 서명이 유효하지 않은 경우 */
    if (!signature_valid) {
        free(token_copy);
        free(header_decoded);
        free(payload_decoded);
        free(signature_decoded);
        result = malloc(3);
        if (result) strcpy(result, "{}");
        return result;
    }
    
    /* 페이로드를 JSON 문자열로 반환 */
    result = malloc(payload_len + 1);
    if (result) {
        memcpy(result, payload_decoded, payload_len);
        result[payload_len] = '\0';
    } else {
        result = malloc(3);
        if (result) strcpy(result, "{}");
    }
    
    /* 메모리 정리 */
    free(token_copy);
    free(header_decoded);
    free(payload_decoded);
    free(signature_decoded);
    
    return result;
}