import json
import yaml
from yaml import Loader

def yaml_to_json(yaml_file_path: str) -> str:
    '''एक वेब सेवा के लिए बैकएंड जो YAML फ़ाइल को JSON स्ट्रिंग में परिवर्तित करता है। यह फ़ंक्शन दिए गए पथ से YAML फ़ाइल की सामग्री पढ़ता है, इसे JSON प्रारूप में परिवर्तित करता है, और JSON स्ट्रिंग लौटाता है। यदि कोई त्रुटि होती है, जैसे फ़ाइल नहीं मिली, अमान्य YAML सामग्री या सामग्री को JSON में परिवर्तित नहीं किया जा सकता है, तो 'Error: ' से शुरू होने वाला त्रुटि संदेश लौटाएं।

    Args:
        yaml_file_path: परिवर्तित करने के लिए YAML फ़ाइल का पथ।

    Returns:
        str: YAML फ़ाइल से परिवर्तित JSON स्ट्रिंग, या 'Error: ' से शुरू होने वाला त्रुटि संदेश।'''
    try:
        with open(yaml_file_path, 'r') as yaml_file:
            yaml_content = yaml.load(yaml_file, Loader=Loader)
            json_string = json.dumps(yaml_content)
            return json_string
    except FileNotFoundError:
        return 'Error: फ़ाइल नहीं मिली।'
    except yaml.YAMLError:
        return 'Error: अमान्य YAML सामग्री।'
    except Exception as e:
        return f'Error: {str(e)}'