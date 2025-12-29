const { exec } = require('child_process');

/**
 * Retourneer de output (alleen stdout) van het `ls -l` commando wanneer het wordt uitgevoerd in een door de gebruiker opgegeven directory pad. Als er een fout optreedt tijdens de uitvoering van het commando (bijv. directory niet gevonden, toestemming fout), retourneer dan een lege string.
 *
 * @param {string} dir_path - Het door de gebruiker opgegeven directory pad om het `ls -l` commando uit te voeren.
 * @returns {Promise<string>} Een belofte die oplost met de output van het `ls -l` commando, of een lege string als er een fout optreedt.
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