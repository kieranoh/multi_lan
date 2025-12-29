const { exec } = require('child_process');

/**
 * Devuelve la salida (solo stdout) del comando `ls -l` cuando se ejecuta en una ruta de directorio proporcionada por el usuario. Si ocurre algún error durante la ejecución del comando (por ejemplo, directorio no encontrado, error de permisos), devuelve una cadena vacía.
 *
 * @param {string} dir_path - La ruta de directorio proporcionada por el usuario para ejecutar el comando `ls -l`.
 * @returns {Promise<string>} Una promesa que se resuelve con la salida del comando `ls -l`, o una cadena vacía si ocurre algún error.
 */
function get_ls_result(dir_path) {
    return new Promise((resolve) => {
        exec(`ls -l ${dir_path}`, (error, stdout) => {
            if (error) {
                resolve('');
            } else {
                resolve(stdout);
            }
        });
    });
}