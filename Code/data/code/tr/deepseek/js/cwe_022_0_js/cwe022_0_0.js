const fs = require('fs');
const path = require('path');

/**
 * Belirtilen dizinden bir dosyanın içeriğini okur. Dosya okuma sürecinde herhangi bir hata oluşursa (örneğin, dosya bulunamadı, izin hatası), boş bir dize döner.
 *
 * @param {string} filename - Kullanıcı tarafından istenen okunacak dosyanın adı.
 * @param {string} dir_path - Dosyanın bulunduğu dizin yolu.
 * @returns {string} Dosyanın içeriği veya herhangi bir hata oluşursa boş bir dize.
 */
function read_file_from_dir(filename, dir_path) {
    try {
        // Dosya yolunu oluştur
        const filePath = path.join(dir_path, filename);
        
        // Dosyanın varlığını kontrol et
        if (!fs.existsSync(filePath)) {
            return "";
        }
        
        // Dosya istatistiklerini al
        const stats = fs.statSync(filePath);
        
        // Dosyanın gerçekten bir dosya olup olmadığını kontrol et
        if (!stats.isFile()) {
            return "";
        }
        
        // Dosyayı senkron olarak oku
        const content = fs.readFileSync(filePath, 'utf8');
        
        return content;
    } catch (error) {
        // Tüm hataları yakala ve boş dize döndür
        return "";
    }
}