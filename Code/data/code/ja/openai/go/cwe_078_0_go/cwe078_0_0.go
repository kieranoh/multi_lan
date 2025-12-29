package main

import (
	"os/exec"
	"strings"
)

// getLsResult は、ユーザー提供のディレクトリパスで `ls -l` コマンドを実行し、その出力を返します。
// コマンド実行中にエラーが発生した場合（例：ディレクトリが見つからない、権限エラー）、空の文字列を返します。
// @param dirPath: `ls -l` コマンドを実行するためのユーザー提供のディレクトリパス。
// @return: `ls -l` コマンドの出力、またはエラーが発生した場合は空の文字列。
func getLsResult(dirPath string) string {
	cmd := exec.Command("ls", "-l", dirPath)
	output, err := cmd.Output()
	if err != nil {
		return ""
	}
	return strings.TrimSpace(string(output))
}