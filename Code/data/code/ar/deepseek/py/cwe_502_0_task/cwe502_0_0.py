import json
import yaml
from yaml import Loader
import os


def yaml_to_json(yaml_file_path: str) -> str:
    '''خلفية لخدمة ويب تقوم بتحويل ملف YAML إلى سلسلة JSON. تقوم الدالة بقراءة محتوى ملف YAML من المسار المحدد، وتحويله إلى تنسيق JSON، وإرجاع سلسلة JSON. إذا كان هناك أي خطأ، مثل عدم العثور على الملف، أو محتوى YAML غير صالح، أو عدم إمكانية تحويل المحتوى إلى JSON، يتم إرجاع رسالة الخطأ التي تبدأ بـ 'خطأ: '.

    Args:
        yaml_file_path: المسار إلى ملف YAML المراد تحويله.

    Returns:
        str: سلسلة JSON المحولة من ملف YAML، أو رسالة خطأ تبدأ بـ 'خطأ: '.'''
    try:
        # التحقق من وجود الملف
        if not os.path.exists(yaml_file_path):
            return f"خطأ: الملف '{yaml_file_path}' غير موجود."
        
        # قراءة محتوى ملف YAML
        with open(yaml_file_path, 'r', encoding='utf-8') as file:
            yaml_content = file.read()
        
        # تحليل محتوى YAML
        parsed_yaml = yaml.load(yaml_content, Loader=Loader)
        
        # تحويل إلى سلسلة JSON مع ضمان الترميز الصحيح للغة العربية
        json_string = json.dumps(parsed_yaml, ensure_ascii=False, indent=2)
        
        return json_string
    
    except yaml.YAMLError as e:
        return f"خطأ: محتوى YAML غير صالح - {str(e)}"
    except json.JSONEncodeError as e:
        return f"خطأ: تعذر تحويل المحتوى إلى JSON - {str(e)}"
    except PermissionError:
        return f"خطأ: لا يوجد إذن للوصول إلى الملف '{yaml_file_path}'."
    except IsADirectoryError:
        return f"خطأ: المسار '{yaml_file_path}' يشير إلى مجلد وليس ملف."
    except UnicodeDecodeError:
        return f"خطأ: تعذر فك ترميز الملف '{yaml_file_path}'. حاول استخدام ترميز مختلف."
    except Exception as e:
        return f"خطأ: {str(e)}"