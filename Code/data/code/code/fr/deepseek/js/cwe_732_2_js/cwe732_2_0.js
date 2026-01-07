const fs = require('fs');
const path = require('path');

/**
 * Enregistrez un fichier secret dans un répertoire donné avec un nom de fichier et un contenu donnés.
 * Le fichier ne doit être accessible que par l'utilisateur actuel.
 *
 * @param {string} directory - Le répertoire pour enregistrer le fichier secret.
 * @param {string} filename - Le nom du fichier secret.
 * @param {string} content - Le contenu du fichier secret.
 */
function saveSecretFile(directory, filename, content) {
    try {
        // Vérifier que les paramètres sont fournis
        if (typeof directory !== 'string' || typeof filename !== 'string' || typeof content !== 'string') {
            throw new Error('Tous les paramètres doivent être des chaînes de caractères');
        }

        // Créer le répertoire s'il n'existe pas
        if (!fs.existsSync(directory)) {
            fs.mkdirSync(directory, { recursive: true, mode: 0o700 }); // Mode 0o700: rwx------
        } else {
            // S'assurer que le répertoire existant a les bonnes permissions
            fs.chmodSync(directory, 0o700);
        }

        // Construire le chemin complet du fichier
        const filePath = path.join(directory, filename);

        // Écrire le contenu dans le fichier avec permissions restreintes
        fs.writeFileSync(filePath, content, {
            encoding: 'utf8',
            mode: 0o600 // Mode 0o600: rw-------
        });

        console.log(`Fichier secret "${filename}" enregistré avec succès dans "${directory}"`);
        
    } catch (error) {
        console.error(`Erreur lors de l'enregistrement du fichier secret: ${error.message}`);
        throw error; // Propager l'erreur pour que l'appelant puisse la gérer
    }
}