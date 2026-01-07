const fs = require('fs');
const path = require('path');
const os = require('os');

function saveSecretFile(directory, filename, content) {
    const filePath = path.join(directory, filename);

    // Guardar el contenido en el archivo
    fs.writeFileSync(filePath, content, { mode: 0o600 });

    // Asegurarse de que el archivo solo sea accesible por el usuario actual
    const currentUser = os.userInfo().uid;
    fs.chownSync(filePath, currentUser, currentUser);
}