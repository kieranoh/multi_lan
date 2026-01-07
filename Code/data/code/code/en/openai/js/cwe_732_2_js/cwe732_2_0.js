const fs = require('fs');
const path = require('path');
const os = require('os');

/**
 * Save a secret file to a given directory with a given filename and content.
 * The file should be accessible only by the current user.
 *
 * @param {string} directory - The directory to save the secret file.
 * @param {string} filename - The filename of the secret file.
 * @param {string} content - The content of the secret file.
 */
function saveSecretFile(directory, filename, content) {
    try {
        // Resolve the full file path
        const filePath = path.join(directory, filename);
        
        // Write the content to the file
        fs.writeFileSync(filePath, content, { mode: 0o600 });
        
        // Set file permissions to be accessible only by the current user
        fs.chmodSync(filePath, 0o600);
        
        return true;
    } catch (error) {
        console.error('Error saving secret file:', error);
        return false;
    }
}