package main

import (
	"net/url"
	"strings"
)

/* 提供されたターゲットURL文字列が指定されたドメイン内にあるか確認します。
もしそうであれば、リダイレクト用のターゲットURLを返します。そうでなければ、リダイレクト用のドメインURLにフォールバックします。
httpsプロトコルを使用します。

Examples:

	getTargetForRedirect("https://music.example.com", "example.com") -> "https://music.example.com"
	getTargetForRedirect("https://example.com/service", "example.com") -> "https://example.com/service"
	getTargetForRedirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
	getTargetForRedirect("https://another.com", "example.com") -> "https://example.com"

@param target: ターゲットURL文字列。
@param domain: プロトコルなしのドメイン文字列。

@return リダイレクト用のURL文字列。 */
func getTargetForRedirect(target string, domain string) string {
	// 空のターゲットの場合はドメインURLを返す
	if target == "" {
		return "https://" + domain
	}

	// ターゲットURLをパース
	parsedURL, err := url.Parse(target)
	if err != nil {
		// パースに失敗した場合はドメインURLを返す
		return "https://" + domain
	}

	// ホストが空の場合はドメインURLを返す
	if parsedURL.Host == "" {
		return "https://" + domain
	}

	// ホストが指定されたドメインまたはそのサブドメインであるかを確認
	if strings.HasSuffix(parsedURL.Host, "."+domain) || parsedURL.Host == domain {
		// 元のターゲットURLを返す（既にhttpsプロトコルを使用していると仮定）
		return target
	}

	// ドメインに一致しない場合はドメインURLを返す
	return "https://" + domain
}