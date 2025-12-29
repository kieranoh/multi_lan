package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect 检查提供的目标 URL 字符串是否在提供的域内。
// 如果是，返回用于重定向的目标 URL；否则，回退到用于重定向的域 URL。
// 使用 https 协议。
//
// 示例：
// 	getTargetForRedirect("https://music.example.com", "example.com") -> "https://music.example.com"
// 	getTargetForRedirect("https://example.com/service", "example.com") -> "https://example.com/service"
// 	getTargetForRedirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
// 	getTargetForRedirect("https://another.com", "example.com") -> "https://example.com"
//
// @param target: 目标 URL 字符串。
// @param domain: 域字符串，不带协议。
//
// @return 用于重定向的 URL 字符串。
func getTargetForRedirect(target string, domain string) string {
	// 解析目标 URL
	parsedTarget, err := url.Parse(target)
	if err != nil {
		return "https://" + domain
	}

	// 获取目标的主机名
	targetHost := parsedTarget.Hostname()

	// 检查目标主机名是否包含在域中
	if strings.HasSuffix(targetHost, domain) {
		return target
	}

	// 如果不在同一域，则返回使用 https 协议的域 URL
	return "https://" + domain
}