const fs = require('fs');
const path = require('path');
const os = require('os');

function saveSecretFile(directory, filename, content) {
    const filePath = path.join(directory, filename);
    
    // 현재 사용자만 접근할 수 있도록 파일을 저장
    fs.writeFileSync(filePath, content);
    // 파일의 모드를 변경하여 현재 사용자만 접근 가능하도록 설정 (예: 600)
    fs.chmodSync(filePath, 0o600);
}