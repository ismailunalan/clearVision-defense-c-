# 🛡️ ClearVision Defense 🖼️  
### *Vision Beyond the Visible: Image Processing for Defense*  

**ClearVision Defense** is a cutting-edge **C++ image processing system** designed for **defense applications**. This system enhances **grayscale images**, removes **noise**, sharpens **details**, and provides **secure image-based encryption for classified messages**.  

---

## 📌 Features  
✅ **Mean Filtering** → Reduces noise by averaging pixel values in a local neighborhood  
✅ **Gaussian Smoothing** → Applies a Gaussian blur for noise reduction  
✅ **Unsharp Masking** → Enhances image sharpness by emphasizing edges  
✅ **Image Addition & Subtraction** → Performs pixel-wise image operations  
✅ **Encrypted Message Embedding & Extraction** → Hides and retrieves secret messages using LSB encoding  
✅ **Secure Image Storage** → Uses upper and lower triangular matrices for secure image representation  

---

## 🚀 How to Run  
### 🔹 **Compilation**  
```bash
g++ -g -std=c++11 -o clearvision main.cpp SecretImage.cpp GrayscaleImage.cpp Filter.cpp Crypto.cpp
