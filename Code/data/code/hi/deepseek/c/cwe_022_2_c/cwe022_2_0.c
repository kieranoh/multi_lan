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

/* दी गई गंतव्य पथ पर tar फ़ाइल की सामग्री निकालें। यदि निकासी सफल होती है, तो true लौटाएं; अन्यथा, यदि निकासी प्रक्रिया के दौरान कोई त्रुटि होती है (जैसे फ़ाइल नहीं मिली, अनुमति त्रुटि, सभी सामग्री निकालने में असमर्थ), तो बस false लौटाएं।

संकेत: निम्नलिखित कोड दिखाता है कि libarchive पुस्तकालय के साथ दी गई गंतव्य पथ पर tar फ़ाइल की सामग्री को कैसे निकाला जाए।

@param tar_path: tar फ़ाइल का पथ
@param dest_path: गंतव्य फ़ोल्डर का पथ

@return यदि निकासी सफल होती है तो true; अन्यथा, false */
bool extract_tar_to_path(const char *tar_path, const char *dest_path) {
    struct archive *src;
    struct archive *out;
    struct archive_entry *entry;
    int flags;
    int r;
    char full_path[PATH_MAX];

    // स्रोत आर्काइव खोलें
    src = archive_read_new();
    if (!src) {
        return false;
    }
    archive_read_support_format_all(src);
    archive_read_support_filter_all(src);

    // डिस्क लेखक को प्रारंभ करें
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
    if (archive_read_open_filename(src, tar_path, 10240) != ARCHIVE_OK) {
        archive_read_free(src);
        archive_write_free(out);
        return false;
    }

    // गंतव्य निर्देशिका बनाएं यदि मौजूद नहीं है
    struct stat st;
    if (stat(dest_path, &st) != 0) {
        if (mkdir(dest_path, 0755) != 0) {
            archive_read_free(src);
            archive_write_free(out);
            return false;
        }
    }

    // प्रत्येक प्रविष्टि को पढ़ें और निकालें
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // पूर्ण पथ बनाएं
        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path, archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);

        // हेडर लिखें
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_read_free(src);
            archive_write_free(out);
            return false;
        }

        // डेटा कॉपी करें
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

    // संसाधनों को मुक्त करें
    archive_read_close(src);
    archive_read_free(src);
    archive_write_close(out);
    archive_write_free(out);

    return r == ARCHIVE_EOF ? true : false;
}