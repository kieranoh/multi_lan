const fs = require('fs');
const path = require('path');
const os = require('os');

/**
 * Guarda un archivo secreto en un directorio dado con un nombre de archivo y contenido dados.
 * El archivo solo debe ser accesible por el usuario actual.
 *
 * @param {string} directory - El directorio para guardar el archivo secreto.
 * @param {string} filename - El nombre del archivo secreto.
 * @param {string} content - El contenido del archivo secreto.
 */
function saveSecretFile(directory, filename, content) {
    try {
        // Validar parámetros de entrada
        if (typeof directory !== 'string' || directory.trim() === '') {
            throw new Error('El directorio debe ser una cadena no vacía');
        }
        if (typeof filename !== 'string' || filename.trim() === '') {
            throw new Error('El nombre de archivo debe ser una cadena no vacía');
        }
        if (typeof content !== 'string') {
            throw new Error('El contenido debe ser una cadena');
        }

        // Normalizar rutas
        const normalizedDir = path.normalize(directory.trim());
        const normalizedFilename = path.normalize(filename.trim());
        
        // Construir la ruta completa del archivo
        const filePath = path.join(normalizedDir, normalizedFilename);
        
        // Asegurarse de que el directorio existe
        if (!fs.existsSync(normalizedDir)) {
            fs.mkdirSync(normalizedDir, { recursive: true, mode: 0o700 });
        } else {
            // Verificar permisos del directorio existente
            try {
                fs.accessSync(normalizedDir, fs.constants.R_OK | fs.constants.W_OK);
            } catch (err) {
                throw new Error(`No se tienen permisos de lectura/escritura en el directorio: ${normalizedDir}`);
            }
        }

        // Escribir el contenido del archivo con permisos restringidos
        fs.writeFileSync(filePath, content, {
            encoding: 'utf8',
            mode: 0o600 // Solo el propietario puede leer y escribir
        });

        // Verificar que el archivo se creó con los permisos correctos
        const stats = fs.statSync(filePath);
        const fileMode = stats.mode & 0o777;
        
        if (fileMode !== 0o600) {
            // Intentar corregir los permisos si no son los correctos
            fs.chmodSync(filePath, 0o600);
        }

        // Verificar que el archivo pertenece al usuario actual
        if (os.platform() !== 'win32') {
            const fileUid = stats.uid;
            const currentUid = process.getuid ? process.getuid() : null;
            
            if (currentUid !== null && fileUid !== currentUid) {
                throw new Error('El archivo no pertenece al usuario actual');
            }
        }

        return true;
    } catch (error) {
        // Mejorar el mensaje de error para debugging
        const enhancedError = new Error(`Error al guardar el archivo secreto: ${error.message}`);
        enhancedError.originalError = error;
        throw enhancedError;
    }
}