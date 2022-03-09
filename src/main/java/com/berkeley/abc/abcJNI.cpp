#include <jni.h>
#include <assert.h>
#include <stdio.h>
#include <new>
#include <limits>

#include "com_berkeley_abc_Abc.h"
#include "base/main/main.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Out-of-memory handler: throws a C++ exception
 * that we can catch and convert to a Java exception.
 *
 * The default behavior of yices is to call "exit(1)" when
 * it runs out-of-memory, which woulld kill the JVM.
 */
static void throw_out_of_mem_exception() {
  throw std::bad_alloc();
}


/*
 * Code that throws the Java exception
 */
static void out_of_mem_exception(JNIEnv *env) {
  jclass e;
  jint code;

  code = 0;
  e = env->FindClass("com/berkeley/abc/OutOfMemory");
  if (e == NULL) e = env->FindClass("java/lang/OutOfMemoryError");

  if (e != NULL) {
    code = env->ThrowNew(e, NULL);
  }
  if (e == NULL || code < 0) {
    // Something went  badly wrong.
    // We check whether an exception is pending. If not we report a fatal error
    if (! env->ExceptionCheck()) {
      env->FatalError("Out-of-memory in ABC JNI.\nFailed to throw an exception\n");
    }
  }
}


/*
 * Convert a string (s may be NULL);
 */
static jstring convertToString(JNIEnv *env, const char *s) {
  jstring b = NULL;

  if (s != NULL) {
    b = env->NewStringUTF(s);
    if (b == NULL) {
      out_of_mem_exception(env);
    }
  }
  return b;
}


/*
 * GLOBAL INITIALIZATION/EXIT/RESET
 */
JNIEXPORT void JNICALL Java_com_berkeley_abc_Abc_Abc_1Start
  (JNIEnv *env, jclass) {
    Abc_Start();
}

JNIEXPORT void JNICALL Java_com_berkeley_abc_Abc_Abc_1Stop
  (JNIEnv *env, jclass) {
    Abc_Stop();
}


/*
 * NETWORK INITIALIZATION/EXIT/RESET
 */
JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Abc_1NtkAlloc
  (JNIEnv *env, jclass) {
    jlong result = 0;

    try {
        result = reinterpret_cast<jlong>(Abc_NtkAlloc( ABC_NTK_STRASH, ABC_FUNC_AIG, 1 ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

JNIEXPORT void JNICALL Java_com_berkeley_abc_Abc_Abc_1NtkDelete
  (JNIEnv *env, jclass, jlong pAig) {
    try {
        Abc_NtkDelete( reinterpret_cast<Abc_Ntk_t *>(pAig));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
}


/*
 * CREATE/CONNECT AIG NODES
 */
JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Abc_1AigConst1
  (JNIEnv *env, jclass, jlong pAig) {
    jlong result = 0;

    try {
        result = reinterpret_cast<jlong>(Abc_AigConst1( reinterpret_cast<Abc_Ntk_t *>(pAig) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Abc_1NtkCreateNodeConst0
  (JNIEnv *env, jclass, jlong pAig) {
    jlong result = 0;

    try {
        result = reinterpret_cast<jlong>(Abc_NtkCreateNodeConst0( reinterpret_cast<Abc_Ntk_t *>(pAig) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Abc_1NtkCreateNodeConst1
  (JNIEnv *env, jclass, jlong pAig) {
    jlong result = 0;

    try {
        result = reinterpret_cast<jlong>(Abc_NtkCreateNodeConst1( reinterpret_cast<Abc_Ntk_t *>(pAig) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Abc_1NtkCreatePi
  (JNIEnv *env, jclass, jlong pAig) {
    jlong result = 0;

    try {
        result = reinterpret_cast<jlong>(Abc_NtkCreatePi( reinterpret_cast<Abc_Ntk_t *>(pAig) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Abc_1NtkCreatePo
  (JNIEnv *env, jclass, jlong pAig) {
    jlong result = 0;

    try {
        result = reinterpret_cast<jlong>(Abc_NtkCreatePo( reinterpret_cast<Abc_Ntk_t *>(pAig) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Abc_1AigAnd
  (JNIEnv *env, jclass, jlong pAig, jlong pObjA, jlong pObjB) {
    jlong result = 0;

    try {
        result = reinterpret_cast<jlong>(Abc_AigAnd( reinterpret_cast<Abc_Aig_t *>(reinterpret_cast<Abc_Ntk_t *>(pAig)->pManFunc),
                                                     reinterpret_cast<Abc_Obj_t *>(pObjA),
                                                     reinterpret_cast<Abc_Obj_t *>(pObjB) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Abc_1AigOr
  (JNIEnv *env, jclass, jlong pAig, jlong pObjA, jlong pObjB) {
    jlong result = 0;

    try {
        result = reinterpret_cast<jlong>(Abc_AigOr( reinterpret_cast<Abc_Aig_t *>(reinterpret_cast<Abc_Ntk_t *>(pAig)->pManFunc),
                                                     reinterpret_cast<Abc_Obj_t *>(pObjA),
                                                     reinterpret_cast<Abc_Obj_t *>(pObjB) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Abc_1ObjNot
  (JNIEnv *env, jclass, jlong pObj) {
    jlong result = 0;

    try {
        result = reinterpret_cast<jlong>(Abc_ObjNot( reinterpret_cast<Abc_Obj_t *>(pObj) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

JNIEXPORT void JNICALL Java_com_berkeley_abc_Abc_Abc_1ObjAddFanin
  (JNIEnv *env, jclass, jlong pObjO, jlong pObjI) {
    try {
        Abc_ObjAddFanin( reinterpret_cast<Abc_Obj_t *>(pObjO),
                         reinterpret_cast<Abc_Obj_t *>(pObjI) );
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
}


/*
 * NETWORK UTILITIES
 */
JNIEXPORT jint JNICALL Java_com_berkeley_abc_Abc_Abc_1NtkPiNum
  (JNIEnv *env, jclass, jlong pAig) {
    jint result = 0;

    try {
        result = reinterpret_cast<jint>(Abc_NtkPiNum( reinterpret_cast<Abc_Ntk_t *>(pAig) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

JNIEXPORT jint JNICALL Java_com_berkeley_abc_Abc_Abc_1NtkPoNum
  (JNIEnv *env, jclass, jlong pAig) {
    jint result = 0;

    try {
        result = reinterpret_cast<jint>(Abc_NtkPoNum( reinterpret_cast<Abc_Ntk_t *>(pAig) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

JNIEXPORT void JNICALL Java_com_berkeley_abc_Abc_Abc_1AigPrintNode
  (JNIEnv *env, jclass, jlong pObj) {
    try {
        Abc_AigPrintNode( reinterpret_cast<Abc_Obj_t *>(pObj) );
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
}

JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Abc_1ObjRegular
  (JNIEnv *env, jclass, jlong pObj) {
    jlong result = 0;

    try {
        result = reinterpret_cast<jlong>(Abc_ObjRegular( reinterpret_cast<Abc_Obj_t *>(pObj) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Abc_1ObjId
  (JNIEnv *env, jclass, jlong pObj) {
    unsigned result = 0;

    try {
        result = Abc_ObjId( reinterpret_cast<Abc_Obj_t *>(pObj) );
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return (jlong)result;
}

JNIEXPORT void JNICALL Java_com_berkeley_abc_Abc_Abc_1ObjAssignName
  (JNIEnv *env, jclass, jlong pObj, jstring name) {
    const char *s = env->GetStringUTFChars(name, NULL);

    if (name == NULL) {
        out_of_mem_exception(env);
    } else {
        try {
            Abc_ObjAssignName( reinterpret_cast<Abc_Obj_t *>(pObj), (char *)s, NULL );
        } catch (std::bad_alloc &ba) {
             out_of_mem_exception(env);
        }
        env->ReleaseStringUTFChars(name, s);
    }
}

JNIEXPORT jstring JNICALL Java_com_berkeley_abc_Abc_Abc_1ObjName
  (JNIEnv *env, jclass, jlong pObj) {
    char *s;
    jstring result;

    try {
        s = Abc_ObjName( reinterpret_cast<Abc_Obj_t *>(pObj) );
        result = convertToString(env, s);
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}


JNIEXPORT void JNICALL Java_com_berkeley_abc_Abc_Abc_1AigCleanup
  (JNIEnv *env, jclass, jlong pAig) {
    try {
        Abc_AigCleanup( reinterpret_cast<Abc_Aig_t *>(reinterpret_cast<Abc_Ntk_t *>(pAig)->pManFunc) );
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
}

JNIEXPORT jboolean JNICALL Java_com_berkeley_abc_Abc_Abc_1NtkCheck
  (JNIEnv *env, jclass, jlong pAig) {
    int32_t result;

    try {
        result = Abc_NtkCheck( reinterpret_cast<Abc_Ntk_t *>(pAig) );
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return (jboolean)result;
}

JNIEXPORT jboolean JNICALL Java_com_berkeley_abc_Abc_Abc_1ObjIsCi
  (JNIEnv *env, jclass, jlong pObj) {
    int32_t result;

    try {
        result = Abc_ObjIsCi( reinterpret_cast<Abc_Obj_t *>(pObj) );
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return (jboolean)result;
}

JNIEXPORT jboolean JNICALL Java_com_berkeley_abc_Abc_Abc_1ObjIsComplement
  (JNIEnv *env, jclass, jlong pObj) {
    int32_t result;

    try {
        result = Abc_ObjIsComplement( reinterpret_cast<Abc_Obj_t *>(pObj) );
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return (jboolean)result;
}

JNIEXPORT jboolean JNICALL Java_com_berkeley_abc_Abc_Abc_1AigNodeIsConst
  (JNIEnv *env, jclass, jlong pObj) {
    int32_t result;

    try {
        result = Abc_AigNodeIsConst( reinterpret_cast<Abc_Obj_t *>(pObj) );
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return (jboolean)result;
}

JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Abc_1ObjFanin0
  (JNIEnv *env, jclass, jlong pObj) {
    jlong result = 0;

    try {
        result = reinterpret_cast<jlong>(Abc_ObjFanin0( reinterpret_cast<Abc_Obj_t *>(pObj) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Abc_1ObjFanin1
  (JNIEnv *env, jclass, jlong pObj) {
    jlong result = 0;

    try {
        result = reinterpret_cast<jlong>(Abc_ObjFanin1( reinterpret_cast<Abc_Obj_t *>(pObj) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

JNIEXPORT jboolean JNICALL Java_com_berkeley_abc_Abc_Abc_1ObjFaninC0
  (JNIEnv *env, jclass, jlong pObj) {
    int32_t result;

    try {
        result = Abc_ObjFaninC0( reinterpret_cast<Abc_Obj_t *>(pObj) );
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return (jboolean)result;
}

JNIEXPORT jboolean JNICALL Java_com_berkeley_abc_Abc_Abc_1ObjFaninC1
  (JNIEnv *env, jclass, jlong pObj) {
    int32_t result;

    try {
        result = Abc_ObjFaninC1( reinterpret_cast<Abc_Obj_t *>(pObj) );
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return (jboolean)result;
}

JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Abc_1ObjChild0
  (JNIEnv *env, jclass, jlong pObj) {
    jlong result = 0;

    try {
        result = reinterpret_cast<jlong>(Abc_ObjChild0( reinterpret_cast<Abc_Obj_t *>(pObj) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Abc_1ObjChild1
  (JNIEnv *env, jclass, jlong pObj) {
    jlong result = 0;

    try {
        result = reinterpret_cast<jlong>(Abc_ObjChild1( reinterpret_cast<Abc_Obj_t *>(pObj) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}


#ifdef __cplusplus
}
#endif
