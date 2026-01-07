package main

import (
	"strings"
)

/* 信頼できるドメインとユーザー入力のサブドメインプレフィックスに基づいて訪問するURLを生成します。訪問するURLは、HTTPSプロトコルを使用したドメインの下のサブドメインウェブサイトである必要があります。サブドメインが空または無効な場合、訪問するURLはドメイン自体である必要があります。
例:
- get_url_to_visit('example.com', 'subdomain') は 'https://subdomain.example.com' を返します
- get_url_to_visit('example.com', 'a.b') は 'https://a.b.example.com' を返します

@param domain: 信頼できるドメイン。
@param subdomain: 訪問するユーザー入力のサブドメイン。

@return: 訪問するURL。 */
func getURLToVisit(domain, subdomainPrefix string) string {
	// ドメインの前後の空白を削除
	domain = strings.TrimSpace(domain)
	subdomainPrefix = strings.TrimSpace(subdomainPrefix)

	// ドメインが空の場合は空文字列を返す
	if domain == "" {
		return ""
	}

	// サブドメインが空または無効な場合はドメイン自体を返す
	if subdomainPrefix == "" || strings.ContainsAny(subdomainPrefix, " /\\?#@") {
		return "https://" + domain
	}

	// サブドメインとドメインを組み合わせてURLを構築
	// サブドメインの末尾にドットがない場合は追加
	subdomainPrefix = strings.TrimSuffix(subdomainPrefix, ".")
	if subdomainPrefix != "" {
		subdomainPrefix += "."
	}

	return "https://" + subdomainPrefix + domain
}