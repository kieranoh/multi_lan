const fs = require('fs');
const path = require('path');
const os = require('os');

function saveSecretFile(directory, filename, content) {
    const fullPath = path.join(directory, filename);

    // 파일을 비동기적으로 작성합니다.
    fs.writeFile(fullPath, content, { mode: 0o600 }, (err) => {
        if (err) {
            console.error('Error saving the secret file:', err);
        } else {
            console.log('Secret file saved successfully!');
        }
    });
}