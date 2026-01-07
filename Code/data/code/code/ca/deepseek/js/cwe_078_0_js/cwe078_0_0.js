const { exec } = require('child_process');
const { promisify } = require('util');

const execAsync = promisify(exec);

async function get_ls_result(dir_path) {
    try {
        // Validar que el paràmetre sigui una cadena no buida
        if (typeof dir_path !== 'string' || dir_path.trim() === '') {
            return '';
        }

        // Netejar el camí per evitar injecció de comandes
        const cleanPath = dir_path.replace(/[;&|`$(){}[\]<>]/g, '');
        
        // Executar la comanda ls -l amb el camí proporcionat
        const { stdout } = await execAsync(`ls -l "${cleanPath}"`);
        
        // Retornar la sortida estàndard
        return stdout;
    } catch (error) {
        // En cas de qualsevol error, retornar cadena buida
        return '';
    }
}