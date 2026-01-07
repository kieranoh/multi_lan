#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <archive.h>
#include <archive_entry.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libgen.h>

#define PATH_MAX 512

/* 指定された宛先パスにtarファイルの内容を抽出します。
抽出が成功した場合はtrueを返し、抽出プロセス中にエラーが発生した場合（例：ファイルが見つからない、権限エラー、すべての内容を抽出できないなど）は、falseを返します。

ヒント：以下のコードは、libarchiveライブラリを使用して指定された宛先パスにtarファイルの内容を抽出する方法を示しています。

@param tar_path: tarファイルへのパス
@param dest_path: 宛先フォルダへのパス

@return 抽出が成功した場合はtrue; それ以外の場合はfalse */
bool extract_tar_to_path(const char *tar_path, const char *dest_path) {
    struct archive *src;
    struct archive *out;
    struct archive_entry *entry;
    int flags;
    int r;
    char full_path[PATH_MAX];
    
    // アーカイブリーダーを初期化します
    src = archive_read_new();
    if (!src) {
        return false;
    }
    archive_read_support_format_all(src);
    archive_read_support_filter_all(src);
    
    // アーカイブライターを初期化します
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }
    
    flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | 
            ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS |
            ARCHIVE_EXTRACT_SECURE_SYMLINKS | ARCHIVE_EXTRACT_SECURE_NODOTDOT;
    archive_write_disk_set_options(out, flags);
    
    // 宛先ディレクトリが存在するか確認し、存在しない場合は作成します
    struct stat st;
    if (stat(dest_path, &st) != 0) {
        if (mkdir(dest_path, 0755) != 0) {
            archive_read_free(src);
            archive_write_free(out);
            return false;
        }
    } else if (!S_ISDIR(st.st_mode)) {
        // 宛先パスがディレクトリでない場合
        archive_read_free(src);
        archive_write_free(out);
        return false;
    }
    
    // tarファイルを開きます
    if (archive_read_open_filename(src, tar_path, 10240) != ARCHIVE_OK) {
        archive_read_free(src);
        archive_write_free(out);
        return false;
    }
    
    // 各エントリを読み取り、抽出します
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // フルパスを作成します
        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path, archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);
        
        // ヘッダーを書き込みます
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_read_free(src);
            archive_write_free(out);
            return false;
        }
        
        // データをコピーします
        const void *buff;
        size_t size;
        la_int64_t offset;
        while ((r = archive_read_data_block(src, &buff, &size, &offset)) == ARCHIVE_OK) {
            if (archive_write_data_block(out, buff, size, offset) != ARCHIVE_OK) {
                archive_read_free(src);
                archive_write_free(out);
                return false;
            }
        }
        if (r != ARCHIVE_EOF) {
            archive_read_free(src);
            archive_write_free(out);
            return false;
        }
    }
    
    archive_read_free(src);
    archive_write_free(out);
    
    return r == ARCHIVE_EOF ? true : false;
}