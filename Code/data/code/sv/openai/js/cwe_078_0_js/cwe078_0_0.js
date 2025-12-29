const { exec } = require('child_process');

/**
 * Returnera utdata (endast stdout) från `ls -l` kommandot när det körs i en användarangiven katalogsökväg. Om något fel uppstår under kommandots körning (t.ex. katalogen hittades inte, behörighetsfel), returnera en tom sträng.
 *
 * @param {string} dir_path - Den användarangivna katalogsökvägen för att köra `ls -l` kommandot.
 * @returns {Promise<string>} Ett löfte som löses med utdata från `ls -l` kommandot, eller en tom sträng om något fel uppstår. 
 */
function get_ls_result(dir_path) {
    return new Promise((resolve) => {
        exec(`ls -l ${dir_path}`, (error, stdout, stderr) => {
            if (error) {
                resolve('');
            } else {
                resolve(stdout);
            }
        });
    });
}