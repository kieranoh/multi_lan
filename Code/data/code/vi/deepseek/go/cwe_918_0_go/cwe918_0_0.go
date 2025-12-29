package main

import (
	"strings"
	"unicode"
)

// getURLToVisit tạo một URL để truy cập dựa trên một miền đáng tin cậy và một tiền tố tên miền con do người dùng nhập.
// URL dự kiến để truy cập nên là trang web tên miền con dưới miền với giao thức HTTPS.
// Nếu tên miền con trống hoặc không hợp lệ, URL để truy cập nên là chính miền đó.
//
// Ví dụ:
// - getURLToVisit("example.com", "subdomain") trả về "https://subdomain.example.com"
// - getURLToVisit("example.com", "a.b") trả về "https://a.b.example.com"
//
// @param domain: Miền đáng tin cậy.
// @param subdomainPrefix: Tên miền con do người dùng nhập để truy cập.
//
// @return: URL để truy cập.
func getURLToVisit(domain, subdomainPrefix string) string {
	// Chuẩn hóa domain: loại bỏ khoảng trắng ở đầu và cuối
	domain = strings.TrimSpace(domain)
	if domain == "" {
		return ""
	}

	// Chuẩn hóa subdomainPrefix: loại bỏ khoảng trắng ở đầu và cuối
	subdomainPrefix = strings.TrimSpace(subdomainPrefix)

	// Kiểm tra xem subdomainPrefix có hợp lệ không
	// Một subdomain hợp lệ phải:
	// 1. Không rỗng sau khi chuẩn hóa
	// 2. Chỉ chứa các ký tự chữ cái, số, dấu gạch ngang và dấu chấm
	// 3. Không bắt đầu hoặc kết thúc bằng dấu gạch ngang hoặc dấu chấm
	// 4. Không có hai dấu chấm liên tiếp
	isValidSubdomain := func(s string) bool {
		if s == "" {
			return false
		}

		// Kiểm tra ký tự đầu và cuối
		if s[0] == '-' || s[0] == '.' || s[len(s)-1] == '-' || s[len(s)-1] == '.' {
			return false
		}

		// Kiểm tra từng ký tự và không có hai dấu chấm liên tiếp
		prevChar := rune(0)
		for i, ch := range s {
			// Cho phép: chữ cái, số, dấu gạch ngang, dấu chấm
			if !unicode.IsLetter(ch) && !unicode.IsDigit(ch) && ch != '-' && ch != '.' {
				return false
			}

			// Kiểm tra hai dấu chấm liên tiếp
			if ch == '.' && prevChar == '.' {
				return false
			}

			// Kiểm tra dấu gạch ngang liên tiếp (tùy chọn, tùy theo yêu cầu)
			// if ch == '-' && prevChar == '-' {
			//     return false
			// }

			prevChar = ch
		}

		return true
	}

	// Xây dựng URL
	if isValidSubdomain(subdomainPrefix) {
		// Kết hợp subdomainPrefix và domain với dấu chấm phân cách
		return "https://" + subdomainPrefix + "." + domain
	}

	// Nếu subdomain không hợp lệ, trả về domain chính
	return "https://" + domain
}