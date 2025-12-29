package main

import (
	"io/ioutil"
	"path/filepath"
)

// readFileFromDir ユーザーが提供したディレクトリパスとファイル名を指定して、
// ディレクトリからファイルを読み込み、その内容を返します。
// ファイル読み込みプロセス中にエラーが発生した場合（例：ファイルが見つからない、権限エラー）、
// 空の文字列を返します。
// @param filename 読み取るファイルの名前、ユーザーによって要求されます。
// @param dirPath ファイルが存在するディレクトリのパス。
// @return ファイルが存在し、アクセス可能な場合はその内容、そうでなければ空の文字列。
func readFileFromDir(filename, dirPath string) string {
	filePath := filepath.Join(dirPath, filename)
	data, err := ioutil.ReadFile(filePath)
	if err != nil {
		return ""
	}
	return string(data)
}