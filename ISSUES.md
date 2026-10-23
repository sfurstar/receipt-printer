# Issue Log — OriginalReceiptPrinter.cpp

Line numbers refer to `src/OriginalReceiptPrinter.cpp` as first committed.

## Issues

| # | Issue | Line(s) | How to reproduce | Concept | Status |
|---|---|---|---|---|---|
| 1 | First letter of the first customer's name is dropped; answering `yes` garbles the next name | 20 | Enter `steven` → "teven". Answer `yes` to another customer, then `Maria` → "s" | `cin.ignore()` vs `cin >> ws` | Fix proposed (FIX-01) |
| 2 | Later receipts also list earlier customers' items | 13, 164 | Serve two customers | Variable scope / resetting state | Open |
| 3 | A letter at "Quantity:" loops forever | 138–141 | Enter `abc` | `cin` fail state | Open |
| 4 | `y` at "Member?" skips the tip, the note and the next customer | 170–172 | Enter `y` | `cin` fail state; `bool` input | Fix proposed (FIX-01) |
| 5 | Cashier note is read but never printed | 219–222 | Enter a note, check the receipt | Unused data | Open |
| 6 | Inventory can go negative | 143–156 | Order 150 waters | Input validation | Open |
| 7 | Tax lines don't add up to Total Tax | 183–186 | Order one small water ($1.00) | Rounding money | Open |
| 8 | Lowercase choices rejected | 53, 61 | Enter `w` | `toupper()` | Fix proposed (FIX-01) |
| 9 | Whole words accepted; receipt shows "(Large)" | 35–36, 53, 164 | Enter `Water`, then `Large` | `string` vs `char` | Fix proposed (FIX-01) |
| 10 | Negative tip accepted | 209–211 | Option 4, enter `-5` | Input validation | Open |
| 11 | Menu prices typed into the code and also stored in the file | 26–29 | Edit `Lab_Menu.txt`; the printed menu doesn't change | One source of truth | Open |
| 12 | Menu file reopened for every item | 66–67 | Read the code | Do work once | Open |
| 13 | Missing menu file leads to a garbage price | 134–136 | Rename `Lab_Menu.txt` | Uninitialized variables | Open |
| 14 | `item_code` set but never used | 41 | Compiler warning | Dead code | Open |
| 15 | No `$` on Subtotal / Discount / After Discount | 228–230 | Look at a receipt | Consistent formatting | Open |
| 16 | Discount prints as a positive number | 229 | Order as a member | Formatting | Open |
| 17 | Audit table misaligned | 266–273 | End-of-day audit | `setw` widths | Open |
| 18 | "Grand Total" prints on the same line as the Y/N question | 257–262 | Answer `N` | Output layout | Open |

## Proposed fixes

### FIX-01 — `get_choice()`: case-insensitive, validated single-letter input

**Fixes:** #1 (with the companion change below), #4, #8, #9, and `yes` at "another customer".
**Does not fix:** #3 and #10, which are number inputs and need a sister function such as `get_positive_int()`.

```cpp
// Asks for a single-letter choice. Accepts upper or lower case, and keeps
// asking until the user types exactly one of the letters in valid_choices.
char get_choice(string prompt, string valid_choices) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin >> ws, input);                 // read the whole line they typed
        if (input.length() == 1) {                 // must be exactly one character
            char choice = toupper(input[0]);       // w -> W
            if (valid_choices.find(choice) != string::npos) {
                return choice;                     // valid: hand it back
            }
        }
        cout << "Invalid choice. Please enter one of: " << valid_choices << endl;
    }
}
```

**Use it at:**

| Prompt | Replaces lines | New code |
|---|---|---|
| Item | 51–56 | `item_choice = get_choice("Please make an item selection: ", "WSCTX");` |
| Size | 59–64 | `size_choice = get_choice("Please select a size (S/M/L): ", "SML");` |
| Member | 170–172 | `bool member = (get_choice("Member? (Y/N): ", "YN") == 'Y');` |
| Another customer | 257–258 | `continue_choice = get_choice("Would you like to process another customer? (Y/N): ", "YN");` |

**Changes that go with it:**

1. Lines 35–36: `string item_choice; string size_choice;` become `char`, and every `item_choice[0]` / `size_choice[0]` becomes `item_choice` / `size_choice`.
2. Line 260: the loop condition can become `while (continue_choice == 'Y')`.
3. **Required:** delete `cin.ignore();` on line 20 and change line 21 to `getline(cin >> ws, CustomerName);`. `get_choice` now removes the newline, so a leftover `cin.ignore()` would eat the first letter of **every** customer's name.

**Optional:** the tip menu can use `get_choice(..., "1234")`, since `toupper` leaves digits alone. The `case 1:` labels then become `case '1':`.

**Tested:**

| Typed | Result |
|---|---|
| `water` at item | Rejected, asked again |
| `w` | Accepted as Water |
| `large` at size | Rejected; `m` accepted |
| `x` | Checked out |
| `yes` at Member | Rejected; `y` accepted, 10% discount applied |
| `nope` at another customer | Rejected; `Y` accepted |
| Names `steven`, `Maria` | Stored correctly |
