#include <jni.h>
#include <assert.h>
#include <stdio.h>
#include <new>
#include <limits>

#include "com_berkeley_abc_Abc.h"
#include "base/main/main.h"
#include "proof/fraig/fraig.h"
#include "proof/fraig/fraigInt.h"
#include "aig/ivy/ivy.h"

#ifdef __cplusplus
extern "C" {
#endif

Fraig_Params_t Params;
Ivy_FraigParams_t iParams;

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
 * Code that throws the Java exception
 */
static void standard_exception(JNIEnv *env) {
  jclass e;
  jint code;

  code = 0;

  if (e != NULL) {
    code = env->ThrowNew(e, "Standard error in ABC JNI.");
  }
  if (e == NULL || code < 0) {
    // Something went  badly wrong.
    // We check whether an exception is pending. If not we report a fatal error
    if (! env->ExceptionCheck()) {
      env->FatalError("Unknown error in ABC JNI.\nFailed to throw an exception\n");
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

//////////////////////////////////////
// AIG
//////////////////////////////////////

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


//////////////////////////////////////
// FRAIG
//////////////////////////////////////

JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Fraig_1ManCreate
  (JNIEnv *env, jclass, jlong fParams) {
    jlong result = 0;

    try {
        if (fParams < 0) {
            result = reinterpret_cast<jlong>(Fraig_ManCreate( NULL ));
        }
        else {
            result = reinterpret_cast<jlong>(Fraig_ManCreate( reinterpret_cast<Fraig_Params_t *>(fParams) ));
        }
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

JNIEXPORT void JNICALL Java_com_berkeley_abc_Abc_Fraig_1ManFree
  (JNIEnv *env, jclass, jlong fAig) {
    try {
        Fraig_ManFree( reinterpret_cast<Fraig_Man_t *>(fAig));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
}

JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Fraig_1ManReadConst1
  (JNIEnv *env, jclass, jlong fAig) {
    jlong result = 0;

    try {
        result = reinterpret_cast<jlong>(Fraig_ManReadConst1( reinterpret_cast<Fraig_Man_t *>(fAig) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Fraig_1ManReadIthVar
  (JNIEnv *env, jclass, jlong fAig, jint i) {
    jlong result = 0;

    try {
        result = reinterpret_cast<jlong>(Fraig_ManReadIthVar( reinterpret_cast<Fraig_Man_t *>(fAig),
                                                              reinterpret_cast<int>(i) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Fraig_1NodeAnd
  (JNIEnv *env, jclass, jlong fAig, jlong fObjA, jlong fObjB) {
    jlong result = 0;

    try {
        result = reinterpret_cast<jlong>(Fraig_NodeAnd( reinterpret_cast<Fraig_Man_t *>(fAig),
                                                        reinterpret_cast<Fraig_Node_t *>(fObjA),
                                                        reinterpret_cast<Fraig_Node_t *>(fObjB) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Fraig_1NodeOr
  (JNIEnv *env, jclass, jlong fAig, jlong fObjA, jlong fObjB) {
    jlong result = 0;

    try {
        result = reinterpret_cast<jlong>(Fraig_NodeOr( reinterpret_cast<Fraig_Man_t *>(fAig),
                                                        reinterpret_cast<Fraig_Node_t *>(fObjA),
                                                        reinterpret_cast<Fraig_Node_t *>(fObjB) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Fraig_1Not
  (JNIEnv *env, jclass, jlong fObj) {
    jlong result = 0;

    try {
        result = reinterpret_cast<jlong>(Fraig_Not( reinterpret_cast<Fraig_Node_t *>(fObj) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

JNIEXPORT jint JNICALL Java_com_berkeley_abc_Abc_Fraig_1ManReadInputNum
  (JNIEnv *env, jclass, jlong fAig) {
    jint result = 0;

    try {
        result = reinterpret_cast<jint>(Fraig_ManReadInputNum( reinterpret_cast<Fraig_Man_t *>(fAig) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Fraig_1Regular
  (JNIEnv *env, jclass, jlong fObj) {
    jlong result = 0;

    try {
        result = reinterpret_cast<jlong>(Fraig_Regular( reinterpret_cast<Fraig_Node_t *>(fObj) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

JNIEXPORT jint JNICALL Java_com_berkeley_abc_Abc_Fraig_1NodeReadNum
  (JNIEnv *env, jclass, jlong fObj) {
    int32_t result = 0;

    try {
        result = Fraig_NodeReadNum( reinterpret_cast<Fraig_Node_t *>(fObj) );
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return (jint)result;
}

JNIEXPORT jboolean JNICALL Java_com_berkeley_abc_Abc_Fraig_1NodeIsVar
  (JNIEnv *env, jclass, jlong fObj) {
    int32_t result;

    try {
        result = Fraig_NodeIsVar( reinterpret_cast<Fraig_Node_t *>(fObj) );
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return (jboolean)result;
}

JNIEXPORT jboolean JNICALL Java_com_berkeley_abc_Abc_Fraig_1IsComplement
  (JNIEnv *env, jclass, jlong fObj) {
    int32_t result;

    try {
        result = Fraig_IsComplement( reinterpret_cast<Fraig_Node_t *>(fObj) );
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return (jboolean)result;
}

JNIEXPORT jboolean JNICALL Java_com_berkeley_abc_Abc_Fraig_1NodeIsConst
  (JNIEnv *env, jclass, jlong fObj) {
    int32_t result;

    try {
        result = Fraig_NodeIsConst( reinterpret_cast<Fraig_Node_t *>(fObj) );
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return (jboolean)result;
}

JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Fraig_1NodeReadOne
  (JNIEnv *env, jclass, jlong fObj) {
    jlong result = 0;

    try {
        result = reinterpret_cast<jlong>(Fraig_NodeReadOne( reinterpret_cast<Fraig_Node_t *>(fObj) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Fraig_1NodeReadTwo
  (JNIEnv *env, jclass, jlong fObj) {
    jlong result = 0;

    try {
        result = reinterpret_cast<jlong>(Fraig_NodeReadTwo( reinterpret_cast<Fraig_Node_t *>(fObj) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

JNIEXPORT void JNICALL Java_com_berkeley_abc_Abc_Fraig_1ManPrintStats
  (JNIEnv *env, jclass, jlong fAig) {
    try {
        Fraig_ManPrintStats( reinterpret_cast<Fraig_Man_t *>(fAig));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
}

JNIEXPORT jboolean JNICALL Java_com_berkeley_abc_Abc_Fraig_1NodesAreEqual
  (JNIEnv *env, jclass, jlong fAig, jlong fObjA, jlong fObjB, jint nBTLimit, jint nTimeLimit) {
    int32_t result;

    try {
        result = Fraig_NodesAreEqual(   reinterpret_cast<Fraig_Man_t *>(fAig),
                                        reinterpret_cast<Fraig_Node_t *>(fObjA),
                                        reinterpret_cast<Fraig_Node_t *>(fObjB),
                                        reinterpret_cast<int>(nBTLimit),
                                        reinterpret_cast<int>(nTimeLimit)    );
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return (jboolean)result;
}

JNIEXPORT jboolean JNICALL Java_com_berkeley_abc_Abc_Fraig_1ManCheckClauseUsingSimInfo
  (JNIEnv *env, jclass, jlong fAig, jlong fObjA, jlong fObjB) {
    int32_t result;

    try {
        result = Fraig_ManCheckClauseUsingSimInfo(  reinterpret_cast<Fraig_Man_t *>(fAig),
                                                    reinterpret_cast<Fraig_Node_t *>(fObjA),
                                                    reinterpret_cast<Fraig_Node_t *>(fObjB)    );
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return (jboolean)result;
}

JNIEXPORT jint JNICALL Java_com_berkeley_abc_Abc_Fraig_1ManCheckClauseUsingSat
  (JNIEnv *env, jclass, jlong fAig, jlong fObjA, jlong fObjB, jint nBTLimit) {
    int32_t result;
    Fraig_Man_t *fMan = reinterpret_cast<Fraig_Man_t *>(fAig);
    int nSatFailsImpOld = fMan->nSatFailsImp;

    try {
        result = Fraig_ManCheckClauseUsingSat(  fMan,
                                                reinterpret_cast<Fraig_Node_t *>(fObjA),
                                                reinterpret_cast<Fraig_Node_t *>(fObjB),
                                                reinterpret_cast<int>(nBTLimit)    );
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    if (result == 1) {
        return 1;
    } else if (fMan->nSatFailsImp == nSatFailsImpOld) {
        return 0;
    } else {
        return -1;
    }
}

JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Fraig_1ParamsGetDefault
  (JNIEnv *env, jclass) {
    jlong result = 0;

    try {
        Fraig_ParamsSetDefault( &Params );
        result = reinterpret_cast<jlong>( &Params );
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Fraig_1ParamsGetDefaultFull
  (JNIEnv *env, jclass) {
    jlong result = 0;

    try {
        Fraig_ParamsSetDefaultFull( &Params );
        result = reinterpret_cast<jlong>( &Params );
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

JNIEXPORT void JNICALL Java_com_berkeley_abc_Abc_Fraig_1ParamsSet_1nPatsRand
  (JNIEnv *env, jclass, jlong fParams, jint n) {
    try {
        ( reinterpret_cast<Fraig_Params_t *>(fParams))->nPatsRand = reinterpret_cast<int>(n);
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
}

JNIEXPORT void JNICALL Java_com_berkeley_abc_Abc_Fraig_1ParamsSet_1nPatsDyna
  (JNIEnv *env, jclass, jlong fParams, jint n) {
    try {
        ( reinterpret_cast<Fraig_Params_t *>(fParams))->nPatsDyna = reinterpret_cast<int>(n);
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
}

JNIEXPORT void JNICALL Java_com_berkeley_abc_Abc_Fraig_1ParamsSet_1nBTLimit
  (JNIEnv *env, jclass, jlong fParams, jint n) {
    try {
        ( reinterpret_cast<Fraig_Params_t *>(fParams))->nBTLimit = reinterpret_cast<int>(n);
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
}

JNIEXPORT void JNICALL Java_com_berkeley_abc_Abc_Fraig_1ParamsSet_1nSeconds
  (JNIEnv *env, jclass, jlong fParams, jint n) {
    try {
        ( reinterpret_cast<Fraig_Params_t *>(fParams))->nSeconds = reinterpret_cast<int>(n);
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
}

JNIEXPORT void JNICALL Java_com_berkeley_abc_Abc_Fraig_1ParamsSet_1fFuncRed
  (JNIEnv *env, jclass, jlong fParams, jint n) {
    try {
        ( reinterpret_cast<Fraig_Params_t *>(fParams))->fFuncRed = reinterpret_cast<int>(n);
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
}

JNIEXPORT void JNICALL Java_com_berkeley_abc_Abc_Fraig_1ParamsSet_1fFeedBack
  (JNIEnv *env, jclass, jlong fParams, jint n) {
    try {
        ( reinterpret_cast<Fraig_Params_t *>(fParams))->fFeedBack = reinterpret_cast<int>(n);
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
}

JNIEXPORT void JNICALL Java_com_berkeley_abc_Abc_Fraig_1ParamsSet_1fDist1Pats
  (JNIEnv *env, jclass, jlong fParams, jint n) {
    try {
        ( reinterpret_cast<Fraig_Params_t *>(fParams))->fDist1Pats = reinterpret_cast<int>(n);
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
}

JNIEXPORT void JNICALL Java_com_berkeley_abc_Abc_Fraig_1ParamsSet_1fDoSparse
  (JNIEnv *env, jclass, jlong fParams, jint n) {
    try {
        ( reinterpret_cast<Fraig_Params_t *>(fParams))->fDoSparse = reinterpret_cast<int>(n);
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
}

JNIEXPORT void JNICALL Java_com_berkeley_abc_Abc_Fraig_1ParamsSet_1fChoicing
  (JNIEnv *env, jclass, jlong fParams, jint n) {
    try {
        ( reinterpret_cast<Fraig_Params_t *>(fParams))->fChoicing = reinterpret_cast<int>(n);
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
}

JNIEXPORT void JNICALL Java_com_berkeley_abc_Abc_Fraig_1ParamsSet_1fTryProve
  (JNIEnv *env, jclass, jlong fParams, jint n) {
    try {
        ( reinterpret_cast<Fraig_Params_t *>(fParams))->fTryProve = reinterpret_cast<int>(n);
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
}

JNIEXPORT void JNICALL Java_com_berkeley_abc_Abc_Fraig_1ParamsSet_1fVerbose
  (JNIEnv *env, jclass, jlong fParams, jint n) {
    try {
        ( reinterpret_cast<Fraig_Params_t *>(fParams))->fVerbose = reinterpret_cast<int>(n);
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
}

JNIEXPORT void JNICALL Java_com_berkeley_abc_Abc_Fraig_1ParamsSet_1fVerboseP
  (JNIEnv *env, jclass, jlong fParams, jint n) {
    try {
        ( reinterpret_cast<Fraig_Params_t *>(fParams))->fVerboseP = reinterpret_cast<int>(n);
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
}

JNIEXPORT void JNICALL Java_com_berkeley_abc_Abc_Fraig_1ParamsSet_1fInternal
  (JNIEnv *env, jclass, jlong fParams, jint n) {
    try {
        ( reinterpret_cast<Fraig_Params_t *>(fParams))->fInternal = reinterpret_cast<int>(n);
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
}

JNIEXPORT void JNICALL Java_com_berkeley_abc_Abc_Fraig_1ParamsSet_1nConfLimit
  (JNIEnv *env, jclass, jlong fParams, jint n) {
    try {
        ( reinterpret_cast<Fraig_Params_t *>(fParams))->nConfLimit = reinterpret_cast<int>(n);
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
}

JNIEXPORT void JNICALL Java_com_berkeley_abc_Abc_Fraig_1ParamsSet_1nInspLimit
  (JNIEnv *env, jclass, jlong fParams, jint n) {
    try {
        ( reinterpret_cast<Fraig_Params_t *>(fParams))->nInspLimit = reinterpret_cast<int>(n);
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
}


//////////////////////////////////////
// IVYAIG
//////////////////////////////////////

/*
 * Class:     com_berkeley_abc_Abc
 * Method:    Ivy_ManStart
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Ivy_1ManStart
  (JNIEnv *env, jclass) {
    jlong result = 0;

    try {
        result = reinterpret_cast<jlong>(Ivy_ManStart());
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

/*
 * Class:     com_berkeley_abc_Abc
 * Method:    Ivy_ManStop
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_berkeley_abc_Abc_Ivy_1ManStop
  (JNIEnv *env, jclass, jlong fAig) {
    try {
        Ivy_ManStop( reinterpret_cast<Ivy_Man_t *>(fAig));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
}

/*
 * Class:     com_berkeley_abc_Abc
 * Method:    Ivy_ManConst1
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Ivy_1ManConst1
  (JNIEnv *env, jclass, jlong fAig) {
    jlong result = 0;

    try {
        result = reinterpret_cast<jlong>(Ivy_ManConst1( reinterpret_cast<Ivy_Man_t *>(fAig) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

/*
 * Class:     com_berkeley_abc_Abc
 * Method:    Ivy_ObjCreatePi
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Ivy_1ObjCreatePi
  (JNIEnv *env, jclass, jlong fAig) {
    jlong result = 0;

    try {
        result = reinterpret_cast<jlong>(Ivy_ObjCreatePi( reinterpret_cast<Ivy_Man_t *>(fAig) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

/*
 * Class:     com_berkeley_abc_Abc
 * Method:    Ivy_And
 * Signature: (JJJ)J
 */
JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Ivy_1And
  (JNIEnv *env, jclass, jlong fAig, jlong fObjA, jlong fObjB) {
    jlong result = 0;

    try {
        result = reinterpret_cast<jlong>(Ivy_And( reinterpret_cast<Ivy_Man_t *>(fAig),
                                                  reinterpret_cast<Ivy_Obj_t *>(fObjA),
                                                  reinterpret_cast<Ivy_Obj_t *>(fObjB) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

/*
 * Class:     com_berkeley_abc_Abc
 * Method:    Ivy_Or
 * Signature: (JJJ)J
 */
JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Ivy_1Or
  (JNIEnv *env, jclass, jlong fAig, jlong fObjA, jlong fObjB) {
    jlong result = 0;

    try {
        result = reinterpret_cast<jlong>(Ivy_Or( reinterpret_cast<Ivy_Man_t *>(fAig),
                                                 reinterpret_cast<Ivy_Obj_t *>(fObjA),
                                                 reinterpret_cast<Ivy_Obj_t *>(fObjB) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

/*
 * Class:     com_berkeley_abc_Abc
 * Method:    Ivy_Not
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Ivy_1Not
  (JNIEnv *env, jclass, jlong fObj) {
    jlong result = 0;

    try {
        result = reinterpret_cast<jlong>(Ivy_Not( reinterpret_cast<Ivy_Obj_t *>(fObj) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

/*
 * Class:     com_berkeley_abc_Abc
 * Method:    Ivy_ManPiNum
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_berkeley_abc_Abc_Ivy_1ManPiNum
  (JNIEnv *env, jclass, jlong fAig) {
    jint result = 0;

    try {
        result = reinterpret_cast<jint>(Ivy_ManPiNum( reinterpret_cast<Ivy_Man_t *>(fAig) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

/*
 * Class:     com_berkeley_abc_Abc
 * Method:    Ivy_Regular
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Ivy_1Regular
  (JNIEnv *env, jclass, jlong fObj) {
    jlong result = 0;

    try {
        result = reinterpret_cast<jlong>(Ivy_Regular( reinterpret_cast<Ivy_Obj_t *>(fObj) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

/*
 * Class:     com_berkeley_abc_Abc
 * Method:    Ivy_ObjId
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_berkeley_abc_Abc_Ivy_1ObjId
  (JNIEnv *env, jclass, jlong fObj) {
    int32_t result = 0;

    try {
        result = Ivy_ObjId( reinterpret_cast<Ivy_Obj_t *>(fObj) );
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return (jint)result;
}

/*
 * Class:     com_berkeley_abc_Abc
 * Method:    Ivy_ObjIsPi
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_berkeley_abc_Abc_Ivy_1ObjIsPi
  (JNIEnv *env, jclass, jlong fObj) {
    int32_t result;

    try {
        result = Ivy_ObjIsPi( reinterpret_cast<Ivy_Obj_t *>(fObj) );
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return (jboolean)result;
}

/*
 * Class:     com_berkeley_abc_Abc
 * Method:    Ivy_IsComplement
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_berkeley_abc_Abc_Ivy_1IsComplement
  (JNIEnv *env, jclass, jlong fObj) {
    int32_t result;

    try {
        result = Ivy_IsComplement( reinterpret_cast<Ivy_Obj_t *>(fObj) );
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return (jboolean)result;
}

/*
 * Class:     com_berkeley_abc_Abc
 * Method:    Ivy_ObjIsConst1
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_berkeley_abc_Abc_Ivy_1ObjIsConst1
  (JNIEnv *env, jclass, jlong fObj) {
    int32_t result;

    try {
        result = Ivy_ObjIsConst1( reinterpret_cast<Ivy_Obj_t *>(fObj) );
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return (jboolean)result;
}

/*
 * Class:     com_berkeley_abc_Abc
 * Method:    Ivy_ObjChild0
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Ivy_1ObjChild0
  (JNIEnv *env, jclass, jlong fObj) {
    jlong result = 0;

    try {
        result = reinterpret_cast<jlong>(Ivy_ObjChild0( reinterpret_cast<Ivy_Obj_t *>(fObj) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

/*
 * Class:     com_berkeley_abc_Abc
 * Method:    Ivy_ObjChild1
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Ivy_1ObjChild1
  (JNIEnv *env, jclass, jlong fObj) {
    jlong result = 0;

    try {
        result = reinterpret_cast<jlong>(Ivy_ObjChild1( reinterpret_cast<Ivy_Obj_t *>(fObj) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

/*
 * Class:     com_berkeley_abc_Abc
 * Method:    Ivy_ManPrintStats
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_berkeley_abc_Abc_Ivy_1ManPrintStats
  (JNIEnv *env, jclass, jlong fAig) {
    try {
        Ivy_ManPrintStats( reinterpret_cast<Ivy_Man_t *>(fAig) );
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
}


/*
 * Class:     com_berkeley_abc_Abc
 * Method:    Ivy_FraigParamsDefault
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Ivy_1FraigParamsDefault
  (JNIEnv *env, jclass) {
    jlong result = 0;

    try {
        Ivy_FraigParamsDefault( &iParams );
        result = reinterpret_cast<jlong>( &iParams );
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

/*
 * Class:     com_berkeley_abc_Abc
 * Method:    Ivy_FraigPerform
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Ivy_1FraigPerform
  (JNIEnv *env, jclass, jlong fAig, jlong fParams) {
    jlong result = 0;

    try {
        result = reinterpret_cast<jlong>(Ivy_FraigPerform( reinterpret_cast<Ivy_Man_t *>(fAig),
                                                           reinterpret_cast<Ivy_FraigParams_t *>(fParams) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

/*
 * Class:     com_berkeley_abc_Abc
 * Method:    Ivy_ObjEquiv
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_berkeley_abc_Abc_Ivy_1ObjEquiv
  (JNIEnv *env, jclass, jlong fObj) {
    jlong result = 0;

    try {
        result = reinterpret_cast<jlong>(Ivy_ObjEquiv( reinterpret_cast<Ivy_Obj_t *>(fObj) ));
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return result;
}

/*
 * Class:     com_berkeley_abc_Abc
 * Method:    Ivy_ManCheck
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_berkeley_abc_Abc_Ivy_1ManCheck
  (JNIEnv *env, jclass, jlong fAig) {
    int32_t result;

    try {
        result = Ivy_ManCheck( reinterpret_cast<Ivy_Man_t *>(fAig) );
    } catch (std::bad_alloc &ba) {
         out_of_mem_exception(env);
    }
    return (jboolean)result;
}


#ifdef __cplusplus
}
#endif
