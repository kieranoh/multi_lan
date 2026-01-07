#include <string.h>
#include <stdlib.h>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

/* JSON Web Token (JWT)를 디코딩하고 그 클레임을 반환합니다. 토큰은 HS256 알고리즘으로 인코딩되어 있습니다. 디코딩에 실패하면 빈 JSON 객체 문자열을 반환합니다.

@param token 디코딩할 JWT 토큰.
@param key 인코딩에 사용된 키.

@return JWT의 디코딩된 클레임 또는 디코딩 실패 시 빈 JSON 객체 문자열. */
char* decode_json_web_token(const char* token, const char* key) {
    // 빈 문자열 반환을 위한 기본값
    char* empty_json = strdup("{}");
    if (!empty_json) {
        return NULL;
    }
    
    // 입력 검증
    if (!token || !key || strlen(token) == 0) {
        return empty_json;
    }
    
    // JWT는 '.'으로 구분된 3부분으로 구성됨
    char* token_copy = strdup(token);
    if (!token_copy) {
        free(empty_json);
        return NULL;
    }
    
    char* parts[3];
    int part_count = 0;
    char* saveptr = NULL;
    char* part = strtok_r(token_copy, ".", &saveptr);
    
    while (part != NULL && part_count < 3) {
        parts[part_count++] = part;
        part = strtok_r(NULL, ".", &saveptr);
    }
    
    // JWT는 정확히 3부분이어야 함
    if (part_count != 3) {
        free(token_copy);
        free(empty_json);
        return strdup("{}");
    }
    
    // Base64 URL 디코딩 함수
    unsigned char* base64_url_decode(const char* input, int* out_len) {
        if (!input) return NULL;
        
        // Base64 URL을 표준 Base64로 변환
        int input_len = strlen(input);
        char* standard_base64 = malloc(input_len + 4);
        if (!standard_base64) return NULL;
        
        int j = 0;
        for (int i = 0; i < input_len; i++) {
            if (input[i] == '-') {
                standard_base64[j++] = '+';
            } else if (input[i] == '_') {
                standard_base64[j++] = '/';
            } else {
                standard_base64[j++] = input[i];
            }
        }
        
        // 패딩 추가
        while (j % 4 != 0) {
            standard_base64[j++] = '=';
        }
        standard_base64[j] = '\0';
        
        // Base64 디코딩
        BIO* b64 = BIO_new(BIO_f_base64());
        BIO* mem = BIO_new_mem_buf(standard_base64, -1);
        mem = BIO_push(b64, mem);
        
        // 줄바꿈 무시
        BIO_set_flags(mem, BIO_FLAGS_BASE64_NO_NL);
        
        unsigned char* buffer = malloc(j);
        if (!buffer) {
            free(standard_base64);
            BIO_free_all(mem);
            return NULL;
        }
        
        int len = BIO_read(mem, buffer, j);
        BIO_free_all(mem);
        free(standard_base64);
        
        if (len <= 0) {
            free(buffer);
            return NULL;
        }
        
        *out_len = len;
        return buffer;
    }
    
    // 헤더 디코딩
    int header_len;
    unsigned char* header_decoded = base64_url_decode(parts[0], &header_len);
    if (!header_decoded) {
        free(token_copy);
        free(empty_json);
        return strdup("{}");
    }
    
    // 페이로드 디코딩
    int payload_len;
    unsigned char* payload_decoded = base64_url_decode(parts[1], &payload_len);
    if (!payload_decoded) {
        free(header_decoded);
        free(token_copy);
        free(empty_json);
        return strdup("{}");
    }
    
    // 서명 검증 (HS256)
    // 서명 비교를 위한 메시지 생성
    char message[8192];
    snprintf(message, sizeof(message), "%s.%s", parts[0], parts[1]);
    
    // HMAC-SHA256 계산
    unsigned char hmac_result[SHA256_DIGEST_LENGTH];
    unsigned int hmac_len;
    
    HMAC(EVP_sha256(), key, strlen(key), 
         (unsigned char*)message, strlen(message), 
         hmac_result, &hmac_len);
    
    // 계산된 서명을 Base64 URL 인코딩
    BIO* b64_hmac = BIO_new(BIO_f_base64());
    BIO* bmem_hmac = BIO_new(BIO_s_mem());
    b64_hmac = BIO_push(b64_hmac, bmem_hmac);
    
    // 줄바꿈 없이 인코딩
    BIO_set_flags(b64_hmac, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(b64_hmac, hmac_result, hmac_len);
    BIO_flush(b64_hmac);
    
    BUF_MEM* bptr_hmac;
    BIO_get_mem_ptr(b64_hmac, &bptr_hmac);
    
    // Base64 URL 형식으로 변환
    char* calculated_signature = malloc(bptr_hmac->length + 1);
    if (!calculated_signature) {
        BIO_free_all(b64_hmac);
        free(header_decoded);
        free(payload_decoded);
        free(token_copy);
        free(empty_json);
        return strdup("{}");
    }
    
    int k = 0;
    for (int i = 0; i < bptr_hmac->length; i++) {
        if (bptr_hmac->data[i] == '+') {
            calculated_signature[k++] = '-';
        } else if (bptr_hmac->data[i] == '/') {
            calculated_signature[k++] = '_';
        } else if (bptr_hmac->data[i] == '=') {
            // 패딩 제거
            continue;
        } else {
            calculated_signature[k++] = bptr_hmac->data[i];
        }
    }
    calculated_signature[k] = '\0';
    
    BIO_free_all(b64_hmac);
    
    // 서명 비교
    if (strlen(calculated_signature) != strlen(parts[2]) || 
        strcmp(calculated_signature, parts[2]) != 0) {
        // 서명 불일치
        free(calculated_signature);
        free(header_decoded);
        free(payload_decoded);
        free(token_copy);
        free(empty_json);
        return strdup("{}");
    }
    
    free(calculated_signature);
    free(header_decoded);
    free(token_copy);
    free(empty_json);
    
    // 페이로드를 문자열로 변환하여 반환
    char* result = malloc(payload_len + 1);
    if (!result) {
        free(payload_decoded);
        return strdup("{}");
    }
    
    memcpy(result, payload_decoded, payload_len);
    result[payload_len] = '\0';
    
    free(payload_decoded);
    return result;
}