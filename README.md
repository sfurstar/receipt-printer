# Receipt Printer

Comp Sci lab: a drink-stand register that takes orders, applies a member discount,
Arkansas/Faulkner/Conway taxes and a tip, prints a receipt (screen + `receipt.txt`),
and ends the day with a grand total and inventory audit.

## Layout

```
receipt-printer/
├── .vscode/                     # build, run and debug config for VS Code
├── src/
│   ├── OriginalReceiptPrinter.cpp   # working version (everything in main)
│   └── ReceiptPrinter.cpp           # in-progress refactor into functions (does not compile yet)
├── Lab_Menu.txt                 # menu data read at runtime (must sit in the folder you run from)
├── .gitignore
└── README.md
```

## Run it

- **F5** in VS Code → builds `src/OriginalReceiptPrinter.cpp` and runs it in the terminal panel.
- **Cmd+Shift+B** → build only.
- Terminal: `clang++ -std=c++17 -Wall -g src/OriginalReceiptPrinter.cpp -o build/receipt_printer && ./build/receipt_printer`

## Input tips (current behavior)

- **Name:** the first character typed is swallowed on the first customer (`cin.ignore()` before `getline`).
- **Item / size:** capital letters only (`W S C T X`, `S M L`).
- **Member?** enter `1` (yes) or `0` (no). Typing `y`/`n` breaks the rest of the input.
- **Tip:** `1`–`4`.
