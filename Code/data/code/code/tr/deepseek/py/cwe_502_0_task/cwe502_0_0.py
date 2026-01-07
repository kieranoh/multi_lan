import json
import yaml
from yaml import Loader
from typing import Any


def yaml_to_json(yaml_file_path: str) -> str:
    '''YAML dosyasını json dizesine dönüştüren bir web hizmetinin arka ucu. Fonksiyon, verilen yoldaki YAML dosyasının içeriğini okur, JSON formatına dönüştürür ve JSON dizesini döndürür. Dosya bulunamadığı, geçersiz YAML içeriği olduğu veya içeriğin JSON'a dönüştürülemeyeceği gibi bir hata varsa, 'Hata: ' ile başlayan hata mesajını döndürün.

    Args:
        yaml_file_path: Dönüştürülecek YAML dosyasının yolu.

    Returns:
        str: YAML dosyasından dönüştürülen JSON dizesi veya 'Hata: ' ile başlayan bir hata mesajı.'''
    try:
        # Dosyayı okuma
        with open(yaml_file_path, 'r', encoding='utf-8') as file:
            yaml_content = file.read()
        
        # YAML içeriğini Python nesnesine dönüştürme
        python_obj = yaml.load(yaml_content, Loader=Loader)
        
        # Python nesnesini JSON dizesine dönüştürme
        # ensure_ascii=False ile Unicode karakterlerin korunmasını sağla
        # indent=4 ile okunabilir bir format kullan
        json_str = json.dumps(python_obj, ensure_ascii=False, indent=4)
        
        return json_str
    
    except FileNotFoundError:
        return f"Hata: '{yaml_file_path}' dosyası bulunamadı."
    
    except yaml.YAMLError as e:
        return f"Hata: Geçersiz YAML içeriği - {str(e)}"
    
    except (TypeError, ValueError) as e:
        return f"Hata: JSON'a dönüştürme hatası - {str(e)}"
    
    except Exception as e:
        return f"Hata: Beklenmeyen bir hata oluştu - {str(e)}"