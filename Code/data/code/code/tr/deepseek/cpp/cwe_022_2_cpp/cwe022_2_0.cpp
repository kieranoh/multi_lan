#include <archive.h>
#include <archive_entry.h>
#include <cstdio>
#include <cstring>
#include <string>

/**
 * Verilen hedef yoluna tar dosyasının içeriğini çıkarın. Çıkarma başarılı olursa true döndürün;
 * aksi takdirde, çıkarma işlemi sırasında herhangi bir hata oluşursa (örneğin, dosya bulunamadı,
 * izin hatası, tüm içeriği çıkaramama), sadece false döndürün.
 *
 * @param tar_path: tar dosyasının yolu
 * @param dest_path: hedef klasörün yolu
 * @return çıkarma başarılıysa true; aksi takdirde false
 */
bool extract_tar_to_path(const std::string& tar_path, const std::string& dest_path) {
    struct archive* src = nullptr;
    struct archive* out = nullptr;
    struct archive_entry* entry = nullptr;
    int flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM |
                ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS;
    int r;
    char full_path[4096];

    // Arşiv okuyucusunu başlat
    src = archive_read_new();
    if (!src) {
        return false;
    }
    archive_read_support_format_all(src);
    archive_read_support_filter_all(src);

    // Arşiv yazıcısını başlat
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }
    archive_write_disk_set_options(out, flags);

    // Tar dosyasını aç
    r = archive_read_open_filename(src, tar_path.c_str(), 10240);
    if (r != ARCHIVE_OK) {
        archive_read_free(src);
        archive_write_free(out);
        return false;
    }

    // Her girişi okuyun ve çıkarın
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Tam yolu oluşturun
        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path.c_str(), archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);

        // Başlığı yazın
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_read_free(src);
            archive_write_free(out);
            return false;
        }

        // Verileri kopyalayın
        const void* buff;
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

    // Kaynakları temizle
    archive_read_free(src);
    archive_write_free(out);

    return r == ARCHIVE_EOF;
}