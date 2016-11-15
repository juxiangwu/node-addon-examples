{
    "targets": [
    {
      "target_name": "hello",
      "sources": [ "cpp/hello.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}