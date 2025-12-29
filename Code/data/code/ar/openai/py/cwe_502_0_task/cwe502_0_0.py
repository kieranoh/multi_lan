import json
import yaml
from yaml import Loader

def yaml_to_json(yaml_file_path: str) -> str:
    '''خلفية لخدمة ويب تقوم بتحويل ملف YAML إلى سلسلة JSON. تقوم الدالة بقراءة محتوى ملف YAML من المسار المحدد، وتحويله إلى تنسيق JSON، وإرجاع سلسلة JSON. إذا كان هناك أي خطأ، مثل عدم العثور على الملف، أو محتوى YAML غير صالح، أو عدم إمكانية تحويل المحتوى إلى JSON، يتم إرجاع رسالة الخطأ التي تبدأ بـ 'خطأ: '.

    Args:
        yaml_file_path: المسار إلى ملف YAML المراد تحويله.

    Returns:
        str: سلسلة JSON المحولة من ملف YAML، أو رسالة خطأ تبدأ بـ 'خطأ: '.'''
    try:
        with open(yaml_file_path, 'r', encoding='utf-8') as yaml_file:
            yaml_content = yaml.load(yaml_file, Loader=Loader)
            json_content = json.dumps(yaml_content, ensure_ascii=False)
            return json_content
    except FileNotFoundError:
        return 'خطأ: لم يتم العثور على الملف.'
    except yaml.YAMLError:
        return 'خطأ: محتوى YAML غير صالح.'
    except Exception as e:
        return f'خطأ: {str(e)}'