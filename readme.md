My attempt at solving various competitive programming problems.

---

## Set up your C++ environment

1.  Download GCC based on your OS:

    - macOS: `brew install gcc`

2.  Create or edit `.vscode/c_cpp_properties.json` to contain roughly the following:

    ```json
    {
      "configurations": [
        {
          "name": "<anything meaningful>",
          "includePath": ["${default}"],
          "defines": ["LOCAL=1", "DEBUG=1"],
          "compilerPath": "<path to installed GNU g++>",
          "cStandard": "c23",
          "cppStandard": "c++23",
          "intelliSenseMode": "<based on your OS>"
        }
      ],
      "version": 4
    }
    ```
