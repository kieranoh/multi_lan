const fs = require('fs');
const path = require('path');

/**
 * Читает содержимое файла из указанного каталога. Если во время чтения файла возникает ошибка (например, файл не найден, ошибка доступа), возвращает пустую строку.
 *
 * @param {string} filename - Имя файла для чтения, запрашиваемое пользователем.
 * @param {string} dir_path - Путь к каталогу, где находится файл.
 * @returns {string} Содержимое файла или пустая строка, если произошла ошибка.
 */
function read_file_from_dir(filename, dir_path) {
    const filePath = path.join(dir_path, filename);
    try {
        const data = fs.readFileSync(filePath, 'utf8');
        return data;
    } catch (error) {
        return '';
    }
}