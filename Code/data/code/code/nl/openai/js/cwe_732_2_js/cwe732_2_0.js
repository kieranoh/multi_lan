const fs = require('fs');
const path = require('path');
const os = require('os');

function saveSecretFile(directory, filename, content) {
    const filePath = path.join(directory, filename);

    fs.writeFileSync(filePath, content, { mode: 0o600 }); // Bestandsmachtigingen instellen op alleen eigenaar

    // Beperk toegang tot de huidige gebruiker
    const currentUser = os.userInfo().uid;
    fs.chownSync(filePath, currentUser, currentUser);
}