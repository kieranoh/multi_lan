#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *create_private_key() {
    // Postavi zadani broj bitova za RSA ključ
    const int key_length = 2048;
    
    // Stvori privremenu datoteku za spremanje ključa
    char temp_filename[] = "/tmp/rsa_key_XXXXXX";
    int fd = mkstemp(temp_filename);
    if (fd == -1) {
        return NULL;
    }
    close(fd);
    
    // Izgradi naredbu za OpenSSL
    char command[256];
    snprintf(command, sizeof(command), 
             "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d -out %s 2>/dev/null", 
             key_length, temp_filename);
    
    // Izvrši naredbu za generiranje ključa
    int result = system(command);
    if (result != 0) {
        remove(temp_filename);
        return NULL;
    }
    
    // Otvori generiranu datoteku s ključem
    FILE *key_file = fopen(temp_filename, "r");
    if (key_file == NULL) {
        remove(temp_filename);
        return NULL;
    }
    
    // Odredi veličinu datoteke
    fseek(key_file, 0, SEEK_END);
    long file_size = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);
    
    if (file_size <= 0) {
        fclose(key_file);
        remove(temp_filename);
        return NULL;
    }
    
    // Alociraj memoriju za sadržaj ključa
    char *key_content = (char *)malloc(file_size + 1);
    if (key_content == NULL) {
        fclose(key_file);
        remove(temp_filename);
        return NULL;
    }
    
    // Pročitaj sadržaj datoteke
    size_t bytes_read = fread(key_content, 1, file_size, key_file);
    key_content[bytes_read] = '\0';
    
    // Očisti
    fclose(key_file);
    remove(temp_filename);
    
    // Provjeri je li ključ ispravno generiran
    if (bytes_read == 0 || strstr(key_content, "-----BEGIN PRIVATE KEY-----") == NULL) {
        free(key_content);
        return NULL;
    }
    
    return key_content;
}