import re
import operator

def evaluate_expression(expr: str) -> str:
    '''Kullanıcı tarafından istenen aritmetik ifadenin değerlendirilmesini yapın ve sonucu döndürün. Eğer ifade geçersizse veya değerlendirme sırasında herhangi bir hata oluşursa, boş bir dize döndürün.

    Args:
        expr (str): Değerlendirilecek kullanıcı tarafından istenen aritmetik ifade.

    Returns:
        str: Aritmetik ifadenin sonucu veya herhangi bir hata oluşursa boş bir dize.'''
    
    # İfade boşsa veya sadece boşluklardan oluşuyorsa boş dize döndür
    if not expr or expr.isspace():
        return ""
    
    # Güvenlik için: Sadece rakamlar, operatörler, parantezler ve boşlükler içermeli
    allowed_chars = set("0123456789+-*/(). ")
    if not set(expr).issubset(allowed_chars):
        return ""
    
    # Güvenlik için: Ardışık operatörleri kontrol et (örneğin "++", "+-", "*/" gibi)
    # Ancak "+-" gibi ifadeler geçerli olabilir (örneğin "3+-2" geçerli değil ama "3+(-2)" geçerli)
    # Basit bir kontrol: İki ardışık operatör (boşluk olmadan) varsa geçersiz
    operator_pattern = r'[+\-*/]{2,}'
    if re.search(operator_pattern, expr.replace(' ', '')):
        return ""
    
    # Parantezlerin dengeli olup olmadığını kontrol et
    stack = []
    for char in expr:
        if char == '(':
            stack.append(char)
        elif char == ')':
            if not stack:
                return ""  # Fazla kapatma parantezi
            stack.pop()
    if stack:
        return ""  # Fazla açma parantezi
    
    try:
        # İfadeyi güvenli bir şekilde değerlendir
        # Önce boşlukları temizle
        expr_clean = expr.replace(' ', '')
        
        # Negatif sayıları doğru şekilde işlemek için
        # "-" işaretini sayıların önünde olduğunda koru
        # Örneğin: "3-2" -> "3-2", "3+-2" -> "3+(-2)" değil, bu zaten filtrelendi
        
        # eval kullanmadan önce daha fazla güvenlik kontrolü
        # Sadece sayılar, operatörler ve parantezler kalmalı
        safe_expr = expr_clean
        safe_pattern = r'^[\d+\-*/().]+$'
        if not re.match(safe_pattern, safe_expr):
            return ""
        
        # Python'un eval fonksiyonunu kullanarak ifadeyi değerlendir
        # Güvenlik için: locals ve globals boş sözlükler
        result = eval(safe_expr, {"__builtins__": {}}, {})
        
        # Sonucu string'e çevir
        # Eğer sonuç tam sayı ise ondalık kısmı gösterme
        if isinstance(result, int):
            return str(result)
        elif isinstance(result, float):
            # Ondalık kısmı sıfırsa tam sayı olarak göster
            if result.is_integer():
                return str(int(result))
            # Ondalık sayıları makul bir hassasiyetle göster
            # Çok küçük sayıları bilimsel gösterimden kaçın
            return format(result, '.10g').rstrip('0').rstrip('.')
        else:
            return ""
            
    except ZeroDivisionError:
        # Sıfıra bölme hatası
        return ""
    except (SyntaxError, NameError, TypeError, ValueError, MemoryError):
        # Diğer olası hatalar
        return ""
    except Exception:
        # Diğer tüm hatalar
        return ""