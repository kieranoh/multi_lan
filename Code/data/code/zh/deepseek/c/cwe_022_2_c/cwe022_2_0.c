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

bool extract_tar_to_path(const char *tar_path, const char *dest_path) {
    struct archive *src = NULL;
    struct archive *out = NULL;
    struct archive_entry *entry = NULL;
    int r;
    int flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS;
    char full_path[PATH_MAX];

    // 检查目标路径是否存在，如果不存在则创建
    struct stat st;
    if (stat(dest_path, &st) != 0) {
        if (mkdir(dest_path, 0755) != 0) {
            return false;
        }
    }

    // 初始化归档读取器
    src = archive_read_new();
    if (!src) {
        return false;
    }
    archive_read_support_format_all(src);
    archive_read_support_filter_all(src);

    // 初始化归档写入器
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }
    archive_write_disk_set_options(out, flags);
    archive_write_disk_set_standard_lookup(out);

    // 打开tar文件
    if (archive_read_open_filename(src, tar_path, 10240) != ARCHIVE_OK) {
        archive_read_free(src);
        archive_write_free(out);
        return false;
    }

    // 读取并提取每个条目
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // 创建完整路径
        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path, archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);

        // 写入头部
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_read_free(src);
            archive_write_free(out);
            return false;
        }

        // 复制数据
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

        // 完成写入当前条目
        r = archive_write_finish_entry(out);
        if (r != ARCHIVE_OK) {
            archive_read_free(src);
            archive_write_free(out);
            return false;
        }
    }

    // 清理资源
    archive_read_free(src);
    archive_write_free(out);

    // 检查是否成功读取到文件末尾
    return r == ARCHIVE_EOF ? true : false;
}