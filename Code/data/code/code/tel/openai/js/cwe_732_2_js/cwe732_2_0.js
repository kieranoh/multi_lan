const fs = require('fs');
const path = require('path');

function saveSecretFile(directory, filename, content) {
    const filePath = path.join(directory, filename);
    
    // 파일을 저장
    fs.writeFileSync(filePath, content, { mode: 0o600 });
    
    // 현재 사용자만 접근할 수 있도록 권한 설정
    fs.chmodSync(filePath, 0o600);
}