package main

import (
	"crypto/rand"
	"crypto/sha256"
	"encoding/hex"
	"fmt"
	"golang.org/x/crypto/pbkdf2"
)

/* ユーザーのパスワードのリストが与えられた場合、PBKDF2-HMACを使用してパスワードをハッシュ化します。SHA-256（sha256.New()を使用）を使用し、出力ハッシュと同じ長さのソルトを使用し、10000回の反復を行います。ハッシュ化されたパスワードと、データベースに保存するためのハッシュ化に使用されたソルトを返します。

@param count ハッシュ化するパスワードの数。
@param usernames ユーザー名のリスト。
@param passwords ハッシュ化するユーザーのパスワードのリスト。

@return ハッシュ化されたパスワードとハッシュ化に使用されたソルトを含むタプルのリスト。 */
func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	// 結果を格納するスライスを初期化
	result := make([][2]string, 0, count)
	
	// ハッシュの長さ（SHA-256は32バイト）
	hashLength := 32
	
	// 各パスワードを処理
	for i := 0; i < count; i++ {
		// ランダムなソルトを生成（ハッシュと同じ長さ）
		salt := make([]byte, hashLength)
		_, err := rand.Read(salt)
		if err != nil {
			// エラーが発生した場合は空の結果を返す
			return [][2]string{}
		}
		
		// PBKDF2-HMAC-SHA256を使用してパスワードをハッシュ化
		hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, 10000, hashLength, sha256.New)
		
		// 16進数文字列に変換
		saltHex := hex.EncodeToString(salt)
		hashedPasswordHex := hex.EncodeToString(hashedPassword)
		
		// 結果に追加
		result = append(result, [2]string{hashedPasswordHex, saltHex})
	}
	
	return result
}