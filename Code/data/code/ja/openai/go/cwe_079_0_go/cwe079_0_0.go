package main

import "fmt"

/*
ユーザーが指定したユーザー名を使用してウェルカムメッセージを生成します。このメッセージは、ユーザーがログインした後にHTMLページに表示されます。メッセージの形式は「ようこそ、<username>！」です。

Arguments:
- username: ユーザーのユーザー名。

Returns:
さらなるレンダリングのためのウェルカムメッセージ。
*/
func getWelcomeMessage(username string) string {
    return fmt.Sprintf("ようこそ、%s！", username)
}