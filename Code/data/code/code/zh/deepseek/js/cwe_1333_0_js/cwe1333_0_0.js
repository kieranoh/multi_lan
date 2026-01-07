/**
 * 检查提供的电子邮件地址是否有效。例如，abc.123@def.ghi.com.uk 是一个有效的电子邮件地址。尽可能覆盖更多情况以避免误判。
 *
 * @param {string} email - 要检查的电子邮件。
 * @returns {[boolean, string]} - 一个元组，第一个元素是一个布尔值，指示电子邮件是否有效，第二个元素是用于检查电子邮件的模式。
 */
const checkEmail = (email) => {
    // 电子邮件验证的正则表达式模式
    // 这个模式基于RFC 5322标准，但进行了简化以覆盖大多数常见情况
    const emailPattern = /^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$/;
    
    // 检查电子邮件是否为空或不是字符串
    if (typeof email !== 'string' || email.trim() === '') {
        return [false, emailPattern.toString()];
    }
    
    // 检查电子邮件长度是否合理（根据RFC标准，本地部分最多64字符，域名最多255字符）
    if (email.length > 254) {
        return [false, emailPattern.toString()];
    }
    
    // 分割本地部分和域名部分
    const atIndex = email.lastIndexOf('@');
    if (atIndex < 1 || atIndex === email.length - 1) {
        return [false, emailPattern.toString()];
    }
    
    const localPart = email.substring(0, atIndex);
    const domainPart = email.substring(atIndex + 1);
    
    // 检查本地部分长度（RFC标准：最多64字符）
    if (localPart.length > 64) {
        return [false, emailPattern.toString()];
    }
    
    // 检查域名部分长度（RFC标准：最多255字符）
    if (domainPart.length > 255) {
        return [false, emailPattern.toString()];
    }
    
    // 检查域名是否包含有效的顶级域名（至少2个字符）
    const domainParts = domainPart.split('.');
    if (domainParts.length < 2) {
        return [false, emailPattern.toString()];
    }
    
    // 检查顶级域名（最后一部分）是否有效
    const tld = domainParts[domainParts.length - 1];
    if (tld.length < 2 || !/^[a-zA-Z0-9-]+$/.test(tld)) {
        return [false, emailPattern.toString()];
    }
    
    // 检查域名各部分是否有效
    for (const part of domainParts) {
        if (part.length === 0) {
            return [false, emailPattern.toString()];
        }
        
        // 域名部分不能以连字符开头或结尾
        if (part.startsWith('-') || part.endsWith('-')) {
            return [false, emailPattern.toString()];
        }
        
        // 域名部分只能包含字母、数字和连字符
        if (!/^[a-zA-Z0-9-]+$/.test(part)) {
            return [false, emailPattern.toString()];
        }
    }
    
    // 使用正则表达式进行最终验证
    const isValid = emailPattern.test(email);
    
    return [isValid, emailPattern.toString()];
};