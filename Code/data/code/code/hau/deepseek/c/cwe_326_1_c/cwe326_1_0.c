char* create_dsa_key() {
    const int key_length = 2048;
    char param_filename[] = "/tmp/tempXXXXXX";
    char key_filename[] = "/tmp/keyXXXXXX";
    char* result = NULL;
    char command[512];
    int fd_param, fd_key;
    
    // DSA 매개변수를 위한 임시 파일 생성
    fd_param = mkstemp(param_filename);
    if (fd_param == -1) {
        return NULL;
    }
    close(fd_param);
    
    // DSA 키를 위한 임시 파일 생성
    fd_key = mkstemp(key_filename);
    if (fd_key == -1) {
        unlink(param_filename);
        return NULL;
    }
    close(fd_key);
    
    // 1. DSA 매개변수 생성
    snprintf(command, sizeof(command), 
             "openssl dsaparam -out %s %d", param_filename, key_length);
    char* output1 = execute_command(command);
    if (output1) {
        free(output1);
    } else {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // 2. DSA 개인 키 생성
    snprintf(command, sizeof(command), 
             "openssl gendsa %s -out %s", param_filename, key_filename);
    char* output2 = execute_command(command);
    if (output2) {
        free(output2);
    } else {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // 3. 생성된 키 파일 읽기
    FILE* key_file = fopen(key_filename, "r");
    if (key_file) {
        fseek(key_file, 0, SEEK_END);
        long file_size = ftell(key_file);
        fseek(key_file, 0, SEEK_SET);
        
        result = (char*)malloc(file_size + 1);
        if (result) {
            size_t bytes_read = fread(result, 1, file_size, key_file);
            result[bytes_read] = '\0';
        }
        fclose(key_file);
    }
    
    // 임시 파일 정리
    unlink(param_filename);
    unlink(key_filename);
    
    return result;
}