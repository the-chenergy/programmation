My attempt at solving various competitive programming problems.

---

## Set up your C++ environment

1.  Download GNU GCC based on your OS:

    - macOS: `brew install gcc`

2.  Create or edit `.vscode/c_cpp_properties.json` to contain roughly the following:

    ```json
    {
      "configurations": [
        {
          "name": "<anything meaningful>",
          "includePath": ["${default}"],
          "defines": [],
          "compilerPath": "<path to installed GNU g++>",
          "cStandard": "gnu17",
          "cppStandard": "gnu++17",
          "intelliSenseMode": "<your os>-gcc-arm64"
        }
      ],
      "version": 4
    }
    ```
