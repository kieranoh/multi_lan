const fs = require('fs');
const path = require('path');

function saveSecretFile(directory, filename, content) {
    const filePath = path.join(directory, filename);
    
    // 파일 내용을 비동기적으로 작성
    fs.writeFile(filePath, content, { mode: 0o600 }, (err) => {
        if (err) {
            console.error('Error writing file:', err);
            return;
        }
        console.log('Secret file saved successfully.');
    });
}