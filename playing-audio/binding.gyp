{
    "targets": [
        {
            "target_name": "player",
            "sources": ["cpp/addon.cc"],
            "link_settings": {
                "libraries": ["-lfmodex64_vc","-lfmodexL64_vc"],
                "library_dirs":["cpp/fmod/lib"],
                "include_dirs":["cpp/fmod/inc"]
            },
            "include_dirs": [
                "<!(node -e \"require('nan')\")",
                "cpp/fmod/inc",
                "cpp"
            ],
            "cflags": [
                "-g", "-std=c++11", "-Wall"
            ],
#            "conditions": [
#                ['OS=="linux"', {
#                    'include_dirs': [
#                        '/usr/include'
#                        ],
#                    'link_settings': {
#                        'library_dirs': ['/usr/share/lib']
#                    },
#                    'cflags!': ['-fno-exceptions'],
#                    'cflags_cc!': ['-fno-rtti', '-fno-exceptions']
#                }],
#                ['OS=="mac"', {
#                    'include_dirs': [
#                        '/opt/local/include'
#                        ],
#                    'link_settings': {
#                        'library_dirs': ['/opt/local/lib']
#                    },
#                    'xcode_settings': {
#                        'MACOSX_DEPLOYMENT_TARGET' : '10.7',
#                        'OTHER_CFLAGS': [
#                            "-mmacosx-version-min=10.7",
#                            "-std=c++11",
#                            "-stdlib=libc++"
#                        ],
#                        'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
#                        'GCC_ENABLE_CPP_RTTI': 'YES'
#                    }
#                }]
#            ]
    }
    ]
}