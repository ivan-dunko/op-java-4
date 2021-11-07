import java.util.*;
import java.lang.String;

class SystemInfo{
    static native Map<String, String> getCpuInfo();
    //static native void getCpuInfo();

    public static void main(String[] args){
        System.loadLibrary("native");
        /*
        Map<String, String> info = getCpuInfo();
        System.out.println(info);
        */
        getCpuInfo();
        System.out.println(getCpuInfo());
    }
}