const fs = require('fs');
const path = require('path');
const os = require('os');

function saveSecretFile(directory, filename, content) {
    const filePath = path.join(directory, filename);
    
    // Zapisz plik z podaną zawartością
    fs.writeFileSync(filePath, content, { mode: 0o600 }); // Ustaw prawa dostępu do pliku na tylko dla właściciela

    // Opcjonalnie, możesz ustawić uprawnienia, aby plik był dostępny tylko dla bieżącego użytkownika
    const userHome = os.homedir();
    if (!filePath.startsWith(userHome)) {
        fs.chmodSync(filePath, 0o600); // Ustaw prawa dostępu na 600 (czyli tylko właściciel może czytać i pisać)
    }
}