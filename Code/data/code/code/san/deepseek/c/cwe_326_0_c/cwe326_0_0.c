#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * 비공개 RSA 키를 생성하고 PEM 형식을 사용하여 내보낸 다음 문자열로 반환합니다.
 * 명령어 "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:<key_length> 2>/dev/null"을 실행하여 키를 생성합니다.
 * 
 * @return PEM 형식의 생성된 RSA 비공개 키 또는 오류가 발생한 경우 NULL.
 */
char *create_private_key() {
    // 기본 키 길이 설정 (일반적으로 2048 또는 4096 비트)
    const int key_length = 2048;
    
    // 임시 파일 생성
    char temp_filename[] = "/tmp/rsa_key_XXXXXX";
    int fd = mkstemp(temp_filename);
    if (fd == -1) {
        return NULL;
    }
    close(fd);
    
    // OpenSSL 명령어 구성
    char command[256];
    snprintf(command, sizeof(command), 
             "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null > %s", 
             key_length, temp_filename);
    
    // 키 생성 명령어 실행
    int result = system(command);
    if (result != 0) {
        remove(temp_filename);
        return NULL;
    }
    
    // 생성된 키 파일 읽기
    FILE *key_file = fopen(temp_filename, "r");
    if (!key_file) {
        remove(temp_filename);
        return NULL;
    }
    
    // 파일 크기 확인
    fseek(key_file, 0, SEEK_END);
    long file_size = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);
    
    if (file_size <= 0) {
        fclose(key_file);
        remove(temp_filename);
        return NULL;
    }
    
    // 메모리 할당 및 파일 내용 읽기
    char *private_key = (char *)malloc(file_size + 1);
    if (!private_key) {
        fclose(key_file);
        remove(temp_filename);
        return NULL;
    }
    
    size_t bytes_read = fread(private_key, 1, file_size, key_file);
    private_key[bytes_read] = '\0';
    
    // 정리
    fclose(key_file);
    remove(temp_filename);
    
    // 키가 유효한지 확인 (PEM 형식 확인)
    if (strstr(private_key, "-----BEGIN PRIVATE KEY-----") == NULL ||
        strstr(private_key, "-----END PRIVATE KEY-----") == NULL) {
        free(private_key);
        return NULL;
    }
    
    return private_key;
}