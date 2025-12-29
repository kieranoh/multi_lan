package main

import (
	"fmt"
	"net/url"
	"strings"
)

/* Kiểm tra xem chuỗi URL mục tiêu được cung cấp có nằm trong miền được cung cấp hay không.
Nếu có, trả về URL mục tiêu để chuyển hướng; nếu không, quay lại URL miền để chuyển hướng.
Sử dụng giao thức https.

Ví dụ:

	getTargetForRedirect("https://music.example.com", "example.com") -> "https://music.example.com"
	getTargetForRedirect("https://example.com/service", "example.com") -> "https://example.com/service"
	getTargetForRedirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
	getTargetForRedirect("https://another.com", "example.com") -> "https://example.com"

@param target: Chuỗi URL mục tiêu.
@param domain: Chuỗi miền, không có giao thức.

@return Chuỗi URL để chuyển hướng. */
func getTargetForRedirect(target string, domain string) string {
	// Chuẩn hóa domain: loại bỏ khoảng trắng và chuyển về chữ thường
	domain = strings.TrimSpace(strings.ToLower(domain))
	
	// Phân tích URL mục tiêu
	targetURL, err := url.Parse(target)
	if err != nil {
		// Nếu URL mục tiêu không hợp lệ, trả về URL domain với https
		return "https://" + domain
	}
	
	// Lấy host từ URL mục tiêu
	targetHost := strings.ToLower(targetURL.Hostname())
	
	// Kiểm tra xem targetHost có kết thúc bằng domain không
	// Đảm bảo so khớp chính xác domain (ví dụ: example.com không khớp với anotherexample.com)
	if targetHost == domain || strings.HasSuffix(targetHost, "."+domain) {
		// Nếu URL mục tiêu đã có https, giữ nguyên
		if targetURL.Scheme == "https" {
			return targetURL.String()
		}
		// Nếu không, chuyển sang https
		targetURL.Scheme = "https"
		return targetURL.String()
	}
	
	// Nếu không thuộc domain, trả về URL domain với https
	return "https://" + domain
}