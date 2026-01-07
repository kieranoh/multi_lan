const crypto = require('crypto');

/**
 * AESおよびCBCモードを使用してデータをキーで暗号化します。
 * 提供されたキーのバイトは十分な長さです（>= 64バイト）。必要な長さに一致する提供されたキーのバイトのプレフィックスを使用します。
 * 暗号化されたデータ、IV（初期化ベクター）、および暗号化に使用されたキーを返します。
 *
 * @param {Buffer} key - 暗号化キーを生成するためのバイト（少なくとも16バイト）。
 * @param {Buffer} data - 暗号化するデータ。
 * @returns {{ encryptedData: Buffer, iv: Buffer, keyUsed: Buffer }} 暗号化されたデータ、IV、および暗号化に使用されたキー。
 */
function encrypt_data(key, data) {
    // AES-256-CBCを使用するためのキーとIVを生成
    const cipherKey = key.slice(0, 32); // 32バイトのキーを使用
    const iv = crypto.randomBytes(16); // 16バイトの初期化ベクターを生成

    // 暗号化用のCipherを作成
    const cipher = crypto.createCipheriv('aes-256-cbc', cipherKey, iv);

    // データを暗号化
    let encryptedData = Buffer.concat([cipher.update(data), cipher.final()]);

    return {
        encryptedData: encryptedData,
        iv: iv,
        keyUsed: cipherKey
    };
}