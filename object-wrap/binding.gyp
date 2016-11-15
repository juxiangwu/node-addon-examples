{
    "targets": [
    {
      "target_name": "addon",
      "sources": [ "cpp/addon.cc","cpp/person.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}