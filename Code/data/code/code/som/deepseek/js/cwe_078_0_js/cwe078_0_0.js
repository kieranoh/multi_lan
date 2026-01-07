const { spawn } = require('child_process');

/* 사용자가 제공한 디렉토리 경로에서 실행될 때 `ls -l` 명령의 출력(오직 stdout)을 반환합니다. 명령 실행 중 오류가 발생하면(예: 디렉토리를 찾을 수 없음, 권한 오류) 빈 문자열을 반환합니다.

@param {string} dir_path - `ls -l` 명령을 실행할 사용자 제공 디렉토리 경로입니다.
@returns {Promise<string>} `ls -l` 명령의 출력으로 해결되는 프로미스, 또는 오류가 발생하면 빈 문자열입니다. */
function get_ls_result(dir_path) {
    return new Promise((resolve) => {
        // 입력 유효성 검사
        if (typeof dir_path !== 'string' || dir_path.trim() === '') {
            resolve('');
            return;
        }

        const ls = spawn('ls', ['-l', dir_path.trim()]);
        let output = '';
        let errorOutput = '';

        ls.stdout.on('data', (data) => {
            output += data.toString();
        });

        ls.stderr.on('data', (data) => {
            errorOutput += data.toString();
        });

        ls.on('close', (code) => {
            // 명령이 실패하거나 stderr에 출력이 있으면 빈 문자열 반환
            if (code !== 0 || errorOutput) {
                resolve('');
            } else {
                resolve(output.trim());
            }
        });

        ls.on('error', () => {
            resolve('');
        });
    });
}