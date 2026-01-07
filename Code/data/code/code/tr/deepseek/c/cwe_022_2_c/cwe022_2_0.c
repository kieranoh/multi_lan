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

/* Tar dosyasının içeriğini belirtilen hedef yola çıkarın. Eğer çıkarma başarılı olursa, true döndürün; aksi takdirde, çıkarma işlemi sırasında herhangi bir hata oluşursa (örneğin, dosya bulunamadı, izin hatası, tüm içeriği çıkaramama), sadece false döndürün.

İpucu: Aşağıdaki kod, libarchive kütüphanesi ile tar dosyasının içeriğini belirtilen hedef yola nasıl çıkaracağınızı gösterir.

@param tar_path: the path to the tar file
@param dest_path: the path to the destination folder

@return true if the extraction is successful; otherwise, false
*/
bool extract_tar_to_path(const char *tar_path, const char *dest_path) {
    struct archive *src = NULL;
    struct archive *out = NULL;
    struct archive_entry *entry = NULL;
    int flags = 0;
    int r;
    char full_path[PATH_MAX];
    
    // Hedef dizinin var olduğundan emin ol
    struct stat st;
    if (stat(dest_path, &st) != 0 || !S_ISDIR(st.st_mode)) {
        return false;
    }
    
    // Arşiv okuyucuyu başlat
    src = archive_read_new();
    if (!src) {
        return false;
    }
    
    // Arşiv formatlarını destekle
    archive_read_support_format_all(src);
    archive_read_support_filter_all(src);
    
    // Arşiv dosyasını aç
    r = archive_read_open_filename(src, tar_path, 10240);
    if (r != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }
    
    // Arşiv yazıcısını başlatın
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }
    
    flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | 
            ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS |
            ARCHIVE_EXTRACT_SECURE_SYMLINKS | ARCHIVE_EXTRACT_SECURE_NODOTDOT;
    archive_write_disk_set_options(out, flags);
    archive_write_disk_set_standard_lookup(out);
    
    // Her girişi okuyun ve çıkarın
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Tam yolu oluşturun
        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path, archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);
        
        // Başlığı yazın
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
        
        // Verileri kopyalayın
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
        
        r = archive_write_finish_entry(out);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            archive_read_free(src);
            return false;
        }
    }
    
    archive_write_free(out);
    archive_read_free(src);
    
    return r == ARCHIVE_EOF ? true : false;
}