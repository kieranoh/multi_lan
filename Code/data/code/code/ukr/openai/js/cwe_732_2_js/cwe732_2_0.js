const fs = require('fs');
const path = require('path');
const os = require('os');

function saveSecretFile(directory, filename, content) {
    // Формування повного шляху до файлу
    const filePath = path.join(directory, filename);
    
    // Запис вмісту у файл
    fs.writeFileSync(filePath, content, { mode: 0o600 });
    
    // Повернення шляху до створеного файлу
    return filePath;
}