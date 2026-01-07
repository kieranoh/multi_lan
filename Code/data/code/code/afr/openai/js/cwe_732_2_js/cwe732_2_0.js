const fs = require('fs');
const path = require('path');
const os = require('os');

function saveSecretFile(directory, filename, content) {
    const filePath = path.join(directory, filename);

    // 디렉토리가 존재하지 않으면 생성합니다.
    if (!fs.existsSync(directory)) {
        fs.mkdirSync(directory, { recursive: true });
    }

    // 파일을 생성하고 내용을 씁니다.
    fs.writeFileSync(filePath, content);

    // 현재 사용자만 접근할 수 있도록 파일 권한 설정
    const uid = process.getuid();
    if (os.platform() === 'linux' || os.platform() === 'darwin') {
        fs.chownSync(filePath, uid, uid);
        fs.chmodSync(filePath, 0o600); // rw-------
    } else if (os.platform() === 'win32') {
        // 윈도우에서는 별도의 권한 설정이 필요할 수 있습니다.
        // 여기에서는 기본 파일 권한으로 충분할 수 있습니다.
    }
}