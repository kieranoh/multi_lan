/**
 * Проверяет, является ли предоставленный адрес электронной почты действительным.
 * @param {string} email - Адрес электронной почты для проверки.
 * @returns {[boolean, string]} - Кортеж, где первый элемент - это булево значение, 
 * указывающее, действителен ли адрес электронной почты, а второй элемент - это 
 * шаблон, использованный для проверки адреса электронной почты.
 */
const checkEmail = (email) => {
    // Основной шаблон для проверки email согласно RFC 5322
    const rfc5322Pattern = /^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$/;
    
    // Альтернативный шаблон для более строгой проверки (рекомендуемый)
    const commonPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    
    // Шаблон для международных доменов (IDN)
    const idnPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}(\.[a-zA-Z]{2,})?$/;
    
    // Шаблон для длинных доменных зон (например, .museum, .international)
    const longTldPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,24}$/;
    
    // Проверка на пустую строку или слишком длинный email
    if (!email || typeof email !== 'string' || email.length > 254) {
        return [false, 'invalid_length'];
    }
    
    // Проверка на наличие символа @
    const atIndex = email.indexOf('@');
    if (atIndex < 1 || atIndex === email.length - 1) {
        return [false, 'no_at_symbol'];
    }
    
    // Разделение на локальную часть и домен
    const localPart = email.substring(0, atIndex);
    const domain = email.substring(atIndex + 1);
    
    // Проверка длины локальной части (максимум 64 символа по RFC)
    if (localPart.length > 64) {
        return [false, 'local_part_too_long'];
    }
    
    // Проверка, что локальная часть не начинается и не заканчивается точкой
    if (localPart.startsWith('.') || localPart.endsWith('.')) {
        return [false, 'invalid_local_part'];
    }
    
    // Проверка на две точки подряд в локальной части
    if (localPart.includes('..')) {
        return [false, 'invalid_local_part'];
    }
    
    // Проверка домена
    if (domain.length > 253) {
        return [false, 'domain_too_long'];
    }
    
    // Проверка, что домен не начинается и не заканчивается точкой или дефисом
    if (domain.startsWith('.') || domain.endsWith('.') || 
        domain.startsWith('-') || domain.endsWith('-')) {
        return [false, 'invalid_domain'];
    }
    
    // Проверка на две точки подряд в домене
    if (domain.includes('..')) {
        return [false, 'invalid_domain'];
    }
    
    // Разделение домена на части
    const domainParts = domain.split('.');
    
    // Проверка, что домен имеет хотя бы 2 части
    if (domainParts.length < 2) {
        return [false, 'invalid_domain_parts'];
    }
    
    // Проверка каждой части домена
    for (const part of domainParts) {
        // Часть не должна быть пустой
        if (!part || part.length === 0) {
            return [false, 'empty_domain_part'];
        }
        
        // Часть не должна начинаться или заканчиваться дефисом
        if (part.startsWith('-') || part.endsWith('-')) {
            return [false, 'invalid_domain_part'];
        }
        
        // Проверка допустимых символов в части домена
        if (!/^[a-zA-Z0-9-]+$/.test(part)) {
            return [false, 'invalid_domain_chars'];
        }
        
        // Длина части домена (максимум 63 символа)
        if (part.length > 63) {
            return [false, 'domain_part_too_long'];
        }
    }
    
    // Проверка TLD (последней части домена)
    const tld = domainParts[domainParts.length - 1];
    if (!/^[a-zA-Z]{2,}$/.test(tld)) {
        return [false, 'invalid_tld'];
    }
    
    // Проверка с использованием основного шаблона RFC 5322
    if (rfc5322Pattern.test(email)) {
        return [true, 'rfc5322_pattern'];
    }
    
    // Проверка с использованием общего шаблона
    if (commonPattern.test(email)) {
        return [true, 'common_pattern'];
    }
    
    // Проверка с использованием шаблона для IDN
    if (idnPattern.test(email)) {
        return [true, 'idn_pattern'];
    }
    
    // Проверка с использованием шаблона для длинных TLD
    if (longTldPattern.test(email)) {
        return [true, 'long_tld_pattern'];
    }
    
    // Если ни один шаблон не подошел
    return [false, 'no_pattern_matched'];
};