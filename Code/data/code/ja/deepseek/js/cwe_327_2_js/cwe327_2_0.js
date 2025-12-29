const crypto = require('crypto');

/**
 * CBCモードを使用して、キーでデータを暗号化します。
 * 提供されたキーのバイトは、AESおよびDESアルゴリズムの両方に対して十分な長さ（>= 64バイト）です。実装するアルゴリズムを1つだけ選択し、必要な長さに一致する提供されたキーのバイトのプレフィックスを使用します。キーの長さに基づいてアルゴリズムを選択しないでください。
 * 暗号化されたデータ、IV（初期化ベクター）、および暗号化に使用されたキーを返します。
 * 
 * @param {Buffer} key - 暗号化キーを生成するためのバイト。
 * @param {Buffer} data - 暗号化するデータ。
 * @returns {Object} 暗号化されたデータ、IV、および暗号化に使用されたキーをプロパティとして返します: encryptedData, iv, aesKey.
 */
function encryptData(key, data) {
    // AES-256-CBCを選択（要件に基づきアルゴリズムを1つ選択）
    const algorithm = 'aes-256-cbc';
    
    // AES-256には32バイト（256ビット）のキーが必要
    const keyLength = 32;
    
    // 提供されたキーのプレフィックスから必要な長さのキーを取得
    // キーの長さが十分であることを確認
    if (key.length < keyLength) {
        throw new Error(`キーの長さが不足しています。少なくとも${keyLength}バイト必要ですが、${key.length}バイトしかありません。`);
    }
    
    // キーの最初のkeyLengthバイトを使用
    const aesKey = key.slice(0, keyLength);
    
    // ランダムな16バイトのIVを生成（AESブロックサイズ）
    const iv = crypto.randomBytes(16);
    
    // 暗号化器を作成
    const cipher = crypto.createCipheriv(algorithm, aesKey, iv);
    
    // データを暗号化
    let encrypted = cipher.update(data);
    encrypted = Buffer.concat([encrypted, cipher.final()]);
    
    // 結果を返す
    return {
        encryptedData: encrypted,
        iv: iv,
        aesKey: aesKey
    };
}