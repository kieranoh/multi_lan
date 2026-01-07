const { exec } = require('child_process');

/**
 * ユーザー提供のディレクトリパスで実行された `ls -l` コマンドの出力（stdout のみ）を返します。コマンド実行中にエラーが発生した場合（例：ディレクトリが見つからない、権限エラー）、空の文字列を返します。
 *
 * @param {string} dir_path - `ls -l` コマンドを実行するためのユーザー提供のディレクトリパス。
 * @returns {Promise<string>} `ls -l` コマンドの出力で解決されるプロミス、またはエラーが発生した場合は空の文字列。
 */
function get_ls_result(dir_path) {
    return new Promise((resolve) => {
        exec(`ls -l ${dir_path}`, (error, stdout) => {
            if (error) {
                resolve('');
            } else {
                resolve(stdout);
            }
        });
    });
}