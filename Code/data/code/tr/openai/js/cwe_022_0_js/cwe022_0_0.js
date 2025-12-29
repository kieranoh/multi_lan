/**
 * Belirtilen dizinden bir dosyanın içeriğini okur. Dosya okuma sürecinde herhangi bir hata oluşursa (örneğin, dosya bulunamadı, izin hatası), boş bir dize döner.
 *
 * @param {string} filename - Kullanıcı tarafından istenen okunacak dosyanın adı.
 * @param {string} dir_path - Dosyanın bulunduğu dizin yolu.
 * @returns {string} Dosyanın içeriği veya herhangi bir hata oluşursa boş bir dize.
 */
function read_file_from_dir(filename, dir_path) {
    const fs = require('fs');
    const path = require('path');

    const filePath = path.join(dir_path, filename);
    
    try {
        const data = fs.readFileSync(filePath, 'utf8');
        return data;
    } catch (error) {
        return '';
    }
}