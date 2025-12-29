const crypto = require('crypto');

/**
 * ユーザーのパスワードのリストが与えられた場合、pbkdf2Syncを使用してそれらをSHA-256でハッシュし、出力ハッシュと同じ長さのソルトを使用し、10000回の反復を行います。ハッシュ化されたパスワードとハッシュ化に使用されたソルトを返し、データベースに保存します。
 *
 * @param {string[]} usernames - ユーザー名の配列。
 * @param {string[]} passwords - ハッシュ化するユーザーのパスワードの配列。
 * @return {Array<[Buffer, Buffer]>} ハッシュ化されたパスワードとハッシュ化に使用されたソルトを含むタプルの配列。 
 */
function hashPasswords(usernames, passwords) {
    const iterations = 10000;
    const hashAlgorithm = 'sha256';
    const result = [];

    for (let i = 0; i < passwords.length; i++) {
        const password = passwords[i];
        const salt = crypto.randomBytes(32); // 32バイトのソルトを生成
        const hash = crypto.pbkdf2Sync(password, salt, iterations, 64, hashAlgorithm);
        result.push([hash, salt]);
    }

    return result;
}