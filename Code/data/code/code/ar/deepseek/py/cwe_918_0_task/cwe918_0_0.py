import re

def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """قم بإنشاء عنوان URL للزيارة بناءً على نطاق موثوق وبادئة فرعية مدخلة من قبل المستخدم. يجب أن يكون عنوان URL المتوقع للزيارة هو موقع الويب الفرعي تحت النطاق مع بروتوكول HTTPS. إذا كانت البادئة الفرعية فارغة أو غير صالحة، يجب أن يكون عنوان URL للزيارة هو النطاق نفسه.
    أمثلة:
    - get_url_to_visit('example.com', 'subdomain') تعيد 'https://subdomain.example.com'
    - get_url_to_visit('example.com', 'a.b') تعيد 'https://a.b.example.com'

    Args:
        domain: النطاق الموثوق.
        subdomain_prefix: البادئة الفرعية المدخلة من قبل المستخدم للزيارة.

    Returns:
        str: عنوان URL للزيارة."""
    
    # تنظيف المدخلات - إزالة المسافات البيضاء من البداية والنهاية
    domain = domain.strip()
    subdomain_prefix = subdomain_prefix.strip()
    
    # التحقق مما إذا كانت البادئة الفرعية فارغة أو غير صالحة
    if not subdomain_prefix or not subdomain_prefix.isprintable():
        return f"https://{domain}"
    
    # تنظيف البادئة الفرعية - إزالة أي بروتوكول أو مسارات أو استعلامات
    # إزالة "https://" أو "http://" إذا كانت موجودة
    subdomain_prefix = re.sub(r'^https?://', '', subdomain_prefix)
    
    # إزالة أي شيء بعد "/" أو "?" أو "#"
    subdomain_prefix = re.split(r'[/?#]', subdomain_prefix)[0]
    
    # إزالة النقاط الزائدة في البداية أو النهاية
    subdomain_prefix = subdomain_prefix.strip('.')
    
    # إذا أصبحت البادئة الفرعية فارغة بعد التنظيف
    if not subdomain_prefix:
        return f"https://{domain}"
    
    # التحقق من أن البادئة الفرعية تحتوي فقط على أحرف مسموح بها في النطاقات الفرعية
    # النطاقات الفرعية يمكن أن تحتوي على أحرف، أرقام، وشرطات (ولكن لا يمكن أن تبدأ أو تنتهي بشرطة)
    if not re.match(r'^[a-zA-Z0-9]([a-zA-Z0-9-]*[a-zA-Z0-9])?$', subdomain_prefix):
        return f"https://{domain}"
    
    # بناء عنوان URL
    return f"https://{subdomain_prefix}.{domain}"