package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"io"
)

/* AESおよびCBCモードを使用してデータをキーで暗号化します。
提供されたキーのバイトは十分な長さです（>= 64バイト）。必要な長さに一致する提供されたキーのバイトのプレフィックスを使用します。
暗号化されたデータ、IV（初期化ベクター）、および暗号化に使用されたキーを返します。

Arguments:
- key: 暗号化キーを生成するためのバイト（少なくとも16バイト）。
- data: 暗号化するデータ。

Returns:
- (encryptedData, iv, aesKey): 暗号化されたデータ、IV、および暗号化に使用されたキー。 */
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// AES-256を使用するため、32バイトのキーを生成
	const keyLength = 32
	if len(key) < keyLength {
		// キーが十分な長さでない場合はパニック
		panic("key must be at least 32 bytes long")
	}
	
	// キーの最初の32バイトをAESキーとして使用
	aesKey = key[:keyLength]
	
	// AES暗号ブロックを作成
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		panic(err)
	}
	
	// データをPKCS#7パディング
	paddedData := pkcs7Pad(data, block.BlockSize())
	
	// IVを生成
	iv = make([]byte, block.BlockSize())
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		panic(err)
	}
	
	// CBCモードで暗号化
	encryptedData = make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)
	
	return encryptedData, iv, aesKey
}

// PKCS#7パディングを実装
func pkcs7Pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}