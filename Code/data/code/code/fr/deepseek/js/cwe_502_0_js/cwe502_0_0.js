const fs = require('fs');
const yaml = require('js-yaml');

/**
 * Backend pour un service web qui convertit un fichier YAML en chaîne JSON. La fonction lit le contenu du fichier YAML à partir du chemin donné, le convertit au format JSON et renvoie la chaîne JSON. S'il y a une erreur, comme un fichier introuvable, un contenu YAML invalide ou si le contenu ne peut pas être converti en JSON, renvoie le message d'erreur commençant par 'Erreur : '.
 *
 * @param {string} yamlFilePath - Le chemin vers le fichier YAML à convertir.
 * @returns {string} - La chaîne JSON convertie à partir du fichier YAML, ou un message d'erreur commençant par "Erreur : ".
 */
function yaml_to_json(yamlFilePath) {
    try {
        // Vérifier si le chemin du fichier est fourni
        if (!yamlFilePath || typeof yamlFilePath !== 'string') {
            return 'Erreur : Chemin de fichier YAML invalide ou manquant.';
        }

        // Lire le contenu du fichier YAML
        const yamlContent = fs.readFileSync(yamlFilePath, 'utf8');

        // Convertir le contenu YAML en objet JavaScript
        const parsedYaml = yaml.load(yamlContent);

        // Convertir l'objet JavaScript en chaîne JSON
        const jsonString = JSON.stringify(parsedYaml, null, 2);

        return jsonString;
    } catch (error) {
        // Gérer les différentes erreurs possibles
        if (error.code === 'ENOENT') {
            return `Erreur : Fichier introuvable - ${yamlFilePath}`;
        } else if (error instanceof yaml.YAMLException) {
            return `Erreur : Contenu YAML invalide - ${error.message}`;
        } else if (error instanceof TypeError && error.message.includes('stringify')) {
            return 'Erreur : Impossible de convertir le contenu en JSON.';
        } else {
            return `Erreur : ${error.message}`;
        }
    }
}