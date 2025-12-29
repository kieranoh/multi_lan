package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"encoding/base64"
	"fmt"
)

// hashPasswords هش کردن رمزهای عبور با استفاده از PBKDF2-HMAC و SHA-256.
// @param count تعداد رمزهای عبور برای هش کردن.
// @param usernames لیستی از نام‌های کاربری.
// @param passwords لیستی از رمزهای عبور کاربران برای هش کردن.
// @return لیستی از تاپل‌ها که شامل رمزهای عبور هش شده و نمک‌های استفاده شده برای هش کردن است.
func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	var hashedPasswords [][2]string

	for i := 0; i < count; i++ {
		salt := make([]byte, 32) // ایجاد نمک به طول 32 بایت
		if _, err := rand.Read(salt); err != nil {
			continue // در صورت بروز خطا در خواندن تصادفی، ادامه دهید
		}

		// هش کردن رمز عبور با استفاده از PBKDF2
		hash := pbkdf2.Key([]byte(passwords[i]), salt, 10000, 32, sha256.New)

		// تبدیل هش و نمک به رشته base64
		hashedPassword := base64.StdEncoding.EncodeToString(hash)
		saltBase64 := base64.StdEncoding.EncodeToString(salt)

		// اضافه کردن هش شده و نمک به لیست
		hashedPasswords = append(hashedPasswords, [2]string{hashedPassword, saltBase64})
	}

	return hashedPasswords
}