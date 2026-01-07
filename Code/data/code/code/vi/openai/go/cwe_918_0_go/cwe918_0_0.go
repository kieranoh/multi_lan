package main

import (
	"fmt"
	"strings"
)

// getURLToVisit tạo một URL để truy cập dựa trên một miền đáng tin cậy và một tiền tố tên miền con do người dùng nhập.
// Nếu tên miền con trống hoặc không hợp lệ, URL để truy cập sẽ là chính miền đó.
// @param domain: Miền đáng tin cậy.
// @param subdomain: Tên miền con do người dùng nhập để truy cập.
// @return: URL để truy cập.
func getURLToVisit(domain, subdomainPrefix string) string {
	if subdomainPrefix == "" || strings.Contains(subdomainPrefix, ".") {
		return "https://" + domain
	}
	return "https://" + subdomainPrefix + "." + domain
}

func main() {
	fmt.Println(getURLToVisit("example.com", "subdomain")) // Kết quả: https://subdomain.example.com
	fmt.Println(getURLToVisit("example.com", "a.b"))       // Kết quả: https://example.com
	fmt.Println(getURLToVisit("example.com", ""))           // Kết quả: https://example.com
}