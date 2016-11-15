{
    "targets": [
    {
      "target_name": "hello",
      "sources": [ "cpp/addon.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}