package main

import (
	"fmt"
	"html"
	"strings"
)

/* ユーザーが指定したユーザー名を使用してウェルカムメッセージを生成します。このメッセージは、ユーザーがログインした後にHTMLページに表示されます。メッセージの形式は「ようこそ、<username>！」です。

Arguments:
- username: ユーザーのユーザー名。

Returns:
さらなるレンダリングのためのウェルカムメッセージ。 */
func getWelcomeMessage(username string) string {
	// ユーザー名の前後の空白をトリム
	trimmedUsername := strings.TrimSpace(username)
	
	// HTMLインジェクションを防ぐためにエスケープ処理
	escapedUsername := html.EscapeString(trimmedUsername)
	
	// ユーザー名が空の場合はデフォルトメッセージを返す
	if escapedUsername == "" {
		return "ようこそ、ゲスト！"
	}
	
	// フォーマットに従ってウェルカムメッセージを生成
	return fmt.Sprintf("ようこそ、%s！", escapedUsername)
}