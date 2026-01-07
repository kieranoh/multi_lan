const fs = require('fs');
const path = require('path');

/* 지정된 디렉토리에 지정된 파일 이름과 내용을 가진 비밀 파일을 저장합니다.
파일은 현재 사용자만 접근할 수 있어야 합니다.

@param {string} directory - 비밀 파일을 저장할 디렉토리.
@param {string} filename - 비밀 파일의 파일 이름.
@param {string} content - 비밀 파일의 내용. */
function saveSecretFile(directory, filename, content) {
    // 디렉토리 경로와 파일 경로 생성
    const dirPath = path.resolve(directory);
    const filePath = path.join(dirPath, filename);
    
    // 디렉토리가 존재하지 않으면 생성 (재귀적으로)
    if (!fs.existsSync(dirPath)) {
        fs.mkdirSync(dirPath, { recursive: true, mode: 0o700 });
    } else {
        // 디렉토리가 이미 존재하면 권한을 700으로 설정
        fs.chmodSync(dirPath, 0o700);
    }
    
    // 파일에 내용 쓰기 (권한 600으로 설정)
    fs.writeFileSync(filePath, content, { mode: 0o600, encoding: 'utf8' });
    
    // 파일이 성공적으로 생성되었는지 확인
    if (fs.existsSync(filePath)) {
        // 파일 권한이 올바르게 설정되었는지 확인하고 필요시 수정
        const stats = fs.statSync(filePath);
        if ((stats.mode & 0o777) !== 0o600) {
            fs.chmodSync(filePath, 0o600);
        }
    }
}