package com.berkeley.abc;

public final class Abc {
    private static boolean is_ready;

    /*
     * Try to load the Abc Library libabc2java.
     *
     * For now, it's best to see the exception (if any) rather than catch it
     * and print a generic message.
     */
    static {
        try {
            System.loadLibrary("abc2java");
            is_ready = true;
        } catch (LinkageError e) {
            is_ready = false;
            throw e;
        }
    }

    /*
     * Check whether the library is loaded.
     * @throws LinkageError if one of the required runtime library is not found
     * (or can't be loaded for some reason).
     */
    public static boolean isReady() {
        return is_ready;
    }

    public static final String versionString = "1.0.0";
    public static final String buildDate = "March 7 2022";


    // Abc Network
    public static native void Abc_Start();
    public static native void Abc_Stop();

    public static native long Abc_NtkAlloc();
    public static native void Abc_NtkDelete( long pAig );
    public static native boolean Abc_NtkCheck( long pAig );

    public static native long Abc_NtkCreateNodeConst0( long pAig );
    public static native long Abc_NtkCreateNodeConst1( long pAig );

    public static native long Abc_NtkCreatePi( long pAig );
    public static native long Abc_NtkCreatePo( long pAig );

    public static native int Abc_NtkPiNum( long pAig );
    public static native int Abc_NtkPoNum( long pAig );


    // Aig
    public static native long Abc_AigConst1( long pAig );
    public static native long Abc_AigAnd( long pAig, long pObjA, long pObjB );
    public static native long Abc_AigOr( long pAig, long pObjA, long pObjB );
    public static native long Abc_ObjNot( long pObj );
    public static native void Abc_ObjAddFanin( long pObjO, long pObjI );

    public static native void Abc_AigPrintNode( long pObj );
    public static native long Abc_ObjRegular( long pObj );
    public static native long Abc_ObjId( long pObj );
    public static native void Abc_ObjAssignName( long pObj, String name );
    public static native String Abc_ObjName( long pObj );

    public static native void Abc_AigCleanup( long pAig );

    public static native boolean Abc_ObjIsCi( long pObj );
    public static native boolean Abc_ObjIsComplement( long pObj );
    public static native boolean Abc_AigNodeIsConst( long pObj );

    public static native long Abc_ObjFanin0( long pObj );
    public static native long Abc_ObjFanin1( long pObj );
    public static native boolean Abc_ObjFaninC0( long pObj );
    public static native boolean Abc_ObjFaninC1( long pObj );

    public static native long Abc_ObjChild0( long pObj );
    public static native long Abc_ObjChild1( long pObj );


    // Fraig
    public static native long Fraig_ManCreate( long fParams );
    public static native void Fraig_ManFree( long fAig );

    public static native long Fraig_ManReadConst1( long fAig );
    public static native long Fraig_ManReadIthVar( long fAig, int i );
    public static native long Fraig_NodeAnd( long fAig, long fObjA, long fObjB );
    public static native long Fraig_NodeOr( long fAig, long fObjA, long fObjB );
    public static native long Fraig_Not( long fObj );

    public static native int Fraig_ManReadInputNum( long fAig );

    public static native long Fraig_Regular( long fObj );
    public static native int Fraig_NodeReadNum( long fObj );

    public static native boolean Fraig_NodeIsVar( long fObj );
    public static native boolean Fraig_IsComplement( long fObj );
    public static native boolean Fraig_NodeIsConst( long fObj );

    public static native long Fraig_NodeReadOne( long fObj );
    public static native long Fraig_NodeReadTwo( long fObj );

    public static native void Fraig_ManPrintStats( long fAig );
    public static native boolean Fraig_NodesAreEqual( long fAig, long fObjA, long fObjB, int nBTLimit, int nTimeLimit );

    public static native boolean Fraig_ManCheckClauseUsingSimInfo( long fAig, long fObjA, long fObjB );
    public static native int Fraig_ManCheckClauseUsingSat( long fAig, long fObjA, long fObjB, int nBTLimit );

    public static native long Fraig_ParamsGetDefault();

    public static native void Fraig_ParamsSet_nPatsRand( long fParams, int n );
    public static native void Fraig_ParamsSet_nPatsDyna( long fParams, int n );
    public static native void Fraig_ParamsSet_nBTLimit( long fParams, int n );
    public static native void Fraig_ParamsSet_nSeconds( long fParams, int n );
    public static native void Fraig_ParamsSet_fFuncRed( long fParams, int n );
    public static native void Fraig_ParamsSet_fFeedBack( long fParams, int n );
    public static native void Fraig_ParamsSet_fDist1Pats( long fParams, int n );
    public static native void Fraig_ParamsSet_fDoSparse( long fParams, int n );
    public static native void Fraig_ParamsSet_fChoicing( long fParams, int n );
    public static native void Fraig_ParamsSet_fTryProve( long fParams, int n );
    public static native void Fraig_ParamsSet_fVerbose( long fParams, int n );
    public static native void Fraig_ParamsSet_fVerboseP( long fParams, int n );
    public static native void Fraig_ParamsSet_fInternal( long fParams, int n );
    public static native void Fraig_ParamsSet_nConfLimit( long fParams, int n );
    public static native void Fraig_ParamsSet_nInspLimit( long fParams, int n );


    // Ivy Aig
    public static native long Ivy_ManStart();
    public static native void Ivy_ManStop( long fAig );

    public static native long Ivy_ManConst1( long fAig );
    public static native long Ivy_ObjCreatePi( long fAig );
    public static native long Ivy_And( long fAig, long fObjA, long fObjB );
    public static native long Ivy_Or( long fAig, long fObjA, long fObjB );
    public static native long Ivy_Not( long fObj );

    public static native int Ivy_ManPiNum( long fAig );

    public static native long Ivy_Regular( long fObj );
    public static native int Ivy_ObjId( long fObj );

    public static native boolean Ivy_ObjIsPi( long fObj );
    public static native boolean Ivy_IsComplement( long fObj );
    public static native boolean Ivy_ObjIsConst1( long fObj );

    public static native long Ivy_ObjChild0( long fObj );
    public static native long Ivy_ObjChild1( long fObj );

    public static native void Ivy_ManPrintStats( long fAig );

    public static native long Ivy_FraigParamsDefault();
    public static native long Ivy_FraigPerform( long fAig, long fParams );
    public static native long Ivy_ObjEquiv( long fObj );

    public static native boolean Ivy_ManCheck( long fAig );

    public static void main(String[] args){
        System.err.println("Abc ready? " + isReady());
        System.err.println("Abc Java Bindings Version " + versionString);
        System.err.println("Build date: " + buildDate);
        System.err.println("Starting Abc");
        Abc_Start();
        System.err.println("Stopping Abc");
        Abc_Stop();
        System.err.println("Done!");
    }
}
