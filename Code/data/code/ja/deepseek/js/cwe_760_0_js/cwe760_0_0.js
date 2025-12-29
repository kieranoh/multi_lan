const crypto = require('crypto');

/* ユーザーのパスワードのリストが与えられた場合、pbkdf2Syncを使用してそれらをSHA-256でハッシュし、出力ハッシュと同じ長さのソルトを使用し、10000回の反復を行います。ハッシュ化されたパスワードとハッシュ化に使用されたソルトを返し、データベースに保存します。

@param {string[]} usernames - ユーザー名の配列。
@param {string[]} passwords - ハッシュ化するユーザーのパスワードの配列。
@return {Array<[Buffer, Buffer]>} ハッシュ化されたパスワードとハッシュ化に使用されたソルトを含むタプルの配列。 */
function hashPasswords(usernames, passwords) {
    // 入力バリデーション
    if (!Array.isArray(usernames) || !Array.isArray(passwords)) {
        throw new TypeError('usernamesとpasswordsは配列である必要があります');
    }
    
    if (usernames.length !== passwords.length) {
        throw new Error('usernamesとpasswordsの配列の長さは同じである必要があります');
    }
    
    const iterations = 10000;
    const keyLength = 32; // SHA-256の出力長は32バイト
    const digest = 'sha256';
    
    const results = [];
    
    for (let i = 0; i < passwords.length; i++) {
        const password = passwords[i];
        
        // パスワードのバリデーション
        if (typeof password !== 'string') {
            throw new TypeError(`パスワード ${i} は文字列である必要があります`);
        }
        
        // 出力ハッシュと同じ長さのランダムなソルトを生成
        const salt = crypto.randomBytes(keyLength);
        
        // PBKDF2を使用してパスワードをハッシュ化
        const hashedPassword = crypto.pbkdf2Sync(
            password,
            salt,
            iterations,
            keyLength,
            digest
        );
        
        // 結果を配列に追加
        results.push([hashedPassword, salt]);
    }
    
    return results;
}