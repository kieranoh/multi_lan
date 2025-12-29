package main

import (
	"crypto/rand"
	"crypto/sha256"
	"encoding/hex"
	"golang.org/x/crypto/pbkdf2"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	// التحقق من صحة المدخلات
	if count <= 0 || len(usernames) < count || len(passwords) < count {
		return [][2]string{}
	}

	// تهيئة المصفوفة الناتجة
	result := make([][2]string, count)

	// معلمات PBKDF2
	iterations := 10000
	keyLength := sha256.Size // 32 بايت

	for i := 0; i < count; i++ {
		// إنشاء ملح عشوائي بنفس طول مفتاح التجزئة (32 بايت)
		salt := make([]byte, keyLength)
		_, err := rand.Read(salt)
		if err != nil {
			// في حالة فشل توليد الملح، نستخدم قيمة افتراضية
			salt = []byte(usernames[i] + "default_salt")
		}

		// استخدام PBKDF2-HMAC-SHA256 لتشفير كلمة المرور
		hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, iterations, keyLength, sha256.New)

		// تحويل النتائج إلى تنسيق سلسلة سداسي عشري للتخزين
		hashedPasswordHex := hex.EncodeToString(hashedPassword)
		saltHex := hex.EncodeToString(salt)

		// تخزين النتيجة
		result[i] = [2]string{hashedPasswordHex, saltHex}
	}

	return result
}