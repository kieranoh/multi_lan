/**
 * Verifica si la dirección de correo electrónico proporcionada es válida. Por ejemplo, abc.123@def.ghi.com.uk es una dirección de correo electrónico válida. Cubre tantos casos como sea posible para evitar falsos negativos.
 *
 * @param {string} email - El correo electrónico a verificar.
 * @returns {[boolean, string]} - Una tupla con el primer elemento siendo un booleano que indica si el correo electrónico es válido y el segundo elemento siendo el patrón utilizado para verificar el correo electrónico.
 */
const checkEmail = (email) => {
    // Patrón de validación de correo electrónico basado en RFC 5322 con algunas adaptaciones prácticas
    // Este patrón intenta cubrir la mayoría de los casos válidos mientras evita falsos negativos
    const emailPattern = /^(?=.{1,254}$)(?=.{1,64}@)[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?\.)+[a-zA-Z]{2,}$/;
    
    // Patrón alternativo más estricto para verificación adicional de dominio
    const strictDomainPattern = /^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?\.)+[a-zA-Z0-9-]{2,}$/;
    
    // Verificar longitud total máxima (254 caracteres según RFC 5321)
    if (email.length > 254) {
        return [false, "RFC_5321_MAX_LENGTH"];
    }
    
    // Verificar que tenga exactamente un símbolo @
    const atCount = (email.match(/@/g) || []).length;
    if (atCount !== 1) {
        return [false, "INVALID_AT_COUNT"];
    }
    
    // Dividir en parte local y dominio
    const parts = email.split('@');
    const localPart = parts[0];
    const domainPart = parts[1];
    
    // Verificar longitud de la parte local (máximo 64 caracteres según RFC 5321)
    if (localPart.length > 64 || localPart.length === 0) {
        return [false, "INVALID_LOCAL_PART_LENGTH"];
    }
    
    // Verificar que la parte local no comience o termine con punto
    if (localPart.startsWith('.') || localPart.endsWith('.')) {
        return [false, "INVALID_LOCAL_PART_DOTS"];
    }
    
    // Verificar que no haya puntos consecutivos en la parte local
    if (localPart.includes('..')) {
        return [false, "CONSECUTIVE_DOTS_LOCAL"];
    }
    
    // Verificar dominio
    if (domainPart.length === 0) {
        return [false, "EMPTY_DOMAIN"];
    }
    
    // Verificar que el dominio no comience o termine con guión o punto
    if (domainPart.startsWith('-') || domainPart.endsWith('-') || 
        domainPart.startsWith('.') || domainPart.endsWith('.')) {
        return [false, "INVALID_DOMAIN_EDGES"];
    }
    
    // Verificar que no haya puntos consecutivos en el dominio
    if (domainPart.includes('..')) {
        return [false, "CONSECUTIVE_DOTS_DOMAIN"];
    }
    
    // Verificar que cada etiqueta del dominio tenga entre 1 y 63 caracteres
    const domainLabels = domainPart.split('.');
    for (const label of domainLabels) {
        if (label.length === 0 || label.length > 63) {
            return [false, "INVALID_DOMAIN_LABEL_LENGTH"];
        }
        
        // Verificar que las etiquetas del dominio solo contengan caracteres válidos
        if (!/^[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$/.test(label)) {
            return [false, "INVALID_DOMAIN_LABEL_CHARS"];
        }
    }
    
    // Verificar que el TLD tenga al menos 2 caracteres (con excepciones para ccTLD de un carácter)
    const tld = domainLabels[domainLabels.length - 1];
    if (tld.length < 2 && !/^[a-zA-Z]$/.test(tld)) {
        // Algunos ccTLD tienen un solo carácter (ej: .ai, .us, etc.), pero en general se requiere al menos 2
        // Para ser conservador, requerimos al menos 2 caracteres para el TLD
        return [false, "INVALID_TLD_LENGTH"];
    }
    
    // Aplicar el patrón principal de validación
    if (emailPattern.test(email)) {
        return [true, "RFC_5322_COMPLIANT"];
    }
    
    // Intentar con patrón más permisivo si el primero falla
    const permissivePattern = /^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$/;
    
    if (permissivePattern.test(email)) {
        return [true, "PERMISSIVE_VALIDATION"];
    }
    
    // Si todo falla, intentar una validación básica
    const basicPattern = /^[^@\s]+@[^@\s]+\.[^@\s]+$/;
    if (basicPattern.test(email) && email.length <= 254) {
        return [true, "BASIC_VALIDATION"];
    }
    
    return [false, "INVALID_EMAIL_FORMAT"];
};