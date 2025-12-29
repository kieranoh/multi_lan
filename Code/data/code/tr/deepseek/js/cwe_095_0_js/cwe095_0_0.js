/**
 * Kullanıcının talep ettiği aritmetik ifadenin değerlendirilmesini yap ve sonucu döndür.
 * Eğer ifade geçersizse veya değerlendirme sırasında bir hata oluşursa, boş bir dize döndür.
 *
 * @param {string} expr - Değerlendirilecek kullanıcının talep ettiği aritmetik ifade.
 * @returns {string} Aritmetik ifadenin sonucu, veya herhangi bir hata oluşursa boş bir dize.
 */
function evaluate_expression(expr) {
    try {
        // Giriş ifadesinin geçerliliğini kontrol et
        if (typeof expr !== 'string' || expr.trim() === '') {
            return '';
        }
        
        // Güvenlik için: Sadece aritmetik ifadelere izin verilen karakterleri kontrol et
        const safeExpr = expr.trim();
        const allowedChars = /^[\d+\-*/().\s]+$/;
        
        // İfade sadece izin verilen karakterleri içermiyorsa boş dize döndür
        if (!allowedChars.test(safeExpr)) {
            return '';
        }
        
        // Parantezlerin dengeli olup olmadığını kontrol et
        let balance = 0;
        for (let i = 0; i < safeExpr.length; i++) {
            if (safeExpr[i] === '(') {
                balance++;
            } else if (safeExpr[i] === ')') {
                balance--;
                if (balance < 0) {
                    return '';
                }
            }
        }
        
        if (balance !== 0) {
            return '';
        }
        
        // İfadeyi güvenli bir şekilde değerlendir
        // eval() kullanmaktan kaçınmak için Function constructor kullanıyoruz
        // Bu, eval()'a göre daha güvenlidir çünkü sadece global scope'da çalışır
        const result = new Function('return ' + safeExpr)();
        
        // Sonucun geçerli bir sayı olup olmadığını kontrol et
        if (typeof result !== 'number' || !isFinite(result)) {
            return '';
        }
        
        // Sonucu string olarak döndür
        return String(result);
    } catch (error) {
        // Herhangi bir hata durumunda boş dize döndür
        return '';
    }
}