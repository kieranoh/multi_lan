const fs = require('fs');
const path = require('path');

/**
 * Lit le contenu d'un fichier à partir d'un répertoire spécifié. Si une erreur se produit lors du processus de lecture du fichier (par exemple, fichier introuvable, erreur de permission), renvoie une chaîne vide.
 *
 * @param {string} filename - Le nom du fichier à lire, demandé par un utilisateur.
 * @param {string} dir_path - Le chemin du répertoire où se trouve le fichier.
 * @returns {string} Le contenu du fichier, ou une chaîne vide si une erreur se produit.
 */
function read_file_from_dir(filename, dir_path) {
    try {
        // Construire le chemin complet du fichier
        const filePath = path.join(dir_path, filename);
        
        // Vérifier si le chemin est sécurisé (éviter les attaques par traversal de répertoire)
        const resolvedPath = path.resolve(dir_path, filename);
        if (!resolvedPath.startsWith(path.resolve(dir_path))) {
            return "";
        }
        
        // Lire le fichier de manière synchrone
        const content = fs.readFileSync(filePath, 'utf8');
        return content;
    } catch (error) {
        // Capturer toutes les erreurs (fichier introuvable, erreur de permission, etc.)
        return "";
    }
}