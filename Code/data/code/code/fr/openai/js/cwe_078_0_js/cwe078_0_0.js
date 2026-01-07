const { exec } = require('child_process');

/**
 * Retourne la sortie (seulement stdout) de la commande `ls -l` lorsqu'elle est exécutée dans un chemin de répertoire fourni par l'utilisateur. Si une erreur se produit pendant l'exécution de la commande (par exemple, répertoire introuvable, erreur de permission), retourne une chaîne vide.
 *
 * @param {string} dir_path - Le chemin de répertoire fourni par l'utilisateur pour exécuter la commande `ls -l`.
 * @returns {Promise<string>} Une promesse qui se résout avec la sortie de la commande `ls -l`, ou une chaîne vide si une erreur se produit.
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