#ifndef __ANDROID_JNI_HELPER_H__
#define __ANDROID_JNI_HELPER_H__

#include <jni.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include<cstdlib>
#include <stdio.h>
#include <string.h>
#include<iostream>
#include "Exceptions.hpp"
//#include "platform/CCPlatformMacros.h"
//#include "math/Vec3.h"

//NS_CC_BEGIN

using namespace std;

typedef struct JniMethodInfo_
{
    JNIEnv *    env;
    jclass      classID;
    jmethodID   methodID;
} JniMethodInfo;

class  JniHelper
{
public:
    typedef std::unordered_map<JNIEnv*, std::vector<jobject>> LocalRefMapType;

    static void setJavaVM(JavaVM *javaVM);
    static JavaVM* getJavaVM();
    static JNIEnv* getEnv();
    static jobject getActivity();

    static bool setClassLoaderFrom(jobject activityInstance);
    static bool getStaticMethodInfo(JniMethodInfo &methodinfo,
                                    const char *className,
                                    const char *methodName,
                                    const char *paramCode);
    static bool getMethodInfo(JniMethodInfo &methodinfo,
                              const char *className,
                              const char *methodName,
                              const char *paramCode);

    static std::string jstring2string(jstring str);

    static jmethodID loadclassMethod_methodID;
    static jobject classloader;
    static std::function<void()> classloaderCallback;

    template <typename... Ts>
    static void callVoidMethod(jobject& obj, const std::string& className,
                               const std::string& methodName,
                               Ts... xs)
    {
        JniMethodInfo t;
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")V";
        if (JniHelper::getMethodInfo_DefaultClassLoader(t, className.c_str(), methodName.c_str(), signature.c_str()))
        {

            LocalRefMapType localRefs;

            t.env->CallVoidMethod(obj, t.methodID, convert(localRefs, t, xs)...);

            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env, localRefs);
        }
        else
        {
            reportError(className, methodName, signature);
        }
    }
    template <typename... Ts>
    static void callVoidMethod(const std::string& signature, jobject& obj, const std::string& className,
                               const std::string& methodName,
                               Ts... xs)
    {
        JniMethodInfo t;

        //std::string signature = "(" + std::string(getJNISignature(xs...)) + ")V";
        if (JniHelper::getMethodInfo_DefaultClassLoader(t, className.c_str(), methodName.c_str(), signature.c_str()))
        {
            LocalRefMapType localRefs;

            t.env->CallVoidMethod(obj, t.methodID, convert(localRefs, t, xs)...);

            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env, localRefs);
        }
        else
        {
            reportError(className, methodName, signature);
        }

    }

    template <typename... Ts>
    static jobject callObjectMethod(jobject& obj, const std::string& className,
                                    const std::string& methodName, const std::string& returnClassName,
                                    Ts... xs)
    {
        jobject res;
        JniMethodInfo t;
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")L" + returnClassName +";";
        if (JniHelper::getMethodInfo_DefaultClassLoader(t, className.c_str(), methodName.c_str(), signature.c_str()))
        {
            LocalRefMapType localRefs;
            res =  t.env->CallObjectMethod(obj,  t.methodID,  convert(localRefs, t, xs)...);
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env, localRefs);
        }
        else
        {
            reportError(className, methodName, signature);
            return NULL;
        }

        return res;
    }
    template <typename... Ts>
    static jobject createObjectMethod(const std::string& className, Ts... xs)
    {
        jobject res;
        JniMethodInfo t;
        std::string methodName = "<init>";
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")V";

        if (JniHelper::getMethodInfo_DefaultClassLoader(t, className.c_str(), methodName.c_str(), signature.c_str()))
        {

            LocalRefMapType localRefs;
            res = t.env->NewObject(t.classID, t.methodID,convert(localRefs, t, xs)...);
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env, localRefs);
        }
        else
        {
            reportError(className, methodName, signature);
            return 0;
        }
        return res;
    }

    template <typename... Ts>
    static bool callBooleanMethod(jobject obj, const std::string& className,
                                  const std::string& methodName,
                                  Ts... xs)
    {
        jboolean jret = JNI_FALSE;
        JniMethodInfo t;
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")Z";
        if (JniHelper::getMethodInfo_DefaultClassLoader(t, className.c_str(), methodName.c_str(), signature.c_str()))
        {
            LocalRefMapType localRefs;
            jret = t.env->CallBooleanMethod(obj, t.methodID, convert(localRefs, t, xs)...);
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env, localRefs);
        }
        else
        {
            reportError(className, methodName, signature);
        }
        return (jret == JNI_TRUE);
    }

    template <typename... Ts>
    static int callIntMethod(const std::string& signature, jobject obj, const std::string& className, const std::string& methodName, Ts... xs)
    {

        jint jret;
        JniMethodInfo t;
        //std::string signature = "(" + std::string(getJNISignature(xs...)) + ")Z";
        if (JniHelper::getMethodInfo_DefaultClassLoader(t, className.c_str(), methodName.c_str(), signature.c_str()))
        {
            LocalRefMapType localRefs;
            jret = t.env->CallIntMethod(obj, t.methodID, convert(localRefs, t, xs)...);
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env, localRefs);
        }
        else
        {
            reportError(className, methodName, signature);
        }
        return (int)jret;

    }

    template <typename... Ts>
    static jobject callStaticObjectMethod(const std::string& className,
                                          const std::string& methodName, const std::string& returnClassName,
                                          Ts... xs)
    {

        jobject ret;
        JniMethodInfo t;
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")L" + returnClassName +";";

        if (JniHelper::getStaticMethodInfo(t, className.c_str(), methodName.c_str(), signature.c_str()))
        {

            LocalRefMapType localRefs;
            ret = t.env->CallStaticObjectMethod(t.classID, t.methodID, convert(localRefs, t, xs)...);
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env, localRefs);
        }
        else
        {
            reportError(className, methodName, signature);
        }
        return ret;
    }

    template <typename... Ts>
    static std::string callStringMethod(jobject obj, const std::string& className,
                                        const std::string& methodName,
                                        Ts... xs)
    {
        std::string ret;
        JniMethodInfo t;
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")Ljava/lang/String;";
        if (JniHelper::getMethodInfo_DefaultClassLoader(t, className.c_str(), methodName.c_str(), signature.c_str()))
        {
            LocalRefMapType localRefs;
            jstring jret = (jstring)t.env->CallObjectMethod(obj, t.methodID, convert(localRefs, t, xs)...);
            ret =JniHelper::jstring2string(jret);
            t.env->DeleteLocalRef(t.classID);
            t.env->DeleteLocalRef(jret);
            deleteLocalRefs(t.env, localRefs);
        }
        else
        {
            reportError(className, methodName, signature);
        }
        return ret;
    }

    static jboolean ToJBool(bool value)
    {
        return value ? JNI_TRUE : JNI_FALSE;
    }

    static std::string getObjectClassName(jobject obj)
    {
        jobject classObj = JniHelper::callObjectMethod(obj, "java/lang/Object", "getClass", "java/lang/Class");
        std::string  className = JniHelper::callStringMethod(classObj, "java/lang/Class", "getName");
        return className;
    }

    static void checkException(JNIEnv* env)
    {
        jthrowable exc = env->ExceptionOccurred();
        jboolean error = env->ExceptionCheck();
        if(error)
        {
            //异常处理
            jclass newExcCls =env->GetObjectClass(exc);
            //class.getclass().getname();
            //输出异常
            jobject testt = (jobject)exc;
            env->ExceptionDescribe();
            //清除异常
            env->ExceptionClear();
            // env->ThrowNew(newExcCls, "thrown from C code");
        }


    }
    static void deleteLocalRefs(JNIEnv* env, LocalRefMapType& localRefs);



static JavaException getExceptionFromName(const std::string& exceptionName) {
        if(exceptionName.compare("alluxio.exception.AlluxIOException")==0) {
            return  AlluxioException();
        } else if (exceptionName.compare("alluxio.exception.IOException")==0) {
                    return  IOException();
        } else if(exceptionName.compare("alluxio.exception.InvalidPathException")==0) {
            return InvalidPathException();
        }  else if(exceptionName.compare("alluxio.exception.FileAlreadyExistsException")==0) {
            return FileAlreadyExistsException();
        } else if(exceptionName.compare("alluxio.exception.FileDoesNotExistException")==0) {
            return  FileDoesNotExistException();
        }
        else {
            return JavaException();
        }

};

 static void exceptionCheck(JNIEnv *env) {

 jthrowable exc;
    exc = env->ExceptionOccurred();
    jboolean error = env->ExceptionCheck();
    if(error)
    {
        //异常处理
        //输出异常
        env->ExceptionDescribe();
        //清除异常
        env->ExceptionClear();
        std::string exceptionName =  JniHelper::getObjectClassName((jobject)exc);
        JavaException e = getExceptionFromName(exceptionName);
        throw e;
       // env->ThrowNew(newExcCls, "thrown from C code");
    }
}




private:
    static jstring  string2jstring(JNIEnv* env,const char* pat);
    //static std::string jstring2string(jstring jstr);
    static JNIEnv* cacheEnv(JavaVM* jvm);

    static bool getMethodInfo_DefaultClassLoader(JniMethodInfo &methodinfo,
            const char *className,
            const char *methodName,
            const char *paramCode);


    static JavaVM* _psJavaVM;

    static jobject _activity;

    static jstring convert(LocalRefMapType& localRefs, JniMethodInfo& t, const char* x);

    static jstring convert(LocalRefMapType& localRefs, JniMethodInfo& t, const std::string& x);

    template <typename T>
    static T convert(LocalRefMapType& localRefs, JniMethodInfo&, T x)
    {
        return x;
    }


    static std::string getJNISignature()
    {
        return "";
    }

    static std::string getJNISignature(bool)
    {
        return "Z";
    }

    static std::string getJNISignature(char)
    {
        return "C";
    }

    static std::string getJNISignature(short)
    {
        return "S";
    }

    static std::string getJNISignature(int)
    {
        return "I";
    }

    static std::string getJNISignature(long)
    {
        return "J";
    }

    static std::string getJNISignature(float)
    {
        return "F";
    }

    static  std::string getJNISignature(double)
    {
        return "D";
    }

    static std::string getJNISignature(const char*)
    {
        return "Ljava/lang/String;";
    }

    static std::string getJNISignature(const std::string&)
    {
        return "Ljava/lang/String;";
    }

    template <typename T>
    static std::string getJNISignature(T x)
    {
        // This template should never be instantiated
        // static_assert(sizeof(x) == 0, "Unsupported argument type");
        return "";
    }

    template <typename T, typename... Ts>
    static std::string getJNISignature(T x, Ts... xs)
    {
        return getJNISignature(x) + getJNISignature(xs...);
    }

    static void reportError(const std::string& className, const std::string& methodName, const std::string& signature);


};
//NS_CC_END
#endif // __ANDROID_JNI_HELPER_H__

