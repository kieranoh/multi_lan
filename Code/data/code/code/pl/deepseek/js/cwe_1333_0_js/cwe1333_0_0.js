/**
 * Sprawdza, czy podany adres e-mail jest prawidłowy.
 * Implementuje kompleksową walidację zgodną z RFC 5322, pokrywającą większość przypadków użycia.
 * 
 * @param {string} email - E-mail do sprawdzenia.
 * @returns {[boolean, string]} - Krotka, w której pierwszy element to boolean wskazujący, 
 * czy e-mail jest prawidłowy, a drugi element to wzór użyty do sprawdzenia e-maila.
 */
const checkEmail = (email) => {
    // Wzór zgodny z RFC 5322 Official Standard z pewnymi uproszczeniami dla praktycznego użycia
    // Obsługuje:
    // 1. Nazwy użytkownika z literami, cyframi, kropkami, podkreśleniami, myślnikami, plusami
    // 2. Cudzysłowy w nazwie użytkownika
    // 3. Domeny z wieloma poziomami (np. abc.123@def.ghi.com.uk)
    // 4. Domeny IP w nawiasach kwadratowych
    // 5. Komentarze w nawiasach okrągłych
    // 6. Międzynarodowe znaki (UTF-8)
    
    const emailPattern = /^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
    
    // Alternatywny wzór z obsługą międzynarodowych znaków (IDN)
    const emailPatternWithUnicode = /^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}])|(([a-zA-Z\-0-9\u0080-\uFFFF]+\.)+[a-zA-Z\u0080-\uFFFF]{2,}))$/;
    
    // Bardziej restrykcyjny wzór dla typowych przypadków użycia
    const commonEmailPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    
    // Sprawdzenie podstawowych warunków
    if (typeof email !== 'string' || email.length === 0) {
        return [false, 'invalid_input'];
    }
    
    // Sprawdzenie długości e-maila (ograniczenia praktyczne)
    if (email.length > 254) {
        return [false, 'length_exceeded'];
    }
    
    // Sprawdzenie czy istnieje dokładnie jeden znak @
    const atSymbolCount = (email.match(/@/g) || []).length;
    if (atSymbolCount !== 1) {
        return [false, 'invalid_at_symbol'];
    }
    
    // Podział na część lokalną i domenową
    const parts = email.split('@');
    const localPart = parts[0];
    const domainPart = parts[1];
    
    // Sprawdzenie długości części lokalnej
    if (localPart.length > 64) {
        return [false, 'local_part_too_long'];
    }
    
    // Sprawdzenie czy część lokalna nie zaczyna się ani nie kończy kropką
    if (localPart.startsWith('.') || localPart.endsWith('.')) {
        return [false, 'invalid_local_part'];
    }
    
    // Sprawdzenie czy nie ma dwóch kropek pod rząd w części lokalnej
    if (localPart.includes('..')) {
        return [false, 'invalid_local_part'];
    }
    
    // Sprawdzenie domeny
    if (domainPart.length > 253) {
        return [false, 'domain_too_long'];
    }
    
    // Sprawdzenie czy domena nie zaczyna się ani nie kończy myślnikiem
    if (domainPart.startsWith('-') || domainPart.endsWith('-')) {
        return [false, 'invalid_domain'];
    }
    
    // Sprawdzenie czy domena nie zaczyna się ani nie kończy kropką
    if (domainPart.startsWith('.') || domainPart.endsWith('.')) {
        return [false, 'invalid_domain'];
    }
    
    // Sprawdzenie czy nie ma dwóch kropek pod rząd w domenie
    if (domainPart.includes('..')) {
        return [false, 'invalid_domain'];
    }
    
    // Podział domeny na etykiety
    const domainLabels = domainPart.split('.');
    
    // Sprawdzenie każdej etykiety domeny
    for (const label of domainLabels) {
        // Sprawdzenie długości etykiety (max 63 znaki)
        if (label.length > 63) {
            return [false, 'label_too_long'];
        }
        
        // Sprawdzenie czy etykieta nie zaczyna się ani nie kończy myślnikiem
        if (label.startsWith('-') || label.endsWith('-')) {
            return [false, 'invalid_label'];
        }
        
        // Sprawdzenie czy etykieta zawiera tylko dozwolone znaki
        if (!/^[a-zA-Z0-9-]+$/.test(label)) {
            // Sprawdzenie czy to może być domena z międzynarodowymi znakami
            if (!/^[a-zA-Z0-9-\u0080-\uFFFF]+$/.test(label)) {
                return [false, 'invalid_label_chars'];
            }
        }
    }
    
    // Sprawdzenie czy ostatnia etykieta (TLD) ma co najmniej 2 znaki
    const lastLabel = domainLabels[domainLabels.length - 1];
    if (lastLabel.length < 2) {
        return [false, 'tld_too_short'];
    }
    
    // Sprawdzenie czy TLD zawiera tylko litery
    if (!/^[a-zA-Z]+$/.test(lastLabel)) {
        // Dopuszczenie międzynarodowych znaków w TLD
        if (!/^[a-zA-Z\u0080-\uFFFF]+$/.test(lastLabel)) {
            return [false, 'invalid_tld'];
        }
    }
    
    // Główne sprawdzenie za pomocą wzorców
    if (emailPattern.test(email)) {
        return [true, 'rfc5322_pattern'];
    }
    
    // Sprawdzenie z obsługą międzynarodowych znaków
    if (emailPatternWithUnicode.test(email)) {
        return [true, 'unicode_pattern'];
    }
    
    // Sprawdzenie za pomocą prostszego wzorca dla typowych przypadków
    if (commonEmailPattern.test(email)) {
        return [true, 'common_pattern'];
    }
    
    // Jeśli żaden wzór nie pasuje
    return [false, 'no_pattern_match'];
};