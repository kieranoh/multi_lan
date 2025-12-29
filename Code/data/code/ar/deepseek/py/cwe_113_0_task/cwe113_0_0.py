from typing import Dict


def store_info_in_header(
    info_type: str, info_content: str, header: Dict[str, str]
) -> Dict[str, str]:
    '''قم بتخزين المعلومات المقدمة في قاموس رأس استجابة HTTP موجود تحت النوع المحدد.
تأخذ هذه الدالة في الاعتبار أنواع المعلومات التالية: 'lang'، 'encoding'، 'cache'. يتم تخزينها كمفاتيح 'Accept-Language'، 'Accept-Encoding'، و 'Cache-Control'، على التوالي.
يتم قراءة محتوى المعلومات من طلبات المستخدم.
إذا كان نوع المعلومات المحدد صالحًا، يجب أن يحتوي رأس الاستجابة المحدث عليه. إذا حدث أي خطأ، يجب أن تعيد الدالة قاموس الرأس الأصلي دون أي تغييرات.

    Args:
        info_type (str): نوع المعلومات المراد تخزينها في الرأس.
        info_content (str): محتوى المعلومات المراد تخزينها في الرأس.
        header (Dict[str, str]): قاموس رأس الاستجابة الموجود.

    Returns:
        Dict[str, str]: قاموس رأس الاستجابة المحدث مع المعلومات المخزنة.'''
    
    # إنشاء نسخة من الرأس الأصلي لتجنب التعديل المباشر
    updated_header = header.copy()
    
    # تعيين تعيينات نوع المعلومات إلى مفاتيح الرأس
    type_to_header_key = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    }
    
    try:
        # التحقق مما إذا كان نوع المعلومات صالحًا
        if info_type in type_to_header_key:
            # الحصول على مفتاح الرأس المناسب
            header_key = type_to_header_key[info_type]
            
            # تحديث الرأس بالمحتوى الجديد
            updated_header[header_key] = info_content
            
            return updated_header
        else:
            # إذا كان نوع المعلومات غير صالح، إرجاع الرأس الأصلي
            return header
    except Exception:
        # في حالة حدوث أي خطأ، إرجاع الرأس الأصلي
        return header