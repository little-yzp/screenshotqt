from paddleocr import PaddleOCR

# 初始化模型（默认启用中英文识别）
ocr = PaddleOCR(use_angle_cls=True, lang='ch')

def extract_ocr_text(result):
    texts = []
    for item in result:
        if isinstance(item, list):
            texts.extend(extract_ocr_text(item))
        # 如果当前元素是包含文字信息的元组（文本，置信度）
        elif isinstance(item, tuple) and len(item) >= 2:
            if isinstance(item[0], str):  # 确保第一个元素是文本
                texts.append(item[0])
        elif isinstance(item, list) and len(item) >= 2:
            if isinstance(item[1], tuple):
                texts.append(item[1][0])
    return texts

# OCR识别
result = ocr.ocr('test.png', cls=True)

# 提取并打印所有文本
all_texts = extract_ocr_text(result)
for text in all_texts:
    print(text)