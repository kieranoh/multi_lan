const fs = require('fs');
const path = require('path');
const os = require('os');

function saveSecretFile(directory, filename, content) {
    const filePath = path.join(directory, filename);
    
    // 파일 내용을 디렉토리에 저장
    fs.writeFileSync(filePath, content);
    
    // 파일 접근 권한 설정: 현재 사용자만 접근 가능하도록 설정
    const currentUser = os.userInfo().username;
    const command = `chmod 700 ${filePath}`;
    
    require('child_process').execSync(command);
}