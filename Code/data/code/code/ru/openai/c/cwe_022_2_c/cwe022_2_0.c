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
    struct archive *src;
    struct archive *out;
    struct archive_entry *entry;
    int r;
    char full_path[PATH_MAX];

    // Открытие архива для чтения
    src = archive_read_new();
    if (archive_read_support_format_tar(src) != ARCHIVE_OK) {
        return false;
    }
    if ((r = archive_read_open_filename(src, tar_path, 10240)) != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }

    // Инициализация писателя архива
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }

    // Установка опций для записи
    int flags = ARCHIVE_EXTRACT_OWNER | ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_TIME;
    archive_write_disk_set_options(out, flags);

    // Чтение и извлечение каждой записи
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Создайте полный путь
        snprintf(full_path, sizeof(full_path), "%s/%s", dest_path, archive_entry_pathname(entry));
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

    // Освобождение ресурсов
    archive_write_free(out);
    archive_read_free(src);
    return r == ARCHIVE_EOF ? true : false;
}