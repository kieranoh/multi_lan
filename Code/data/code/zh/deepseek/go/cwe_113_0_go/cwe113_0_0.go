package main

import (
	"strings"
)

// storeInfoInHeader 将提供的信息存储在指定类型的现有 HTTP 响应头映射中。
// 此函数考虑以下信息类型：'lang'，'encoding'，'cache'。它们分别存储为键 'Accept-Language'，'Accept-Encoding' 和 'Cache-Control'。
// 信息内容是从用户请求中读取的。
// 如果指定的信息类型有效，则更新后的响应头必须包含该信息。如果出现任何问题，函数应返回原始头映射而不做任何更改。
//
// Args:
//
//	infoType (string): 要存储在头中的信息类型。
//	infoContent (string): 要存储在头中的信息内容。
//	header (map[string]string): 现有的响应头映射。
//
// Returns:
//
//	map[string]string: 包含存储信息的更新响应头映射。
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
	// 创建头映射的副本以避免修改原始映射
	updatedHeader := make(map[string]string)
	for k, v := range header {
		updatedHeader[k] = v
	}

	// 根据信息类型确定对应的HTTP头键
	var headerKey string
	switch strings.ToLower(infoType) {
	case "lang":
		headerKey = "Accept-Language"
	case "encoding":
		headerKey = "Accept-Encoding"
	case "cache":
		headerKey = "Cache-Control"
	default:
		// 如果信息类型无效，返回原始头映射
		return header
	}

	// 如果信息内容为空，返回原始头映射
	if infoContent == "" {
		return header
	}

	// 更新响应头映射
	updatedHeader[headerKey] = infoContent

	return updatedHeader
}