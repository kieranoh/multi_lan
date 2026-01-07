package main

import (
	"net/url"
	"strings"
)

func getTargetForRedirect(target string, domain string) string {
	// 解析目标URL
	targetURL, err := url.Parse(target)
	if err != nil {
		// 如果解析失败，回退到域URL
		return "https://" + domain
	}

	// 确保使用https协议
	targetURL.Scheme = "https"

	// 获取目标URL的主机名
	hostname := targetURL.Hostname()
	if hostname == "" {
		// 如果没有主机名，回退到域URL
		return "https://" + domain
	}

	// 检查主机名是否在指定域内
	// 允许精确匹配或子域名匹配
	if hostname == domain || strings.HasSuffix(hostname, "."+domain) {
		// 返回完整的目标URL
		return targetURL.String()
	}

	// 不在域内，回退到域URL
	return "https://" + domain
}