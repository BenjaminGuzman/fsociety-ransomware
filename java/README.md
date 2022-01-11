# Fsociety ransomware

-- Java -- abandoned
## Instructions

### Generate headers
```shell
javac net/benjaminguzman/Main.java -h a
```

### Compile C library

On GNU/Linux
```shell
gcc -fPIC -I"$JAVA_HOME/include" -I"$JAVA_HOME/include/linux" -shared -o liba.so net_benjaminguzman_Main.c
```
(**lib** prefix is important)

On Windows
TODO

### Create jar

```shell
javac net/benjaminguzman/*.java -d /tmp/out && jar cvfm fsociety.jar MANIFEST.MF -C /tmp/out/ . a/liba.so
```