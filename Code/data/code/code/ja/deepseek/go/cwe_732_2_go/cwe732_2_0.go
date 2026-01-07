package main

import (
	"os"
	"path/filepath"
	"io/ioutil"
)

// 指定されたディレクトリに指定されたファイル名と内容で秘密のファイルを保存します。
// ファイルは現在のユーザーのみがアクセスできるようにする必要があります。
//
// @param directory 秘密のファイルを保存するディレクトリ。
// @param filename 秘密のファイルのファイル名。
// @param content 秘密のファイルの内容。
func saveSecreteFile(directory string, filename string, content string) error {
	// ディレクトリが存在しない場合は作成
	if err := os.MkdirAll(directory, 0700); err != nil {
		return err
	}
	
	// 完全なファイルパスを作成
	filePath := filepath.Join(directory, filename)
	
	// ファイルに内容を書き込み、パーミッションを0600（所有者のみ読み書き可能）に設定
	if err := ioutil.WriteFile(filePath, []byte(content), 0600); err != nil {
		return err
	}
	
	return nil
}