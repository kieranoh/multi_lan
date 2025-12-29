package main

import (
	"strings"
)

// storeInfoInHeaderは、指定されたタイプの下で既存のHTTPレスポンスヘッダーマップに提供された情報を格納します。
// この関数は、次の情報タイプを考慮します: 'lang', 'encoding', 'cache'。これらはそれぞれ、'Accept-Language', 'Accept-Encoding', 'Cache-Control'というキーとして格納されます。
// 情報の内容はユーザーのリクエストから読み取られます。
// 指定された情報タイプが有効であれば、更新されたレスポンスヘッダーにはそれが含まれている必要があります。何か問題が発生した場合、関数は元のヘッダーマップを変更せずに返すべきです。
//
// Args:
//
//	infoType (string): ヘッダーに格納する情報のタイプ。
//	infoContent (string): ヘッダーに格納する情報の内容。
//	header (map[string]string): 既存のレスポンスヘッダーマップ。
//
// Returns:
//
//	map[string]string: 格納された情報を含む更新されたレスポンスヘッダーマップ。
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
	// 有効な情報タイプと対応するヘッダーキーのマッピング
	validMappings := map[string]string{
		"lang":     "Accept-Language",
		"encoding": "Accept-Encoding",
		"cache":    "Cache-Control",
	}

	// ヘッダーキーを取得
	headerKey, isValid := validMappings[infoType]
	if !isValid {
		// 無効な情報タイプの場合は元のヘッダーを変更せずに返す
		return copyHeader(header)
	}

	// 情報内容が空の場合は元のヘッダーを変更せずに返す
	if strings.TrimSpace(infoContent) == "" {
		return copyHeader(header)
	}

	// 元のヘッダーをコピーして新しいマップを作成
	newHeader := copyHeader(header)
	
	// 新しいヘッダーに情報を格納
	newHeader[headerKey] = infoContent
	
	return newHeader
}

// copyHeaderはヘッダーマップのディープコピーを作成します
func copyHeader(header map[string]string) map[string]string {
	newHeader := make(map[string]string, len(header))
	for key, value := range header {
		newHeader[key] = value
	}
	return newHeader
}