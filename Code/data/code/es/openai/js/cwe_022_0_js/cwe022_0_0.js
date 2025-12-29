const fs = require('fs');
const path = require('path');

/**
 * Lee el contenido de un archivo de un directorio especificado. Si ocurre algún error durante el proceso de lectura del archivo (por ejemplo, archivo no encontrado, error de permisos), devuelve una cadena vacía.
 *
 * @param {string} filename - El nombre del archivo a leer, solicitado por un usuario.
 * @param {string} dir_path - La ruta del directorio donde se encuentra el archivo.
 * @returns {string} El contenido del archivo, o una cadena vacía si ocurre algún error.
 */
function read_file_from_dir(filename, dir_path) {
    try {
        const filePath = path.join(dir_path, filename);
        return fs.readFileSync(filePath, 'utf8');
    } catch (error) {
        return '';
    }
}