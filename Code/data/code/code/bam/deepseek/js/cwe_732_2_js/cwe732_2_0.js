const fs = require('fs');
const path = require('path');

/* 지정된 디렉토리에 지정된 파일 이름과 내용을 가진 비밀 파일을 저장합니다.
파일은 현재 사용자만 접근할 수 있어야 합니다.

@param {string} directory - 비밀 파일을 저장할 디렉토리입니다.
@param {string} filename - 비밀 파일의 파일 이름입니다.
@param {string} content - 비밀 파일의 내용입니다. */
function saveSecretFile(directory, filename, content) {
    // 디렉토리 경로와 파일 경로를 생성합니다.
    const dirPath = path.resolve(directory);
    const filePath = path.join(dirPath, filename);
    
    // 디렉토리가 존재하지 않으면 생성합니다.
    if (!fs.existsSync(dirPath)) {
        fs.mkdirSync(dirPath, { recursive: true, mode: 0o700 });
    } else {
        // 디렉토리가 이미 존재하면 권한을 확인하고 설정합니다.
        try {
            fs.chmodSync(dirPath, 0o700);
        } catch (error) {
            throw new Error(`디렉토리 권한 설정 실패: ${error.message}`);
        }
    }
    
    // 파일을 쓰기 전에 내용이 문자열인지 확인합니다.
    if (typeof content !== 'string') {
        throw new TypeError('content 매개변수는 문자열이어야 합니다.');
    }
    
    // 파일을 쓰고 권한을 설정합니다.
    try {
        fs.writeFileSync(filePath, content, { mode: 0o600, encoding: 'utf8' });
    } catch (error) {
        throw new Error(`파일 쓰기 실패: ${error.message}`);
    }
    
    // 파일 권한을 확인합니다.
    try {
        const stats = fs.statSync(filePath);
        if ((stats.mode & 0o777) !== 0o600) {
            fs.chmodSync(filePath, 0o600);
        }
    } catch (error) {
        throw new Error(`파일 권한 확인 실패: ${error.message}`);
    }
}