-dontobfuscate
-verbose

-keep class com.eegeo.mobilesdkharness.INativeMessageRunner

-keep class com.eegeo.** { *; }
-dontwarn com.eegeo.**

-keep class com.google.android.gms.* { public *; }
-dontwarn com.google.android.gms.**

-keep public class java.lang.management.* { public *; }
-dontwarn java.lang.management.**

-keep class org.codehaus.mojo.**
-dontwarn org.codehaus.mojo.**

-keep class javax.xml.bind.*
-dontwarn javax.xml.bind.*

-keep public interface org.easymock.** { *; }
-dontwarn org.easymock.**
-keep class junit.framework.TestCase { *; }
-dontwarn junit.framework.TestCase
-keep class junit.runner.BaseTestRunner { *; }
-dontwarn junit.runner.BaseTestRunner 

-dontwarn android.test.**
-dontwarn android.support.test.**


-keep class javax.lang.model.element.** { *; }
-dontwarn javax.lang.model.element.**

-keep class com.google.vr.cardboard.** { *; }