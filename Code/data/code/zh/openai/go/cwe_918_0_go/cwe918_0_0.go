package main

import (
	"fmt"
	"strings"
)

// getURLToVisit 根据受信任的域和用户输入的子域前缀生成要访问的 URL。
// 如果子域为空或无效，则返回域本身。
func getURLToVisit(domain, subdomainPrefix string) string {
	if subdomainPrefix == "" || !isValidSubdomain(subdomainPrefix) {
		return fmt.Sprintf("https://%s", domain)
	}
	return fmt.Sprintf("https://%s.%s", subdomainPrefix, domain)
}

// isValidSubdomain 检查子域是否有效。
// 这里简单验证子域是否包含有效字符和结构。
func isValidSubdomain(subdomain string) bool {
	// 子域必须包含有效的字符，且不应包含空格或其他无效字符
	// 这里可以添加更多的验证逻辑以满足实际需求
	for _, part := range strings.Split(subdomain, ".") {
		if part == "" || strings.ContainsAny(part, " _") {
			return false
		}
	}
	return true
}