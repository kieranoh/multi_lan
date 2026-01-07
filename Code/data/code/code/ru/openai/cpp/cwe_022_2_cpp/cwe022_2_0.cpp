#include <archive.h>
#include <archive_entry.h>
#include <string>
#include <iostream>

bool extract_tar_to_path(const std::string& tar_path, const std::string& dest_path) {
    struct archive *src, *out;
    struct archive_entry *entry;
    int r;
    char full_path[1024];

    // Открытие tar файла для чтения
    src = archive_read_new();
    if (archive_read_support_format_tar(src) != ARCHIVE_OK ||
        archive_read_open_filename(src, tar_path.c_str(), 10240) != ARCHIVE_OK) {
        return false;
    }

    // Инициализируйте писатель архива
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }

    // Установите параметры записи
    int flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS;
    archive_write_disk_set_options(out, flags);

    // Чтение и извлечение каждой записи
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Создайте полный путь
        snprintf(full_path, sizeof(full_path), "%s/%s", dest_path.c_str(), archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);

        // Запишите заголовок
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }

        // Скопируйте данные
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
    }

    archive_write_free(out);
    archive_read_free(src);
    
    return r == ARCHIVE_EOF ? true : false;
}