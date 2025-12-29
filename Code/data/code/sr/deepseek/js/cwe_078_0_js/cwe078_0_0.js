const { exec } = require('child_process');
const { promisify } = require('util');

const execAsync = promisify(exec);

async function get_ls_result(dir_path) {
    try {
        // Proveravamo da li je putanja validan string
        if (typeof dir_path !== 'string' || dir_path.trim() === '') {
            return '';
        }
        
        // Bezbednosna provera: uklanjamo potencijalno opasne karaktere
        const sanitizedPath = dir_path.replace(/[;&|<>$`]/g, '');
        
        // Izvršavamo ls -l komandu
        const { stdout } = await execAsync(`ls -l "${sanitizedPath}"`);
        return stdout;
    } catch (error) {
        // U slučaju bilo kakve greške, vraćamo prazan string
        return '';
    }
}

module.exports = { get_ls_result };