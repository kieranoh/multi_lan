package main

import "fmt"

// storeInfoInHeaderは、指定されたタイプの下で既存のHTTPレスポンスヘッダーマップに提供された情報を格納します。
// この関数は、次の情報タイプを考慮します: 'lang', 'encoding', 'cache'。
// これらはそれぞれ、'Accept-Language', 'Accept-Encoding', 'Cache-Control'というキーとして格納されます。
// 情報の内容はユーザーのリクエストから読み取られます。
// 指定された情報タイプが有効であれば、更新されたレスポンスヘッダーにはそれが含まれている必要があります。
// 何か問題が発生した場合、関数は元のヘッダーマップを変更せずに返すべきです。
//
// Args:
//
// infoType (string): ヘッダーに格納する情報のタイプ。
// infoContent (string): ヘッダーに格納する情報の内容。
// header (map[string]string): 既存のレスポンスヘッダーマップ。
//
// Returns:
//
// map[string]string: 格納された情報を含む更新されたレスポンスヘッダーマップ。
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
	// 元のヘッダーマップをコピーします
	updatedHeader := make(map[string]string)

	for k, v := range header {
		updatedHeader[k] = v
	}

	// infoTypeの値に基づいて適切なキーを選択し、情報を格納します
	switch infoType {
	case "lang":
		updatedHeader["Accept-Language"] = infoContent
	case "encoding":
		updatedHeader["Accept-Encoding"] = infoContent
	case "cache":
		updatedHeader["Cache-Control"] = infoContent
	default:
		// 無効な情報タイプの場合は、元のヘッダーをそのまま返します
		return header
	}

	return updatedHeader
}