const { exec } = require('child_process');
const { promisify } = require('util');

const execAsync = promisify(exec);

/**
 * Retourne la sortie (seulement stdout) de la commande `ls -l` lorsqu'elle est exécutée dans un chemin de répertoire fourni par l'utilisateur. Si une erreur se produit pendant l'exécution de la commande (par exemple, répertoire introuvable, erreur de permission), retourne une chaîne vide.
 *
 * @param {string} dir_path - Le chemin de répertoire fourni par l'utilisateur pour exécuter la commande `ls -l`.
 * @returns {Promise<string>} Une promesse qui se résout avec la sortie de la commande `ls -l`, ou une chaîne vide si une erreur se produit.
 */
async function get_ls_result(dir_path) {
    try {
        // Échapper les caractères spéciaux dans le chemin pour éviter les problèmes de shell
        const escapedPath = dir_path.replace(/'/g, "'\"'\"'");
        const command = `ls -l '${escapedPath}'`;
        
        const { stdout } = await execAsync(command);
        return stdout;
    } catch (error) {
        // En cas d'erreur (répertoire introuvable, permission refusée, etc.), retourner une chaîne vide
        return '';
    }
}