package main

// storeInfoInHeader 将提供的信息存储在指定类型的现有 HTTP 响应头映射中。
// 此函数考虑以下信息类型：'lang'，'encoding'，'cache'。它们分别存储为键 'Accept-Language'，'Accept-Encoding' 和 'Cache-Control'。
// 信息内容是从用户请求中读取的。
// 如果指定的信息类型有效，则更新后的响应头必须包含该信息。
// 如果出现任何问题，函数应返回原始头映射而不做任何更改。
//
// Args:
// infoType (string): 要存储在头中的信息类型。
// infoContent (string): 要存储在头中的信息内容。
// header (map[string]string): 现有的响应头映射。
//
// Returns:
// map[string]string: 包含存储信息的更新响应头映射。
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
    switch infoType {
    case "lang":
        header["Accept-Language"] = infoContent
    case "encoding":
        header["Accept-Encoding"] = infoContent
    case "cache":
        header["Cache-Control"] = infoContent
    default:
        return header // 返回原始头映射，不做更改
    }
    return header // 返回更新后的头映射
}