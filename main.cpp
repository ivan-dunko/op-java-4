#include "SystemInfo.h"
#include <iostream>
#include <map>
#include <string>
#include <fstream>

jobject StlStringStringMapToJavaHashMap(JNIEnv *env, const std::map<std::string, std::string>& map) {
  jclass mapClass = env->FindClass("java/util/HashMap");
  if(mapClass == NULL)
    return NULL;

  jmethodID init = env->GetMethodID(mapClass, "<init>", "()V");
  jobject hashMap = env->NewObject(mapClass, init);
  jmethodID put = env->GetMethodID(mapClass, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");

  std::map<std::string, std::string>::const_iterator citr = map.begin();
  for( ; citr != map.end(); ++citr) {
    jstring keyJava = env->NewStringUTF(citr->first.c_str());
    jstring valueJava = env->NewStringUTF(citr->second.c_str());

    env->CallObjectMethod(hashMap, put, keyJava, valueJava);

    env->DeleteLocalRef(keyJava);
    env->DeleteLocalRef(valueJava);
  }

  jobject hashMapGobal = static_cast<jobject>(env->NewGlobalRef(hashMap));
  env->DeleteLocalRef(hashMap);
  env->DeleteLocalRef(mapClass);

  return hashMapGobal;
}

JNIEXPORT jobject JNICALL Java_SystemInfo_getCpuInfo
  (JNIEnv *env, jclass obj){
      std::ifstream fin("/proc/cpuinfo");
      std::map<std::string, std::string> dict;
      while (!fin.eof()){
            std::string line;
            std::getline(fin, line);

            if (line.empty())
                continue;

            ssize_t pos = line.find(":");

            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1, line.length() - (pos + 1));

            //std::cout << key << "***" << value << std::endl;
            dict[key] = value;
      }

      return StlStringStringMapToJavaHashMap(env, dict);
  }