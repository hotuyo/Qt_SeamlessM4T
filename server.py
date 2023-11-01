from flask import Flask, request
import torch
from seamless_communication.models.inference import Translator
app = Flask(__name__)
app.config['JSON_AS_ASCII'] = True
translator = Translator("seamlessM4T_large", "vocoder_36langs", torch.device("cuda"), torch.float16)
@app.route('/translate', methods=['POST'])
def testpost():
    if request.method == 'POST':
        input_text = request.json.get('text', '')
        translate_option = request.json.get('type', '')
        target_language = request.json.get('target', '')
        src_language = request.json.get('src', '')
        translated_text, _, _ = translator.predict(input_text, translate_option, target_language, src_lang=src_language)
        print(str(translated_text))
        return str(translated_text)
if __name__ == '__main__':
    app.run(host= '192.168.1.6', port=9979, threaded=True)