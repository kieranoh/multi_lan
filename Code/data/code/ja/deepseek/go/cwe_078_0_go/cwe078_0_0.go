package main

import (
	"bytes"
	"os"
	"os/exec"
	"path/filepath"
)

/* `ls -l` コマンドがユーザー提供のディレクトリパスで実行されたときの出力（stdout のみ）を返します。コマンド実行中にエラーが発生した場合（例：ディレクトリが見つからない、権限エラー）、空の文字列を返します。

@param dir_path `ls -l` コマンドを実行するためのユーザー提供のディレクトリパス。

@return `ls -l` コマンドの出力、またはエラーが発生した場合は空の文字列。 */
func getLsResult(dirPath string) string {
	// ディレクトリパスをクリーンアップして絶対パスに変換
	cleanPath := filepath.Clean(dirPath)
	absPath, err := filepath.Abs(cleanPath)
	if err != nil {
		return ""
	}

	// パスがディレクトリとして存在するか確認
	fileInfo, err := os.Stat(absPath)
	if err != nil {
		return ""
	}
	if !fileInfo.IsDir() {
		return ""
	}

	// ls -l コマンドを実行
	cmd := exec.Command("ls", "-l", absPath)
	var stdout, stderr bytes.Buffer
	cmd.Stdout = &stdout
	cmd.Stderr = &stderr

	// コマンド実行
	if err := cmd.Run(); err != nil {
		return ""
	}

	// stderrに出力がある場合はエラーとみなす
	if stderr.Len() > 0 {
		return ""
	}

	// 出力を文字列として返す（末尾の改行は保持）
	return stdout.String()
}