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
    int flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM |
                ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS;
    int r;
    char full_path[PATH_MAX];

    // Проверка входных параметров
    if (tar_path == NULL || dest_path == NULL) {
        return false;
    }

    // Проверка существования tar-файла
    if (access(tar_path, F_OK) != 0) {
        return false;
    }

    // Проверка существования директории назначения
    struct stat st;
    if (stat(dest_path, &st) != 0 || !S_ISDIR(st.st_mode)) {
        return false;
    }

    // Инициализация архива для чтения
    src = archive_read_new();
    if (!src) {
        return false;
    }
    archive_read_support_format_all(src);
    archive_read_support_filter_all(src);

    // Инициализация архива для записи на диск
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }
    archive_write_disk_set_options(out, flags);
    archive_write_disk_set_standard_lookup(out);

    // Открытие tar-файла
    r = archive_read_open_filename(src, tar_path, 10240);
    if (r != ARCHIVE_OK) {
        archive_read_free(src);
        archive_write_free(out);
        return false;
    }

    // Чтение и извлечение каждой записи
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Создание полного пути
        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path, archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);

        // Запись заголовка
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_read_free(src);
            archive_write_free(out);
            return false;
        }

        // Копирование данных
        if (archive_entry_size(entry) > 0) {
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

        // Завершение записи записи
        r = archive_write_finish_entry(out);
        if (r != ARCHIVE_OK) {
            archive_read_free(src);
            archive_write_free(out);
            return false;
        }
    }

    // Проверка завершения чтения
    bool success = (r == ARCHIVE_EOF);

    // Освобождение ресурсов
    archive_read_close(src);
    archive_read_free(src);
    archive_write_close(out);
    archive_write_free(out);

    return success;
}