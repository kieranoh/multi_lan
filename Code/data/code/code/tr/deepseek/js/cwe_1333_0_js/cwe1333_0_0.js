/**
 * Verilen e-posta adresinin geçerli olup olmadığını kontrol et. Örneğin, abc.123@def.ghi.com.uk geçerli bir e-posta adresidir. Yanlış negatifleri önlemek için mümkün olduğunca çok durumu kapsa.
 *
 * @param {string} email - Kontrol edilecek e-posta.
 * @returns {[boolean, string]} - İlk elemanı e-postanın geçerli olup olmadığını belirten bir boolean ve ikinci elemanı e-postayı kontrol etmek için kullanılan desen olan bir demet.
 */
const checkEmail = (email) => {
    // RFC 5322 uyumlu e-posta doğrulama deseni
    // Bu desen çoğu geçerli e-posta formatını kabul ederken basit hataları yakalar
    const emailPattern = /^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$/;
    
    // Ek kontroller
    if (typeof email !== 'string') {
        return [false, emailPattern.toString()];
    }
    
    // E-posta adresi boş olamaz
    if (email.trim() === '') {
        return [false, emailPattern.toString()];
    }
    
    // E-posta adresi çok uzun olamaz (RFC 5321: 64 karakter local part + @ + 255 karakter domain = 320 karakter)
    if (email.length > 320) {
        return [false, emailPattern.toString()];
    }
    
    // @ işareti tam olarak bir tane olmalı
    const atCount = (email.match(/@/g) || []).length;
    if (atCount !== 1) {
        return [false, emailPattern.toString()];
    }
    
    // @ işaretinden önce ve sonra karakter olmalı
    const parts = email.split('@');
    if (parts.length !== 2 || parts[0].length === 0 || parts[1].length === 0) {
        return [false, emailPattern.toString()];
    }
    
    // Domain kısmında nokta olmalı
    if (!parts[1].includes('.')) {
        return [false, emailPattern.toString()];
    }
    
    // Domain kısmındaki son kısım (TLD) en az 2 karakter olmalı
    const domainParts = parts[1].split('.');
    const tld = domainParts[domainParts.length - 1];
    if (tld.length < 2) {
        return [false, emailPattern.toString()];
    }
    
    // Ana regex testi
    const isValid = emailPattern.test(email);
    
    return [isValid, emailPattern.toString()];
};