{
    "targets": [
    {
      "target_name": "addon",
      "sources": [ "cpp/addon.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}