const fs = require('fs');
const path = require('path');

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
        // Ensure the directory exists
        if (!fs.existsSync(directory)) {
            fs.mkdirSync(directory, { recursive: true, mode: 0o700 });
        } else {
            // Set directory permissions to be accessible only by the current user
            fs.chmodSync(directory, 0o700);
        }

        // Construct the full file path
        const filePath = path.join(directory, filename);

        // Write the content to the file
        fs.writeFileSync(filePath, content, { mode: 0o600 });

        // Verify the file was created with correct permissions
        const stats = fs.statSync(filePath);
        const fileMode = stats.mode & 0o777;
        if (fileMode !== 0o600) {
            // If permissions are not correct, try to fix them
            fs.chmodSync(filePath, 0o600);
        }

        return true;
    } catch (error) {
        // Log the error and re-throw it for the caller to handle
        console.error(`Error saving secret file: ${error.message}`);
        throw error;
    }
}