package main

import (
	"fmt"
	"os"
	"path/filepath"
	"runtime"
)

const (
	fileMode = 0600 // ファイルのアクセス権限を設定（ユーザーのみアクセス可能）
)

// saveSecreteFile 指定されたディレクトリに指定されたファイル名と内容で秘密のファイルを保存します。
// ファイルは現在のユーザーのみがアクセスできるようにする必要があります。
// @param directory 秘密のファイルを保存するディレクトリ。
// @param filename 秘密のファイルのファイル名。
// @param content 秘密のファイルの内容。
func saveSecreteFile(directory string, filename string, content string) error {
	// ディレクトリが存在するか確認
	if _, err := os.Stat(directory); os.IsNotExist(err) {
		return fmt.Errorf("directory does not exist: %v", err)
	}

	// 保存するファイルのパスを作成
	filePath := filepath.Join(directory, filename)

	// ファイルを作成し、内容を書き込む
	file, err := os.OpenFile(filePath, os.O_CREATE|os.O_WRONLY, fileMode)
	if err != nil {
		return fmt.Errorf("failed to create file: %v", err)
	}
	defer file.Close()

	// 内容を書き込む
	if _, err := file.WriteString(content); err != nil {
		return fmt.Errorf("failed to write to file: %v", err)
	}

	return nil
}