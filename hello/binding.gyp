{
     "targets": [
        {
            "target_name": "hello",
            "sources": [ "hello.cc"],
            "cflags": ["-Wall", "-std=c++11"],
            "include_dirs" : [ "<!(node -e \"require('nan')\")" ]
        }
    ]
}