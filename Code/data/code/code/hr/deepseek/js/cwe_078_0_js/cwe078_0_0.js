const { exec } = require('child_process');
const { promisify } = require('util');

const execAsync = promisify(exec);

/**
 * Vraća izlaz (samo stdout) `ls -l` naredbe kada se izvrši u korisnički zadanom putu do direktorija.
 * Ako dođe do bilo kakve pogreške tijekom izvršenja naredbe (npr. direktorij nije pronađen, pogreška s dozvolama), vraća prazni niz.
 *
 * @param {string} dir_path - Korisnički zadan put do direktorija za izvršenje `ls -l` naredbe.
 * @returns {Promise<string>} Promesa koja se rješava s izlazom `ls -l` naredbe, ili praznim nizom ako dođe do bilo kakve pogreške.
 */
async function get_ls_result(dir_path) {
    try {
        // Provjera je li put valjan string
        if (typeof dir_path !== 'string' || dir_path.trim() === '') {
            return '';
        }
        
        // Escapiranje specijalnih znakova u putu za sigurno izvršenje naredbe
        const escapedPath = dir_path.replace(/'/g, "'\"'\"'");
        const command = `ls -l '${escapedPath}'`;
        
        // Izvršavanje naredbe
        const { stdout } = await execAsync(command);
        
        // Vraćanje stdout-a
        return stdout;
    } catch (error) {
        // U slučaju bilo kakve pogreške, vraćamo prazan string
        return '';
    }
}