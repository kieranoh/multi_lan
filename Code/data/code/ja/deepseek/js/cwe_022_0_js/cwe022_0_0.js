const fs = require('fs');
const path = require('path');

/**
 * 指定されたディレクトリからファイルの内容を読み取ります。ファイル読み取りプロセス中にエラーが発生した場合（例：ファイルが見つからない、権限エラー）、空の文字列を返します。
 *
 * @param {string} filename - ユーザーが要求した読み取るファイルの名前。
 * @param {string} dir_path - ファイルが存在するディレクトリのパス。
 * @returns {string} ファイルの内容、またはエラーが発生した場合は空の文字列。
 */
function read_file_from_dir(filename, dir_path) {
    try {
        // ファイルパスを構築
        const filePath = path.join(dir_path, filename);
        
        // ファイルを同期的に読み取り（エラーが発生した場合はcatchブロックで処理）
        const content = fs.readFileSync(filePath, 'utf8');
        
        return content;
    } catch (error) {
        // すべてのエラー（ファイルが見つからない、権限エラー、その他のIOエラー）に対して空の文字列を返す
        return '';
    }
}