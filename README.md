# Qt and SeamlessM4T

Use the flask framework to enable the SeamlessM4T large model on the server.

```python
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
  	#服务端口监听本机IP 地址和端口
    app.run(host= '192.168.1.6', port=9979, threaded=True)
```

