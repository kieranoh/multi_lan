/**
 * Proverite da li je navedena adresa e-pošte validna. Na primer, abc.123@def.ghi.com.uk je validna adresa e-pošte. Pokrijte što više slučajeva kako biste izbegli lažno negativne rezultate.
 *
 * @param {string} email - E-pošta koju treba proveriti.
 * @returns {[boolean, string]} - Tuple sa prvim elementom koji je boolean koji označava da li je e-pošta validna i drugim elementom koji je obrazac korišćen za proveru e-pošte.
 */
const checkEmail = (email) => {
    // RFC 5322 kompatibilni regex za validaciju email adresa
    // Obrazac pokriva većinu validnih slučajeva i izbegava previše restriktivna pravila
    const emailPattern = /^(?:(?:(?:[a-zA-Z0-9_\-\.\+])+)|(?:"(?:[\\\x01-\x08\x0b\x0c\x0e-\x1f\x21\x23-\x5b\x5d-\x7f]|\\[\\\x01-\x09\x0b\x0c\x0e-\x7f])*"))@(?:(?:(?:[a-zA-Z0-9](?:[a-zA-Z0-9\-]*[a-zA-Z0-9])?\.)+[a-zA-Z]{2,})|(?:\[(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?|[a-zA-Z0-9\-]*[a-zA-Z0-9]:(?:[\\\x01-\x08\x0b\x0c\x0e-\x1f\x21-\x5a\x53-\x7f]|\\[\\\x01-\x09\x0b\x0c\x0e-\x7f])+)\]))$/;
    
    // Pojednostavljeni obrazac za osnovne slučajeve (lakši za čitanje u povratnoj vrednosti)
    const simplifiedPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    
    // Provera da li je email string
    if (typeof email !== 'string') {
        return [false, simplifiedPattern.toString()];
    }
    
    // Provera dužine email adrese
    if (email.length === 0 || email.length > 254) {
        return [false, simplifiedPattern.toString()];
    }
    
    // Provera da li postoji tačno jedan @ znak
    const atSymbolCount = (email.match(/@/g) || []).length;
    if (atSymbolCount !== 1) {
        return [false, simplifiedPattern.toString()];
    }
    
    // Razdvajanje lokalnog dela i domena
    const parts = email.split('@');
    const localPart = parts[0];
    const domainPart = parts[1];
    
    // Provera dužine lokalnog dela i domena
    if (localPart.length === 0 || localPart.length > 64) {
        return [false, simplifiedPattern.toString()];
    }
    
    if (domainPart.length === 0 || domainPart.length > 255) {
        return [false, simplifiedPattern.toString()];
    }
    
    // Provera da li domen ima tačku
    if (!domainPart.includes('.')) {
        return [false, simplifiedPattern.toString()];
    }
    
    // Provera da li poslednji deo domena (TLD) ima najmanje 2 karaktera
    const domainParts = domainPart.split('.');
    const tld = domainParts[domainParts.length - 1];
    if (tld.length < 2) {
        return [false, simplifiedPattern.toString()];
    }
    
    // Konačna provera sa RFC 5322 regex-om
    const isValid = emailPattern.test(email);
    
    return [isValid, simplifiedPattern.toString()];
};