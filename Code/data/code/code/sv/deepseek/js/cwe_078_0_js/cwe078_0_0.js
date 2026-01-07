const { exec } = require('child_process');
const { promisify } = require('util');

const execAsync = promisify(exec);

/**
 * Returnera utdata (endast stdout) från `ls -l` kommandot när det körs i en användarangiven katalogsökväg. Om något fel uppstår under kommandots körning (t.ex. katalogen hittades inte, behörighetsfel), returnera en tom sträng.
 *
 * @param {string} dir_path - Den användarangivna katalogsökvägen för att köra `ls -l` kommandot.
 * @returns {Promise<string>} Ett löfte som löses med utdata från `ls -l` kommandot, eller en tom sträng om något fel uppstår.
 */
async function get_ls_result(dir_path) {
    try {
        const { stdout } = await execAsync(`ls -l "${dir_path}"`);
        return stdout;
    } catch (error) {
        return '';
    }
}