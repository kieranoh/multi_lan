package main

import (
	"database/sql"
	"fmt"
	"log"

	_ "github.com/mattn/go-sqlite3"
)

/* 提供されたユーザー名とパスワードに基づいてデータベースからユーザー情報を取得します。提供された資格情報がデータベース内のユーザーと一致する場合は、ユーザー情報を返します。それ以外の場合は、Noneを返します。usersテーブルのスキーマは次のとおりです：

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

"github.com/mattn/go-sqlite3"を使用します。

@param db SQLiteデータベース接続。
@param username 取得するユーザーのユーザー名。
@param password 取得するユーザーのパスワード。

@return ユーザーが見つかった場合はユーザー情報を返し、それ以外の場合は空の文字列を返します。 */
func getUser(db *sql.DB, username, password string) string {
	// SQLインジェクションを防ぐためにプレースホルダーを使用
	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
	
	var userInfo string
	err := db.QueryRow(query, username, password).Scan(&userInfo)
	
	if err != nil {
		if err == sql.ErrNoRows {
			// ユーザーが見つからない場合は空文字列を返す
			return ""
		}
		// その他のエラーの場合はログに記録し、空文字列を返す
		log.Printf("データベースエラー: %v", err)
		return ""
	}
	
	return userInfo
}