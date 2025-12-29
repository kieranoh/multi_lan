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
    // キーの長さを検証
    if (!Buffer.isBuffer(key) || key.length < 16) {
        throw new Error('キーは少なくとも16バイトのBufferである必要があります');
    }
    
    if (!Buffer.isBuffer(data)) {
        throw new Error('データはBufferである必要があります');
    }
    
    // AES-256-CBCを使用するため、32バイトのキーが必要
    const keyLength = 32;
    
    // 提供されたキーから必要な長さのプレフィックスを使用
    const keyUsed = key.slice(0, keyLength);
    
    // 16バイトのランダムなIVを生成
    const iv = crypto.randomBytes(16);
    
    // AES-256-CBC暗号化器を作成
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);
    
    // データを暗号化
    const encryptedChunks = [];
    encryptedChunks.push(cipher.update(data));
    encryptedChunks.push(cipher.final());
    
    // 暗号化されたデータを結合
    const encryptedData = Buffer.concat(encryptedChunks);
    
    return {
        encryptedData,
        iv,
        keyUsed
    };
}