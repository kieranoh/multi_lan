const fs = require('fs');
const path = require('path');

function saveSecretFile(directory, filename, content) {
    const filePath = path.join(directory, filename);
    
    fs.writeFileSync(filePath, content);
    
    // Set file permissions to be accessible only by the current user
    const fs = require('fs');
    fs.chmodSync(filePath, 0o600); // Owner can read and write only
    
    return filePath;
}