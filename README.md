# Arbitrary Precision Calculator (APC)

A command-line calculator in **C** that performs arithmetic on numbers of **any length**, far beyond the range of `int` or `long long`. Each number is stored digit by digit in a **doubly linked list**, and every operation is done the way it is done on paper.

> Built by **Tharis Selvaraj**

---

## Features

- Addition, subtraction, multiplication and division of very large numbers
- Negative results in subtraction (e.g. `33 - 55 = -22`)
- Works from the command line, then lets you continue with new input
- Memory of every list is freed after each calculation

## How it works

Each digit of a number is a node in a doubly linked list:

```
head -> 1 <-> 2 <-> 3 <-> 4 <-> 5 <- tail
```

| Operation | Method |
|---|---|
| **Addition** | Add digit by digit from the **tail**, carrying to the next digit. |
| **Subtraction** | Make sure the bigger number is on top (swap if needed), subtract digit by digit with **borrow**, remove the starting zeros, and make the first digit negative if the answer is negative. |
| **Multiplication** | Multiply the 2nd number's digits one at a time with the 1st number, shift each row with zeros (`count`), and **add** the rows together. |
| **Division** | Take one digit at a time into a remainder list. While `rem >= divisor`, **subtract** the divisor and increment `count`. The `count` for each step becomes one digit of the quotient. Starting zeros are removed at the end. |

## Project structure

```
.
├── apc.h               # Structure, macros and function prototypes
├── main.c              # Input handling, operator selection and the continue loop
├── insert.c            # dl_insert_first / dl_insert_last
├── print.c             # print_list / print_result
├── addition.c          # Addition
├── subtraction.c       # Subtraction
├── multiplication.c    # Multiplication
├── division.c          # Division
└── screenshots/        # Sample outputs
```

## Build

```bash
gcc *.c
```

## Usage

```bash
./a.out <number1> <operator> <number2>
```

| Operator | Operation |
|---|---|
| `+` | Addition |
| `-` | Subtraction |
| `x` | Multiplication |
| `/` | Division |

After the result, the program asks **Do you want to continue? (y/n)**. Choosing `y` reboots the calculator and asks for new input; choosing `n` exits.

### Examples

```bash
./a.out 12345678234678456789 + 2346789234567
./a.out 2345678975315656886 - 12345678567891234567678902345678
./a.out 23456788942675567 x 234567890753123456000000
./a.out 34567834567875396 / 234567842
```

---

## Sample Output

### Addition
```
12345678234678456789 + 2346789234567 = 12345680581467691356
```
![Addition](screenshots/addition.png)

### Subtraction
```
2345678975315656886 - 12345678567891234567678902345678 = -12345678567888888888703586688792
```
![Subtraction](screenshots/subtraction.png)

### Multiplication
```
23456788942675567 x 234567890753123456000000 = 5502209506124596660914038905799552000000
```
![Multiplication](screenshots/multiplication.png)

### Division
```
34567834567875396 / 234567842 = 147368174
```
![Division](screenshots/division.png)

---

## Limitations

- Only non-negative whole numbers are accepted as input.
- Division returns the **quotient** only (no remainder or decimals).
- Division by zero prints an error message.

## Author

**Tharis Selvaraj**
