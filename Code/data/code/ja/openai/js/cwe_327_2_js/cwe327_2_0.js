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
    // AESを選択し、キーを32バイトに切り詰める
    const aesKey = key.slice(0, 32);
    const iv = crypto.randomBytes(16); // IVを生成
    const cipher = crypto.createCipheriv('aes-256-cbc', aesKey, iv); // AES-256-CBCで暗号化

    let encryptedData = cipher.update(data, 'utf8', 'hex');
    encryptedData += cipher.final('hex');

    return {
        encryptedData: encryptedData,
        iv: iv.toString('hex'),
        aesKey: aesKey.toString('hex')
    };
}