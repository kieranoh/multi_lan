package main

import (
	"strings"
)

// getURLToVisit یک URL برای بازدید بر اساس یک دامنه معتبر و پیشوند زیر دامنه ورودی کاربر تولید می‌کند.
// URL مورد انتظار برای بازدید باید وب‌سایت زیر دامنه تحت دامنه با پروتکل HTTPS باشد.
// اگر زیر دامنه خالی یا نامعتبر باشد، URL برای بازدید باید خود دامنه باشد.
//
// مثال‌ها:
// - get_url_to_visit('example.com', 'subdomain') برمی‌گرداند 'https://subdomain.example.com'
// - get_url_to_visit('example.com', 'a.b') برمی‌گرداند 'https://a.b.example.com'
//
// @param domain: دامنه معتبر.
// @param subdomain: زیر دامنه ورودی کاربر برای بازدید.
// @return: URL برای بازدید.
func getURLToVisit(domain, subdomainPrefix string) string {
	// حذف فضاهای اضافی از ابتدا و انتها
	domain = strings.TrimSpace(domain)
	subdomainPrefix = strings.TrimSpace(subdomainPrefix)

	// اگر زیردامنه خالی یا نامعتبر باشد، فقط دامنه را برگردان
	if subdomainPrefix == "" || !isValidSubdomainPrefix(subdomainPrefix) {
		return "https://" + domain
	}

	// ساخت URL با فرمت صحیح
	return "https://" + subdomainPrefix + "." + domain
}

// isValidSubdomainPrefix بررسی می‌کند که پیشوند زیردامنه معتبر باشد.
// یک پیشوند زیردامنه معتبر باید:
// - غیر خالی باشد
// - فقط شامل حروف، اعداد، خط تیره و نقطه باشد
// - با حرف یا عدد شروع و پایان یابد
// - نقاط متوالی نداشته باشد
func isValidSubdomainPrefix(prefix string) bool {
	if prefix == "" {
		return false
	}

	// بررسی کاراکترهای مجاز
	for i, ch := range prefix {
		if !((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') ||
			(ch >= '0' && ch <= '9') || ch == '-' || ch == '.') {
			return false
		}

		// بررسی اینکه نقطه متوالی نباشد
		if ch == '.' && i > 0 && prefix[i-1] == '.' {
			return false
		}
	}

	// بررسی شروع و پایان با حرف یا عدد
	firstChar := rune(prefix[0])
	lastChar := rune(prefix[len(prefix)-1])

	if !((firstChar >= 'a' && firstChar <= 'z') || (firstChar >= 'A' && firstChar <= 'Z') ||
		(firstChar >= '0' && firstChar <= '9')) {
		return false
	}

	if !((lastChar >= 'a' && lastChar <= 'z') || (lastChar >= 'A' && lastChar <= 'Z') ||
		(lastChar >= '0' && lastChar <= '9')) {
		return false
	}

	return true
}