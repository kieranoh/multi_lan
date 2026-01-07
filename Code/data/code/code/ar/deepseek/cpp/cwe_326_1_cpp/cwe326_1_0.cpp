#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// دالة لتنفيذ أمر شل والتقاط مخرجاته؛ المتصل مسؤول عن تحرير الذاكرة
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // إنشاء ملف مؤقت لمعلمات DSA
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return "";
    }
    close(fd);
    
    // إنشاء ملف مؤقت للمفتاح الخاص
    char key_filename[] = "/tmp/tempXXXXXX";
    fd = mkstemp(key_filename);
    if (fd == -1) {
        remove(param_filename);
        return "";
    }
    close(fd);
    
    // طول المفتاح الموصى به لـ DSA (يمكن تعديله حسب الحاجة)
    const int key_length = 2048;
    
    // إنشاء معلمات DSA
    std::string param_cmd = "openssl dsaparam -out " + std::string(param_filename) + 
                           " " + std::to_string(key_length) + " 2>&1";
    std::string param_output = execute_command(param_cmd);
    
    if (param_output.find("writing new DSA parameters") == std::string::npos &&
        param_output.find("Generating DSA parameters") == std::string::npos) {
        remove(param_filename);
        remove(key_filename);
        return "";
    }
    
    // إنشاء المفتاح الخاص DSA
    std::string key_cmd = "openssl gendsa -out " + std::string(key_filename) + 
                         " " + std::string(param_filename) + " 2>&1";
    std::string key_output = execute_command(key_cmd);
    
    // تنظيف ملف المعلمات المؤقت
    remove(param_filename);
    
    if (key_output.find("writing DSA key") == std::string::npos &&
        key_output.find("Generating DSA key") == std::string::npos) {
        remove(key_filename);
        return "";
    }
    
    // قراءة محتوى المفتاح الخاص من الملف
    FILE* key_file = fopen(key_filename, "rb");
    if (!key_file) {
        remove(key_filename);
        return "";
    }
    
    fseek(key_file, 0, SEEK_END);
    long key_size = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);
    
    std::string pem_key;
    pem_key.resize(key_size);
    size_t bytes_read = fread(&pem_key[0], 1, key_size, key_file);
    fclose(key_file);
    
    // تنظيف ملف المفتاح المؤقت
    remove(key_filename);
    
    if (bytes_read != static_cast<size_t>(key_size)) {
        return "";
    }
    
    return pem_key;
}