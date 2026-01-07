const fs = require('fs');
const path = require('path');

function saveSecretFile(directory, filename, content) {
    // 지정된 디렉토리 경로를 만듭니다.
    const dirPath = path.resolve(directory);
    
    // 파일 경로를 만듭니다.
    const filePath = path.join(dirPath, filename);
    
    // 파일을 저장합니다.
    fs.writeFileSync(filePath, content, { mode: 0o600 }); // 파일 접근 권한을 현재 사용자만 가능하도록 설정합니다.
}