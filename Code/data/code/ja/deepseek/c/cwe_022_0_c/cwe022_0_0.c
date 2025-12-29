#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifdef _WIN32
    #include <windows.h>
    #define PATH_SEPARATOR '\\'
#else
    #include <sys/stat.h>
    #include <unistd.h>
    #define PATH_SEPARATOR '/'
#endif

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // 入力パラメータの検証
    if (filename == NULL || dir_path == NULL || filename[0] == '\0') {
        return strdup("");
    }
    
    // フルパスの構築
    size_t dir_len = strlen(dir_path);
    size_t file_len = strlen(filename);
    size_t total_len = dir_len + 1 + file_len + 1; // +1 for separator, +1 for null terminator
    
    char *full_path = (char *)malloc(total_len);
    if (full_path == NULL) {
        return strdup("");
    }
    
    // パスの構築
    strcpy(full_path, dir_path);
    
    // ディレクトリパスの末尾にスラッシュがない場合は追加
    if (dir_len > 0 && dir_path[dir_len - 1] != '/' && dir_path[dir_len - 1] != '\\') {
        full_path[dir_len] = PATH_SEPARATOR;
        strcpy(full_path + dir_len + 1, filename);
    } else {
        strcpy(full_path + dir_len, filename);
    }
    
    // ファイルの存在確認とアクセス権のチェック
    FILE *file = fopen(full_path, "rb");
    if (file == NULL) {
        free(full_path);
        return strdup("");
    }
    
    // ファイルサイズの取得
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    long file_size = ftell(file);
    if (file_size < 0) {
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    rewind(file);
    
    // メモリの確保（null終端用に+1）
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    // ファイル内容の読み込み
    size_t bytes_read = fread(content, 1, file_size, file);
    if (bytes_read != (size_t)file_size) {
        free(content);
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    // null終端を追加
    content[file_size] = '\0';
    
    // リソースの解放
    fclose(file);
    free(full_path);
    
    return content;
}