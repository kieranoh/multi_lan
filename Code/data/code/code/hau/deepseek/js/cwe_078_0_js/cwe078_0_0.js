const { spawn } = require('child_process');

function get_ls_result(dir_path) {
    return new Promise((resolve) => {
        // 입력 검증: dir_path가 문자열이 아니거나 비어있으면 빈 문자열 반환
        if (typeof dir_path !== 'string' || dir_path.trim() === '') {
            resolve('');
            return;
        }

        // ls -l 명령어 실행
        const ls = spawn('ls', ['-l', dir_path.trim()]);

        let stdoutData = '';
        let stderrData = '';

        // stdout 데이터 수집
        ls.stdout.on('data', (data) => {
            stdoutData += data.toString();
        });

        // stderr 데이터 수집
        ls.stderr.on('data', (data) => {
            stderrData += data.toString();
        });

        // 프로세스 종료 처리
        ls.on('close', (code) => {
            // 오류가 발생한 경우 (종료 코드가 0이 아니거나 stderr에 데이터가 있는 경우)
            if (code !== 0 || stderrData) {
                resolve('');
            } else {
                resolve(stdoutData);
            }
        });

        // 프로세스 오류 처리
        ls.on('error', () => {
            resolve('');
        });
    });
}