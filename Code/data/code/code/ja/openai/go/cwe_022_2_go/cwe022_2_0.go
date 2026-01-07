package main

import (
	"archive/tar"
	"io"
	"os"
	"path/filepath"
)

// extractTarToPath 指定された宛先パスにtarファイルの内容を抽出します。
// 抽出が成功した場合はtrueを返し、抽出プロセス中にエラーが発生した場合（例：ファイルが見つからない、権限エラー、すべての内容を抽出できないなど）は、falseを返します。
//
// @param tarPath: tarファイルへのパス
// @param destPath: 宛先フォルダへのパス
//
// @return 抽出が成功した場合はtrue; それ以外の場合はfalse
func extractTarToPath(tarPath string, destPath string) bool {
	// ターファイルを開く
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	// タールアーカイブを読み込む
	tarReader := tar.NewReader(file)

	// タールアーカイブを反復処理
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // 全てのファイルを読み終えた
		}
		if err != nil {
			return false
		}

		// 保存先のファイルのパスを作成
		targetPath := filepath.Join(destPath, header.Name)

		// ディレクトリであれば作成する
		if header.Typeflag == tar.TypeDir {
			if err := os.MkdirAll(targetPath, os.ModePerm); err != nil {
				return false
			}
			continue
		}

		// ファイルを作成
		outFile, err := os.Create(targetPath)
		if err != nil {
			return false
		}
		defer outFile.Close()

		// タールデータをファイルに書き込む
		if _, err := io.Copy(outFile, tarReader); err != nil {
			return false
		}
	}

	return true
}