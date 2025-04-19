#include <jni.h>
#include <string>
#include <android/log.h>
#include <vector>

const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

#define LOG_TAG "NativeBase64"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
// Base64 编码函数
std::string base64_encode(const unsigned char* bytes_to_encode, unsigned int in_len) {
    std::string ret;
    int i = 0;
    int val = 0;
    int valb = -6;

    for (unsigned int j = 0; j < in_len; j++) {
        val = (val << 8) + bytes_to_encode[j];
        valb += 8;

        while (valb >= 0) {
            ret.push_back(base64_chars[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }

    if (valb > -6) {
        ret.push_back(base64_chars[((val << 8) >> (valb + 8)) & 0x3F]);
    }

    while (ret.size() % 4) {
        ret.push_back('=');
    }

    return ret;
      // 打印 std::string 内容


}


// Base64 解码函数
std::string base64_decode(const std::string& encoded_string) {
    std::vector<int> T(256, -1);
    for (int i = 0; i < 64; i++) {
        T[base64_chars[i]] = i;
    }

    std::string ret;
    int val = 0;
    int valb = -8;

    for (unsigned int i = 0; i < encoded_string.size(); i++) {
        char c = encoded_string[i];
        if (T[c] == -1) {
            break;
            return "false";// 遇到 -1，跳出循环
        }

        val = (val << 6) + T[c];
        valb += 6;

        if (valb >= 0) {
            ret.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    LOGI("解码后的字符串: %s", ret.c_str());
    return ret;

}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_base64_MainActivity_base64Decode(JNIEnv *env, jobject /* this */, jstring input) {
    const char *inputStr = env->GetStringUTFChars(input, 0);
    std::string decoded = base64_decode(inputStr);
    env->ReleaseStringUTFChars(input, inputStr);

    return env->NewStringUTF(decoded.c_str());
}



extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_base64_MainActivity_base64Encode(JNIEnv *env, jobject /* this */, jstring input) {
    const char *inputStr = env->GetStringUTFChars(input, 0);
    std::string encoded = base64_encode(reinterpret_cast<const unsigned char*>(inputStr), strlen(inputStr));
    env->ReleaseStringUTFChars(input, inputStr);
    return env->NewStringUTF(encoded.c_str());
}