#include <archive.h>
#include <archive_entry.h>
#include <string>
#include <cstring>
#include <cerrno>
#include <sys/stat.h>

bool extract_tar_to_path(const std::string& tar_path, const std::string& dest_path) {
    struct archive *src = nullptr;
    struct archive *out = nullptr;
    struct archive_entry *entry = nullptr;
    int flags = 0;
    int r = 0;
    char full_path[4096];

    // 创建目标目录（如果不存在）
    struct stat st;
    if (stat(dest_path.c_str(), &st) != 0) {
        if (mkdir(dest_path.c_str(), 0755) != 0 && errno != EEXIST) {
            return false;
        }
    }

    // 初始化读取归档
    src = archive_read_new();
    if (!src) {
        return false;
    }
    archive_read_support_format_tar(src);
    archive_read_support_filter_all(src);

    // 打开tar文件
    r = archive_read_open_filename(src, tar_path.c_str(), 10240);
    if (r != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }

    // 初始化归档写入器
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }
    
    // 设置提取选项
    flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | 
            ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS |
            ARCHIVE_EXTRACT_SECURE_SYMLINKS | ARCHIVE_EXTRACT_SECURE_NODOTDOT;
    archive_write_disk_set_options(out, flags);
    archive_write_disk_set_standard_lookup(out);

    // 读取并提取每个条目
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // 创建完整路径
        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path.c_str(), archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);

        // 写入头部
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }

        // 复制数据
        const void *buff;
        size_t size;
        la_int64_t offset;
        while ((r = archive_read_data_block(src, &buff, &size, &offset)) == ARCHIVE_OK) {
            if (archive_write_data_block(out, buff, size, offset) != ARCHIVE_OK) {
                archive_write_free(out);
                archive_read_free(src);
                return false;
            }
        }
        
        if (r != ARCHIVE_EOF) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }

        // 完成当前条目的写入
        r = archive_write_finish_entry(out);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
    }

    // 清理资源
    archive_write_free(out);
    archive_read_free(src);

    // 检查是否成功读取到归档结束
    return (r == ARCHIVE_EOF);
}