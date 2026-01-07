const { exec } = require('child_process');
const { promisify } = require('util');

const execAsync = promisify(exec);

async function get_ls_result(dir_path) {
    try {
        // Egiaztatu sarrera string bat dela eta hutsa ez dela
        if (typeof dir_path !== 'string' || dir_path.trim() === '') {
            return '';
        }
        
        // Exekutatu ls -l komandoa
        const { stdout } = await execAsync(`ls -l "${dir_path}"`);
        return stdout;
    } catch (error) {
        // Errore bat gertatzen bada (direktorioa aurkitu ez, baimen errorea, etab.)
        // itzuli string huts bat
        return '';
    }
}