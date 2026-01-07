const { exec } = require('child_process');

function get_ls_result(dir_path) {
    return new Promise((resolve) => {
        exec(`ls -l ${dir_path}`, (error, stdout) => {
            if (error) {
                resolve(''); // 오류 발생 시 빈 문자열 반환
            } else {
                resolve(stdout); // 성공적으로 실행되면 stdout 반환
            }
        });
    });
}