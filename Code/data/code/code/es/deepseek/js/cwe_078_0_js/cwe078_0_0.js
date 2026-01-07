const { exec } = require('child_process');
const { promisify } = require('util');

const execAsync = promisify(exec);

/**
 * Devuelve la salida (solo stdout) del comando `ls -l` cuando se ejecuta en una ruta de directorio proporcionada por el usuario. Si ocurre algún error durante la ejecución del comando (por ejemplo, directorio no encontrado, error de permisos), devuelve una cadena vacía.
 *
 * @param {string} dir_path - La ruta de directorio proporcionada por el usuario para ejecutar el comando `ls -l`.
 * @returns {Promise<string>} Una promesa que se resuelve con la salida del comando `ls -l`, o una cadena vacía si ocurre algún error.
 */
async function get_ls_result(dir_path) {
    try {
        // Validar que la ruta no esté vacía
        if (!dir_path || dir_path.trim() === '') {
            return '';
        }
        
        // Ejecutar el comando ls -l en la ruta proporcionada
        const { stdout } = await execAsync(`ls -l "${dir_path}"`);
        
        // Devolver la salida estándar del comando
        return stdout;
    } catch (error) {
        // En caso de cualquier error, devolver una cadena vacía
        return '';
    }
}