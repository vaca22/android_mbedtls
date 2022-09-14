#include <jni.h>
#include <string>
#include <android/log.h>

#include "mbedtls/aes.h"


#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "threaded_app", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "threaded_app", __VA_ARGS__))

#define INPUT_LENGTH 16

mbedtls_aes_context aes;
mbedtls_aes_context aes2;


unsigned char key[] = {0xff, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0xff, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

unsigned char input[INPUT_LENGTH] = {1};

static void cbc()
{

    mbedtls_aes_init(&aes);
    mbedtls_aes_init(&aes2);
    mbedtls_aes_setkey_enc(&aes, key, 256);
    mbedtls_aes_setkey_dec(&aes2, key, 256);

    for(int k=0;k<16;k++){
        input[k]=k;
    }

    unsigned char iv[] = {0xff, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
    unsigned char iv1[] = {0xff, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
    unsigned char encrypt_output[INPUT_LENGTH] = {0};
    unsigned char decrypt_output[INPUT_LENGTH] = {0};
    mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, INPUT_LENGTH, iv, input, encrypt_output);



    mbedtls_aes_crypt_cbc(&aes2, MBEDTLS_AES_DECRYPT, INPUT_LENGTH, iv1, encrypt_output, decrypt_output);

    for(int k=0;k<16;k++){
        LOGI( "%d", decrypt_output[k]);
    }


}





extern "C" JNIEXPORT jstring JNICALL
Java_com_vaca_myapplication_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {



    LOGE("FUCK");

    cbc();
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}