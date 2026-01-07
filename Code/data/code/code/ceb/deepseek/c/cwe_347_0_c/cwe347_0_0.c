#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

/* Base64 URL 디코딩 함수 */
static unsigned char* base64url_decode(const char* input, int* out_len) {
    if (!input) return NULL;
    
    int len = strlen(input);
    char* base64 = (char*)malloc(len + 4);
    if (!base64) return NULL;
    
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (input[i] == '-') {
            base64[j++] = '+';
        } else if (input[i] == '_') {
            base64[j++] = '/';
        } else {
            base64[j++] = input[i];
        }
    }
    
    /* 패딩 추가 */
    while (j % 4 != 0) {
        base64[j++] = '=';
    }
    base64[j] = '\0';
    
    BIO* b64 = BIO_new(BIO_f_base64());
    BIO* mem = BIO_new_mem_buf(base64, j);
    mem = BIO_push(b64, mem);
    
    /* Base64 디코딩 */
    unsigned char* output = (unsigned char*)malloc(j);
    if (!output) {
        free(base64);
        BIO_free_all(mem);
        return NULL;
    }
    
    int decoded_len = BIO_read(mem, output, j);
    BIO_free_all(mem);
    free(base64);
    
    if (decoded_len <= 0) {
        free(output);
        return NULL;
    }
    
    *out_len = decoded_len;
    return output;
}

/* HMAC SHA256 검증 함수 */
static int verify_hmac_sha256(const char* key, const char* header_and_payload, 
                              const unsigned char* signature, int sig_len) {
    unsigned char result[SHA256_DIGEST_LENGTH];
    unsigned int result_len;
    
    HMAC(EVP_sha256(), key, strlen(key), 
         (const unsigned char*)header_and_payload, strlen(header_and_payload),
         result, &result_len);
    
    if (result_len != (unsigned int)sig_len) {
        return 0;
    }
    
    return memcmp(result, signature, sig_len) == 0;
}

/* JSON 객체 문자열 생성 */
static char* create_json_object(const char* payload, int payload_len) {
    if (!payload || payload_len <= 0) {
        char* empty_json = (char*)malloc(3);
        if (empty_json) {
            strcpy(empty_json, "{}");
        }
        return empty_json;
    }
    
    /* payload는 이미 JSON 문자열이므로 그대로 복사 */
    char* json = (char*)malloc(payload_len + 1);
    if (!json) return NULL;
    
    memcpy(json, payload, payload_len);
    json[payload_len] = '\0';
    
    return json;
}

char* decode_json_web_token(const char* token, const char* key) {
    if (!token || !key) {
        return create_json_object(NULL, 0);
    }
    
    /* JWT 파싱: header.payload.signature */
    char* token_copy = strdup(token);
    if (!token_copy) {
        return create_json_object(NULL, 0);
    }
    
    char* saveptr = NULL;
    char* header_str = strtok_r(token_copy, ".", &saveptr);
    char* payload_str = strtok_r(NULL, ".", &saveptr);
    char* signature_str = strtok_r(NULL, ".", &saveptr);
    
    if (!header_str || !payload_str || !signature_str) {
        free(token_copy);
        return create_json_object(NULL, 0);
    }
    
    /* 서명 검증을 위한 헤더와 페이로드 문자열 생성 */
    int header_len = strlen(header_str);
    int payload_len = strlen(payload_str);
    char* header_and_payload = (char*)malloc(header_len + payload_len + 2);
    if (!header_and_payload) {
        free(token_copy);
        return create_json_object(NULL, 0);
    }
    
    sprintf(header_and_payload, "%s.%s", header_str, payload_str);
    
    /* 서명 디코딩 */
    int sig_len = 0;
    unsigned char* signature = base64url_decode(signature_str, &sig_len);
    
    /* 서명 검증 */
    int is_valid = 0;
    if (signature) {
        is_valid = verify_hmac_sha256(key, header_and_payload, signature, sig_len);
        free(signature);
    }
    
    free(header_and_payload);
    
    if (!is_valid) {
        free(token_copy);
        return create_json_object(NULL, 0);
    }
    
    /* 페이로드 디코딩 */
    int decoded_payload_len = 0;
    unsigned char* decoded_payload = base64url_decode(payload_str, &decoded_payload_len);
    
    char* result = NULL;
    if (decoded_payload) {
        result = create_json_object((const char*)decoded_payload, decoded_payload_len);
        free(decoded_payload);
    } else {
        result = create_json_object(NULL, 0);
    }
    
    free(token_copy);
    return result;
}