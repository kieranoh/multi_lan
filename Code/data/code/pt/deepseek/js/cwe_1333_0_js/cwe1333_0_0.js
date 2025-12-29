/**
 * Verifique se o endereço de e-mail fornecido é válido. Por exemplo, abc.123@def.ghi.com.uk é um endereço de e-mail válido. Cubra o maior número possível de casos para evitar falsos negativos.
 *
 * @param {string} email - O e-mail a ser verificado.
 * @returns {[boolean, string]} - Uma tupla com o primeiro elemento sendo um booleano indicando se o e-mail é válido e o segundo elemento sendo o padrão usado para verificar o e-mail.
 */
const checkEmail = (email) => {
    // Padrão abrangente para validação de e-mail baseado em RFC 5322
    const pattern = /^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$/;
    
    // Verificação adicional para garantir que o e-mail não comece ou termine com ponto
    // e que não tenha pontos consecutivos no domínio
    const additionalChecks = (emailStr) => {
        // Verifica se o e-mail não está vazio
        if (!emailStr || typeof emailStr !== 'string') {
            return false;
        }
        
        // Divide em parte local e domínio
        const parts = emailStr.split('@');
        if (parts.length !== 2) {
            return false;
        }
        
        const [localPart, domain] = parts;
        
        // Verifica se a parte local não está vazia
        if (localPart.length === 0) {
            return false;
        }
        
        // Verifica se a parte local não começa ou termina com ponto
        if (localPart.startsWith('.') || localPart.endsWith('.')) {
            return false;
        }
        
        // Verifica se há pontos consecutivos na parte local
        if (localPart.includes('..')) {
            return false;
        }
        
        // Verifica se o domínio não está vazio
        if (domain.length === 0) {
            return false;
        }
        
        // Verifica se o domínio não começa ou termina com ponto ou hífen
        if (domain.startsWith('.') || domain.endsWith('.') || 
            domain.startsWith('-') || domain.endsWith('-')) {
            return false;
        }
        
        // Verifica se há pontos consecutivos no domínio
        if (domain.includes('..')) {
            return false;
        }
        
        // Verifica se o domínio tem pelo menos um ponto
        if (!domain.includes('.')) {
            return false;
        }
        
        // Verifica se o TLD tem pelo menos 2 caracteres (exceto para ccTLDs de 1 letra)
        const domainParts = domain.split('.');
        const tld = domainParts[domainParts.length - 1];
        if (tld.length < 2 && !/^[a-zA-Z]$/.test(tld)) {
            return false;
        }
        
        // Verifica se cada parte do domínio não começa ou termina com hífen
        for (const part of domainParts) {
            if (part.startsWith('-') || part.endsWith('-')) {
                return false;
            }
            if (part.length === 0) {
                return false;
            }
        }
        
        return true;
    };
    
    // Executa ambas as verificações
    const isValidPattern = pattern.test(email);
    const isValidAdditional = additionalChecks(email);
    const isValid = isValidPattern && isValidAdditional;
    
    return [isValid, pattern.toString()];
};