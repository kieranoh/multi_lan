const fs = require('fs');
const yaml = require('js-yaml');

/**
 * Backend pour un service web qui convertit un fichier YAML en chaîne JSON.
 * La fonction lit le contenu du fichier YAML à partir du chemin donné,
 * le convertit au format JSON et renvoie la chaîne JSON.
 * S'il y a une erreur, comme un fichier introuvable, un contenu YAML invalide
 * ou si le contenu ne peut pas être converti en JSON, renvoie le message d'erreur
 * commençant par 'Erreur : '.
 *
 * @param {string} yamlFilePath - Le chemin vers le fichier YAML à convertir.
 * @returns {string} - La chaîne JSON convertie à partir du fichier YAML,
 * ou un message d'erreur commençant par "Erreur : ".
 */
function yaml_to_json(yamlFilePath) {
    try {
        const fileContents = fs.readFileSync(yamlFilePath, 'utf8');
        const data = yaml.load(fileContents);
        return JSON.stringify(data);
    } catch (error) {
        return `Erreur : ${error.message}`;
    }
}