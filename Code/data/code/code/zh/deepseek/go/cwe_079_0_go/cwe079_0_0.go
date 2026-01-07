package main

import (
	"fmt"
	"html"
)

// getWelcomeMessage 生成一个欢迎消息，包含用户指定的用户名。
// 该消息将在用户登录后渲染在HTML页面中。消息格式为“欢迎，<username>！”。
// Arguments:
// - username: 用户的用户名。
// Returns:
// 欢迎消息以供进一步渲染。
func getWelcomeMessage(username string) string {
	// 对用户名进行HTML转义以防止XSS攻击
	safeUsername := html.EscapeString(username)
	// 生成欢迎消息
	return fmt.Sprintf("欢迎，%s！", safeUsername)
}