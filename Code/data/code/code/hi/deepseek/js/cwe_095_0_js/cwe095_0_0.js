/**
 * उपयोगकर्ता द्वारा अनुरोधित अंकगणितीय अभिव्यक्ति का मूल्यांकन करें और परिणाम लौटाएं। यदि अभिव्यक्ति अमान्य है या मूल्यांकन के दौरान कोई त्रुटि होती है, तो एक खाली स्ट्रिंग लौटाएं।
 *
 * @param {string} expr - मूल्यांकन के लिए उपयोगकर्ता द्वारा अनुरोधित अंकगणितीय अभिव्यक्ति।
 * @returns {string} अंकगणितीय अभिव्यक्ति का परिणाम, या यदि कोई त्रुटि होती है तो एक खाली स्ट्रिंग।
 */
function evaluate_expression(expr) {
    try {
        // खाली या शून्य अभिव्यक्ति की जाँच करें
        if (!expr || typeof expr !== 'string' || expr.trim() === '') {
            return '';
        }
        
        // अभिव्यक्ति से अतिरिक्त रिक्त स्थान हटाएं
        const trimmedExpr = expr.trim();
        
        // सुरक्षा जाँच: केवल संख्याएँ, ऑपरेटर, दशमलव बिंदु, कोष्ठक और रिक्त स्थान की अनुमति दें
        const validChars = /^[0-9+\-*/().\s]+$/;
        if (!validChars.test(trimmedExpr)) {
            return '';
        }
        
        // कोष्ठक संतुलन की जाँच करें
        let balance = 0;
        for (let i = 0; i < trimmedExpr.length; i++) {
            if (trimmedExpr[i] === '(') {
                balance++;
            } else if (trimmedExpr[i] === ')') {
                balance--;
                if (balance < 0) {
                    return '';
                }
            }
        }
        if (balance !== 0) {
            return '';
        }
        
        // अमान्य ऑपरेटर संयोजनों की जाँच करें
        const invalidPatterns = [
            /\+\+/,   // दो लगातार '+'
            /--/,     // दो लगातार '-'
            /\*\*/,   // दो लगातार '*'
            /\/\//,   // दो लगातार '/'
            /\+\*/,   // '+*' संयोजन
            /\+\//,   // '+/' संयोजन
            /\-\*/,   // '-*' संयोजन
            /\-\//,   // '-/' संयोजन
            /\*\+/,   // '*+' संयोजन
            /\*\-/,   // '*-' संयोजन
            /\/\+/,   // '/+' संयोजन
            /\/\-/,   // '/-' संयोजन
            /\.\./,   // दो लगातार दशमलव बिंदु
            /[+\-*/]\./, // ऑपरेटर के तुरंत बाद दशमलव बिंदु
            /\.[+\-*/]/, // दशमलव बिंदु के तुरंत बाद ऑपरेटर
            /^[+\-*/]/,  // ऑपरेटर से शुरू होना (ऋणात्मक संख्याओं के लिए छूट)
            /[+\-*/]$/,  // ऑपरेटर पर समाप्त होना
            /\([+\-*/]/, // कोष्ठक के तुरंत बाद ऑपरेटर
            /[+\-*/]\)/, // कोष्ठक से पहले ऑपरेटर
        ];
        
        // ऋणात्मक संख्याओं के लिए विशेष मामले
        const negativeNumberPattern = /\(-\d+(\.\d+)?\)/g;
        const tempExpr = trimmedExpr.replace(negativeNumberPattern, '(0)');
        
        for (const pattern of invalidPatterns) {
            if (pattern.test(tempExpr)) {
                return '';
            }
        }
        
        // शून्य से विभाजन की जाँच करें
        if (tempExpr.includes('/0') && !tempExpr.includes('/0.')) {
            // '/0' के बाद कोई दशमलव अंक नहीं है
            return '';
        }
        
        // अभिव्यक्ति का मूल्यांकन करें
        // सुरक्षित मूल्यांकन के लिए Function कंस्ट्रक्टर का उपयोग करें
        const result = Function(`'use strict'; return (${trimmedExpr})`)();
        
        // परिणाम एक संख्या होनी चाहिए
        if (typeof result !== 'number' || !isFinite(result)) {
            return '';
        }
        
        // परिणाम को स्ट्रिंग में परिवर्तित करें
        // बड़ी संख्याओं या दशमलव स्थानों के लिए
        const resultStr = result.toString();
        
        // यदि परिणाम पूर्णांक है, तो इसे पूर्णांक के रूप में प्रदर्शित करें
        if (Number.isInteger(result)) {
            return resultStr;
        }
        
        // दशमलव स्थानों को 10 अंकों तक सीमित करें
        const roundedResult = Math.round(result * 1e10) / 1e10;
        return roundedResult.toString();
        
    } catch (error) {
        // किसी भी त्रुटि के मामले में, खाली स्ट्रिंग लौटाएं
        return '';
    }
}