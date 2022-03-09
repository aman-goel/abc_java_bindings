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

    public static native void Abc_Start();
    public static native void Abc_Stop();

    public static native long Abc_NtkAlloc();
    public static native void Abc_NtkDelete( long pAig );

    public static native long Abc_AigConst1( long pAig );
    public static native long Abc_NtkCreateNodeConst0( long pAig );
    public static native long Abc_NtkCreateNodeConst1( long pAig );

    public static native long Abc_NtkCreatePi( long pAig );
    public static native long Abc_NtkCreatePo( long pAig );

    public static native long Abc_AigAnd( long pAig, long pObjA, long pObjB );
    public static native long Abc_AigOr( long pAig, long pObjA, long pObjB );
    public static native long Abc_ObjNot( long pObj );
    public static native void Abc_ObjAddFanin( long pObjO, long pObjI );

    public static native int Abc_NtkPiNum( long pAig );
    public static native int Abc_NtkPoNum( long pAig );

    public static native void Abc_AigPrintNode( long pObj );
    public static native long Abc_ObjRegular( long pObj );
    public static native long Abc_ObjId( long pObj );
    public static native void Abc_ObjAssignName( long pObj, String name );
    public static native String Abc_ObjName( long pObj );

    public static native void Abc_AigCleanup( long pAig );
    public static native boolean Abc_NtkCheck( long pAig );

    public static native boolean Abc_ObjIsCi( long pObj );
    public static native boolean Abc_ObjIsComplement( long pObj );
    public static native boolean Abc_AigNodeIsConst( long pObj );

    public static native long Abc_ObjFanin0( long pObj );
    public static native long Abc_ObjFanin1( long pObj );
    public static native boolean Abc_ObjFaninC0( long pObj );
    public static native boolean Abc_ObjFaninC1( long pObj );

    public static native long Abc_ObjChild0( long pObj );
    public static native long Abc_ObjChild1( long pObj );

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
