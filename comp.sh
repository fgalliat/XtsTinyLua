rm *.o 2>/dev/null
g++ -fpermissive -o luac lua.c  2>&1 | grep "error" | grep -v lua_error
rm *.o 2>/dev/null
