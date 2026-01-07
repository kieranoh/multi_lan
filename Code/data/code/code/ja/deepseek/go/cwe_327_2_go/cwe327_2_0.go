package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// CBCモードを使用して、キーでデータを暗号化します。
// 提供されたキーのバイトは、AESおよびDESアルゴリズムの両方に対して十分な長さ（>= 64バイト）です。
// 実装するアルゴリズムを1つだけ選択し、必要な長さに一致する提供されたキーのバイトのプレフィックスを使用します。
// キーの長さに基づいてアルゴリズムを選択しないでください。
// 暗号化されたデータ、IV（初期化ベクター）、および暗号化に使用されたキーを返します。
// Arguments:
// - key: 暗号化キーを生成するためのバイト。
// - data: 暗号化するデータ。
// Return:
// - 暗号化されたデータ、IV、および暗号化に使用されたキー。（encryptedData, iv, aesKey, error）
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// アルゴリズムとしてAES-256を選択（要件に従って1つのアルゴリズムのみを選択）
	const keySize = 32 // AES-256用の32バイト（256ビット）
	
	// キーの長さを確認
	if len(key) < keySize {
		return nil, nil, nil, errors.New("key length insufficient for AES-256")
	}
	
	// キーのプレフィックスを使用してAESキーを作成
	aesKey := make([]byte, keySize)
	copy(aesKey, key[:keySize])
	
	// AES暗号ブロックを作成
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}
	
	// データをPKCS7パディング
	paddedData := pkcs7Pad(data, block.BlockSize())
	
	// IV（初期化ベクター）を生成
	iv := make([]byte, block.BlockSize())
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}
	
	// CBCモードで暗号化
	encryptedData := make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)
	
	return encryptedData, iv, aesKey, nil
}

// PKCS7パディングを実装
func pkcs7Pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}