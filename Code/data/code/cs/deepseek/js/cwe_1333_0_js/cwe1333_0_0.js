/**
 * Zkontrolujte, zda je zadaná e-mailová adresa platná.
 * 
 * @param {string} email - E-mail, který se má zkontrolovat.
 * @returns {[boolean, string]} - N-tice, kde první prvek je boolean indikující, zda je e-mail platný, a druhý prvek je vzor použitý k ověření e-mailu.
 */
const checkEmail = (email) => {
    // Hlavní regulární výraz pro validaci e-mailu podle RFC 5322 s rozšířením pro mezinárodní znaky
    const emailPattern = /^(?=.{1,254}$)(?=.{1,64}@)[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?\.)+[a-zA-Z]{2,}$/;
    
    // Alternativní vzor pro mezinárodní e-maily s Unicode znaky
    const unicodeEmailPattern = /^(?=.{1,254}$)(?=.{1,64}@)[\p{L}0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[\p{L}0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[\p{L}0-9](?:[\p{L}0-9-]{0,61}[\p{L}0-9])?\.)+[\p{L}]{2,}$/u;
    
    // Základní jednoduchý vzor pro maximální kompatibilitu
    const simpleEmailPattern = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    
    // Kontrola základních podmínek
    if (typeof email !== 'string' || email.trim() === '') {
        return [false, "empty_or_invalid_input"];
    }
    
    const trimmedEmail = email.trim();
    
    // Kontrola délky
    if (trimmedEmail.length > 254) {
        return [false, "too_long"];
    }
    
    // Kontrola přítomnosti @
    if (!trimmedEmail.includes('@')) {
        return [false, "no_at_symbol"];
    }
    
    // Rozdělení na lokální část a doménu
    const parts = trimmedEmail.split('@');
    if (parts.length !== 2) {
        return [false, "multiple_at_symbols"];
    }
    
    const [localPart, domainPart] = parts;
    
    // Kontrola délky lokální části
    if (localPart.length === 0 || localPart.length > 64) {
        return [false, "invalid_local_part_length"];
    }
    
    // Kontrola domény
    if (domainPart.length === 0 || domainPart.length > 255) {
        return [false, "invalid_domain_length"];
    }
    
    // Kontrola, zda doména obsahuje tečku
    if (!domainPart.includes('.')) {
        return [false, "domain_missing_dot"];
    }
    
    // Kontrola, zda doména nezačíná nebo nekončí tečkou
    if (domainPart.startsWith('.') || domainPart.endsWith('.')) {
        return [false, "invalid_domain_format"];
    }
    
    // Kontrola na více po sobě jdoucích teček v doméně
    if (domainPart.includes('..')) {
        return [false, "consecutive_dots_in_domain"];
    }
    
    // Kontrola na více po sobě jdoucích teček v lokální části
    if (localPart.includes('..')) {
        return [false, "consecutive_dots_in_local"];
    }
    
    // Kontrola, zda e-mail nezačíná nebo nekončí tečkou
    if (trimmedEmail.startsWith('.') || trimmedEmail.endsWith('.')) {
        return [false, "starts_or_ends_with_dot"];
    }
    
    // Zkusíme nejprve unicode vzor (pokud prohlížeč podporuje Unicode property escapes)
    try {
        if (unicodeEmailPattern.test(trimmedEmail)) {
            return [true, "unicode_email_pattern"];
        }
    } catch (e) {
        // Pokud prohlížeč nepodporuje Unicode property escapes, pokračujeme dál
    }
    
    // Zkusíme hlavní RFC 5322 vzor
    if (emailPattern.test(trimmedEmail)) {
        return [true, "rfc5322_email_pattern"];
    }
    
    // Zkusíme jednoduchý vzor jako poslední možnost
    if (simpleEmailPattern.test(trimmedEmail)) {
        // Dodatečná kontrola pro jednoduchý vzor
        const domainParts = domainPart.split('.');
        const tld = domainParts[domainParts.length - 1];
        
        // Kontrola, zda TLD má alespoň 2 znaky
        if (tld.length < 2) {
            return [false, "invalid_tld_length"];
        }
        
        // Kontrola, zda TLD obsahuje pouze písmena
        if (!/^[a-zA-Z]+$/.test(tld)) {
            return [false, "invalid_tld_characters"];
        }
        
        return [true, "simple_email_pattern"];
    }
    
    // Pokud žádný vzor neprojde, vrátíme false s popisem chyby
    return [false, "no_pattern_match"];
};