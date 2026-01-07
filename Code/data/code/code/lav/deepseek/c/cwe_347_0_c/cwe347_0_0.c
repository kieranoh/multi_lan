#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

// Base64 URL 디코딩 함수
static unsigned char* base64_url_decode(const char* input, int *out_len) {
    int len = strlen(input);
    char* normalized = malloc(len + 4);
    if (!normalized) return NULL;
    
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (input[i] == '-') {
            normalized[j++] = '+';
        } else if (input[i] == '_') {
            normalized[j++] = '/';
        } else {
            normalized[j++] = input[i];
        }
    }
    
    // 패딩 추가
    while (j % 4 != 0) {
        normalized[j++] = '=';
    }
    normalized[j] = '\0';
    
    BIO *bio, *b64;
    unsigned char* buffer = malloc(j);
    if (!buffer) {
        free(normalized);
        return NULL;
    }
    
    bio = BIO_new_mem_buf(normalized, -1);
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_push(b64, bio);
    
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    int decoded_len = BIO_read(bio, buffer, j);
    
    BIO_free_all(bio);
    free(normalized);
    
    if (decoded_len <= 0) {
        free(buffer);
        return NULL;
    }
    
    *out_len = decoded_len;
    return buffer;
}

// Base64 URL 인코딩 함수
static char* base64_url_encode(const unsigned char* input, int length) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;
    
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);
    
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(bio, input, length);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);
    
    char* encoded = malloc(bufferPtr->length + 1);
    if (!encoded) {
        BIO_free_all(bio);
        return NULL;
    }
    
    memcpy(encoded, bufferPtr->data, bufferPtr->length);
    encoded[bufferPtr->length] = '\0';
    
    // URL-safe 변환
    for (int i = 0; i < bufferPtr->length; i++) {
        if (encoded[i] == '+') encoded[i] = '-';
        else if (encoded[i] == '/') encoded[i] = '_';
        else if (encoded[i] == '=') {
            encoded[i] = '\0';
            break;
        }
    }
    
    BIO_free_all(bio);
    return encoded;
}

// HMAC SHA256 서명 생성
static char* hmac_sha256(const char* key, const char* data) {
    unsigned char* digest = HMAC(EVP_sha256(), key, strlen(key), 
                                 (unsigned char*)data, strlen(data), NULL, NULL);
    if (!digest) return NULL;
    
    return base64_url_encode(digest, SHA256_DIGEST_LENGTH);
}

// JWT 디코딩 함수
char* decode_json_web_token(const char* token, const char* key) {
    if (!token || !key) {
        return strdup("{}");
    }
    
    // 토큰 파싱
    char* token_copy = strdup(token);
    if (!token_copy) {
        return strdup("{}");
    }
    
    char* parts[3];
    int part_count = 0;
    char* saveptr = NULL;
    
    char* part = strtok_r(token_copy, ".", &saveptr);
    while (part && part_count < 3) {
        parts[part_count++] = part;
        part = strtok_r(NULL, ".", &saveptr);
    }
    
    if (part_count != 3) {
        free(token_copy);
        return strdup("{}");
    }
    
    // 서명 검증
    char header_payload[1024];
    snprintf(header_payload, sizeof(header_payload), "%s.%s", parts[0], parts[1]);
    
    char* calculated_signature = hmac_sha256(key, header_payload);
    if (!calculated_signature) {
        free(token_copy);
        return strdup("{}");
    }
    
    // 서명 비교
    if (strcmp(calculated_signature, parts[2]) != 0) {
        free(calculated_signature);
        free(token_copy);
        return strdup("{}");
    }
    
    free(calculated_signature);
    
    // 페이로드 디코딩
    int payload_len;
    unsigned char* payload_decoded = base64_url_decode(parts[1], &payload_len);
    if (!payload_decoded) {
        free(token_copy);
        return strdup("{}");
    }
    
    // 페이로드를 문자열로 변환
    char* payload_str = malloc(payload_len + 1);
    if (!payload_str) {
        free(payload_decoded);
        free(token_copy);
        return strdup("{}");
    }
    
    memcpy(payload_str, payload_decoded, payload_len);
    payload_str[payload_len] = '\0';
    
    // 결과 정리
    free(payload_decoded);
    free(token_copy);
    
    return payload_str;
}