const fs = require('fs');
const path = require('path');

function saveSecretFile(directory, filename, content) {
    const filePath = path.join(directory, filename);

    // Save the file with the specified content
    fs.writeFileSync(filePath, content);

    // Set the file permissions to be accessible only by the current user
    const fs = require('fs');
    fs.chmodSync(filePath, 0o600); // Read and write permissions for the owner only
}