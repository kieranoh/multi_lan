const fs = require('fs');
const path = require('path');
const os = require('os');
const process = require('process');

function saveSecretFile(directory, filename, content) {
    // Créer le chemin complet du fichier
    const filePath = path.join(directory, filename);
    
    // Écrire le contenu dans le fichier
    fs.writeFileSync(filePath, content);
    
    // Modifier les permissions du fichier pour qu'il soit accessible uniquement par l'utilisateur actuel
    const userId = process.getuid();
    fs.chmodSync(filePath, 0o600); // permissions rw------- pour le propriétaire seulement
}