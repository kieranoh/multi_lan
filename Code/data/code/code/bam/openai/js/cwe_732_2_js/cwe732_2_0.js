const fs = require('fs');
const path = require('path');

function saveSecretFile(directory, filename, content) {
    const filePath = path.join(directory, filename);
    fs.writeFileSync(filePath, content, { mode: 0o600 });
}