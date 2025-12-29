#include <archive.h>
#include <archive_entry.h>
#include <string>
#include <cstring>

bool extract_tar_to_path(const std::string& tar_path, const std::string& dest_path) {
    struct archive *src = nullptr;
    struct archive *out = nullptr;
    struct archive_entry *entry = nullptr;
    int flags = 0;
    int r = 0;
    char full_path[4096];

    // आर्काइव रीडर को प्रारंभ करें
    src = archive_read_new();
    if (!src) {
        return false;
    }
    
    // आर्काइव रीडर सेटिंग्स
    archive_read_support_format_all(src);
    archive_read_support_filter_all(src);
    
    // आर्काइव लेखक को प्रारंभ करें
    out = archive_write_disk_new();
    if (!out) {
        archive_read_free(src);
        return false;
    }
    
    // डिस्क लेखन विकल्प सेट करें
    flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | 
            ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS |
            ARCHIVE_EXTRACT_SECURE_SYMLINKS | ARCHIVE_EXTRACT_SECURE_NODOTDOT;
    archive_write_disk_set_options(out, flags);
    archive_write_disk_set_standard_lookup(out);
    
    // tar फ़ाइल खोलें
    r = archive_read_open_filename(src, tar_path.c_str(), 10240);
    if (r != ARCHIVE_OK) {
        archive_read_free(src);
        archive_write_free(out);
        return false;
    }
    
    // प्रत्येक प्रविष्टि को पढ़ें और निकालें
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // पूर्ण पथ बनाएं
        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path.c_str(), archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);
        
        // हेडर लिखें
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_read_free(src);
            archive_write_free(out);
            return false;
        }
        
        // डेटा कॉपी करें
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
        
        // प्रविष्टि समाप्त करें
        r = archive_write_finish_entry(out);
        if (r != ARCHIVE_OK) {
            archive_read_free(src);
            archive_write_free(out);
            return false;
        }
    }
    
    // संसाधनों को मुक्त करें
    archive_read_close(src);
    archive_read_free(src);
    archive_write_close(out);
    archive_write_free(out);
    
    // सफलता की जाँच करें
    return (r == ARCHIVE_EOF);
}