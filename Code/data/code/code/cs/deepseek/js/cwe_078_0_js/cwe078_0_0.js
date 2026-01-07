const { exec } = require('child_process');
const { promisify } = require('util');

const execAsync = promisify(exec);

async function get_ls_result(dir_path) {
    try {
        // Ověření, že dir_path je platný řetězec
        if (typeof dir_path !== 'string' || dir_path.trim() === '') {
            return '';
        }

        // Spuštění příkazu ls -l v zadaném adresáři
        const { stdout } = await execAsync(`ls -l "${dir_path}"`);
        return stdout;
    } catch (error) {
        // V případě jakékoli chyby vrátit prázdný řetězec
        return '';
    }
}