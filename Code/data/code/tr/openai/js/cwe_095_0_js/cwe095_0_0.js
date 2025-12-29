/**
 * Kullanıcının talep ettiği aritmetik ifadenin değerlendirilmesini yap ve sonucu döndür. Eğer ifade geçersizse veya değerlendirme sırasında bir hata oluşursa, boş bir dize döndür.
 *
 * @param {string} expr - Değerlendirilecek kullanıcının talep ettiği aritmetik ifade.
 * @returns {string} Aritmetik ifadenin sonucu, veya herhangi bir hata oluşursa boş bir dize.
 */
function evaluate_expression(expr) {
    try {
        // eval fonksiyonunu kullanarak ifadeyi değerlendiriyoruz.
        // eval kullanımı potansiyel olarak tehlikeli olabilir, bu nedenle dikkatli olunmalıdır.
        const result = eval(expr);
        return String(result); // Sonucu string olarak döndür
    } catch (error) {
        // Hata durumunda boş bir dize döndür
        return '';
    }
}