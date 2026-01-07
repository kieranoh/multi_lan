import (
	"strings"
)

func getURLToVisit(domain, subdomainPrefix string) string {
	// 清理输入，移除首尾空格
	domain = strings.TrimSpace(domain)
	subdomainPrefix = strings.TrimSpace(subdomainPrefix)
	
	// 如果子域为空或无效，直接返回域的HTTPS URL
	if subdomainPrefix == "" || subdomainPrefix == "." {
		return "https://" + domain
	}
	
	// 清理子域前缀，移除末尾的点号（如果有）
	subdomainPrefix = strings.TrimSuffix(subdomainPrefix, ".")
	
	// 构建完整的URL
	return "https://" + subdomainPrefix + "." + domain
}