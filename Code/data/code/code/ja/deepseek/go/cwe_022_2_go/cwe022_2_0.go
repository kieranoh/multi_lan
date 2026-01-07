package main

import (
	"archive/tar"
	"compress/gzip"
	"fmt"
	"io"
	"os"
	"path/filepath"
)

/* 指定された宛先パスにtarファイルの内容を抽出します。
抽出が成功した場合はtrueを返し、抽出プロセス中にエラーが発生した場合（例：ファイルが見つからない、権限エラー、すべての内容を抽出できないなど）は、falseを返します。

@param tarPath: tarファイルへのパス
@param destPath: 宛先フォルダへのパス

@return 抽出が成功した場合はtrue; それ以外の場合はfalse */
func extractTarToPath(tarPath string, destPath string) bool {
	// 入力パスの検証
	if tarPath == "" || destPath == "" {
		return false
	}

	// tarファイルを開く
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	// tarファイルの読み込みを準備
	// gzip圧縮かどうかを確認
	var tarReader *tar.Reader
	if filepath.Ext(tarPath) == ".gz" || filepath.Ext(tarPath) == ".tgz" {
		gzReader, err := gzip.NewReader(file)
		if err != nil {
			return false
		}
		defer gzReader.Close()
		tarReader = tar.NewReader(gzReader)
	} else {
		tarReader = tar.NewReader(file)
	}

	// 宛先ディレクトリの作成
	if err := os.MkdirAll(destPath, 0755); err != nil {
		return false
	}

	// tarファイルの内容を抽出
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // tarファイルの終了
		}
		if err != nil {
			return false
		}

		// セキュリティ対策: 宛先パスがdestPath内にあることを確認
		targetPath := filepath.Join(destPath, header.Name)
		if !isPathWithinDest(destPath, targetPath) {
			return false
		}

		// ファイルタイプに基づいて処理
		switch header.Typeflag {
		case tar.TypeDir:
			// ディレクトリの作成
			if err := os.MkdirAll(targetPath, os.FileMode(header.Mode)); err != nil {
				return false
			}
		case tar.TypeReg, tar.TypeRegA:
			// 通常ファイルの作成
			if err := extractFile(tarReader, targetPath, header); err != nil {
				return false
			}
		case tar.TypeSymlink:
			// シンボリックリンクの作成
			if err := os.Symlink(header.Linkname, targetPath); err != nil {
				return false
			}
		case tar.TypeLink:
			// ハードリンクの作成
			linkPath := filepath.Join(destPath, header.Linkname)
			if !isPathWithinDest(destPath, linkPath) {
				return false
			}
			if err := os.Link(linkPath, targetPath); err != nil {
				return false
			}
		default:
			// サポートされていないファイルタイプはスキップ
			continue
		}
	}

	return true
}

// ファイルを抽出するヘルパー関数
func extractFile(reader *tar.Reader, targetPath string, header *tar.Header) error {
	// 親ディレクトリの作成
	if err := os.MkdirAll(filepath.Dir(targetPath), 0755); err != nil {
		return err
	}

	// ファイルの作成
	file, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, os.FileMode(header.Mode))
	if err != nil {
		return err
	}
	defer file.Close()

	// ファイル内容の書き込み
	if _, err := io.Copy(file, reader); err != nil {
		// 書き込みエラーが発生した場合、作成したファイルを削除
		os.Remove(targetPath)
		return err
	}

	return nil
}

// パスが宛先ディレクトリ内にあることを確認するヘルパー関数
func isPathWithinDest(destPath, targetPath string) bool {
	rel, err := filepath.Rel(destPath, targetPath)
	if err != nil {
		return false
	}
	// 相対パスが".."で始まる場合は宛先ディレクトリの外側を指す
	return !(len(rel) >= 2 && rel[0:2] == "..")
}