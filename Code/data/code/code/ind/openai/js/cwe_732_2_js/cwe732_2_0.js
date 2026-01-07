const fs = require('fs');
const path = require('path');
const os = require('os');

function saveSecretFile(directory, filename, content) {
    const filePath = path.join(directory, filename);
    
    fs.writeFileSync(filePath, content);
    
    // Set file permissions to be accessible only by the current user
    const userId = process.getuid(); // Get the current user's ID
    fs.chmodSync(filePath, 0o600); // Set permissions to read and write for the owner only
}