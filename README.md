**VIRNA IS STILL UNDER-DEVELOPMENT. PLEASE USE AT YOUR OWN RISK!**

# Virna

A programming language designed to be stack-based and concatenative with reverse polish notation.

## Compiler

The compiler is built with C++. Also you can use **vir** for better experience.

## Example(s)

- **Hello World**:
  ```virna
  in main
      "Hello, World\n" puts
  end
  ```
- [**Brainfuck Compiler**](https://gitlab.com/aiocat/virna/-/blob/main/example/brainfuck/brainfuck.vi)

## Usage

Clone the repository and compile program:

```sh
g++ virna.cpp -o virna
```

- **Windows**:
  ```sh
  .\vir.bat .\test\main g++
  ```
- **\*nix**:
  ```sh
  ./vir.sh ./test/main g++
  ```
  Second argument can be changed. Ex: if you want to use clang:

```sh
./vir.sh ./test/main clang++
```

Virna => C++ => Executable

## About Stacks

Virna currently have 2 different stack. First one is for numbers, and the other is for strings.

## Language Reference

### Numbers

```virna
in main
    100 30 +
    0 ret
end
```

Pushes 100 and 30 to the stack and sums it.

```
Program Start  []
100            [100]
30             [100, 30]
+              [130]
```

### Strings

```virna
in main
    "Hello, " "World" ++
    0 ret
end
```

Pushes "Hello, " and "World" to the stack and concats it.

```
Program Start  []
"Hello, "      ["Hello, "]
"World"        ["Hello, ", "World"]
++             ["Hello, World"]
```

String escapes are same with C++.

### Stack Manupilation

#### Arithmetic Operations

| Syntax | Description                                                                      |
| ------ | -------------------------------------------------------------------------------- |
| +      | Sums up two elements on the top of the stack.                                    |
| -      | Substracts up two elements on the top of the stack.                              |
| \*     | Multiples up two elements on the top of the stack.                               |
| %      | Mods up two elements on the top of the stack.                                    |
| dimo   | Divides up two elements on the top of the stack and returns both result and mod. |

#### Bitwise Operations

| Syntax | Description  |
| ------ | ------------ |
| >>     | Right shift. |
| <<     | Left shift.  |
| \|     | Bitwise OR.  |
| &      | Bitwise AND. |
| ^      | Bitwise XOR. |
| ~      | Bitwise NOT. |

#### Stack Manipulation

| Syntax  | Description                                                                                                 |
| ------- | ----------------------------------------------------------------------------------------------------------- |
| dup     | Duplicate a number on the top of the stack.                                                                 |
| dups    | Duplicate a string on the top of the stack.                                                                 |
| swap    | Swaps two number on the top of the stack.                                                                   |
| swaps   | Swaps two string on the top of the stack.                                                                   |
| pop     | Pops a number on the top of the stack.                                                                      |
| pops    | Pops a string on the top of the stack.                                                                      |
| trns    | Pushes the string on top of the stack to the number stack. (C Style)                                        |
| lens    | Calculates length of the string on the top of the stack and pushes to the number stack.                     |
| revs    | Reverses the string on the top of the stack.                                                                |
| neg     | Convert the number on the top of the stack to the negative number.                                          |
| put     | Print the number on the top of the stack and pop it.                                                        |
| puts    | Print the string on the top of the stack and pop it.                                                        |
| putc    | Print the number as character on the top of the stack and pop it.                                           |
| ret     | Returns the number on the top of the stack.                                                                 |
| appendc | Gets the number on the top of the stack and pushes number as a character to string on the top of the stack. |
| ++      | Concats the two string on the top of the stack.                                                             |

#### Comparison

These commands will return `0` if it isn't, `1` if it is.

| Syntax | Description                                      |
| ------ | ------------------------------------------------ |
| >      | Compares the greater on top two number.          |
| <      | Compares the less on top two number.             |
| >=     | Compares the greater or equal on top two number. |
| <=     | Compares the less or equal on top two number.    |
| =      | Compares the equal on top two number.            |
| !      | Compares the not equal on top two number.        |
| eqs    | Compares the equal on top two string.            |

### Number Variables

| Syntax | Description                                                        |
| ------ | ------------------------------------------------------------------ |
| let    | Create a new variable with default value. (0)                      |
| set    | Change the variable value with number on top of the stack and pop. |

Example:

```virna
in main
    let test # Create variable with 0 #
    2 3 # Push two values on the top of the stack #
    set test # Test is now 3. and the stack is [2] #

    test # Push test's value on the top of the stack #
    # Stack is now [2, 3] #
    # Variable is 3 #
end
```

### String Variables

| Syntax | Description                                                        |
| ------ | ------------------------------------------------------------------ |
| lets   | Create a new variable with default value. ("")                     |
| sets   | Change the variable value with string on top of the stack and pop. |

Example:

```virna
in main
    lets test # Create variable with "" #
    "Hello" # Push string on the top of the stack #
    set test # Test is now ,"Hello". and the stack is [] #

    test # Push test's value on the top of the stack #
    # Stack is now "Hello" #
    # Variable is still "Hello" #
end
```

### Functions

Declaring a function:

```virna
in sqrt
    dup *
    0 ret
end
```

All functions must return value `0` or else, Program will exit with non-default value.

Using a function:

```virna
in sqrt
    dup *
    0 ret
end

in main
    5 sqrt
    put
    0 ret
end
```

This program will output `25`.

### Inline Functions

You can define a function as an inline function with `inline` keyword.

```virna
in sqrt inline
    dup *
    0 ret
end
```

### Import

You can import from another file with `import` keyword.

sqrt.vi

```virna
in sqrt inline
    dup *
    0 ret
end
```

main.vi

```virna
import "sqrt.vi"

in main
    5 sqrt put
    0 ret
end
```

### System

`readf` and `writef` will return `1` if success, `0` if it isn't.

`shell` will return the program exit number. (`0` if success)

| Syntax | Description                                                                                                                             |
| ------ | --------------------------------------------------------------------------------------------------------------------------------------- |
| readf  | Reads the file on top of the string stack and pushes the body to the string stack and pushes the result on the top of the number stack. |
| writef | Writes to the file on top of the string stack and pushes the result on the top of the number stack.                                     |
| shell  | Executes the command on top of the string stack and pushes the result on the top of the number stack.                                   |
| write  | Wrapper for write syscall.                                                                                                              |

**Example** `readf`:

```virna
in main
    "test.txt" readf

    if
        puts
    end
end
```

**Example** `writef`:

```virna
in main
    "content" "test.txt" writef

    if
        "Success" puts
    end
end
```

**Example** `shell`:

```virna
in main
    "mkdir test" shell

    0 = if
        "Success" puts
    end
end
```

**Example** `write`:

```virna
in main
    1 "standart output\n" write
    2 "an stderr ex\n" write
end
```

### Control Flow

### If-Else

If block will be executed if the number of the top of the stack is `1`. Else, it will execute the else block if exists.

```virna
in main
    5 4 > # Returns 1 #
    if
        "5 is greater than 4!" puts
    else
        # ... #
    end

    0 ret
end
```

### While Loop

| Syntax | Description                           |
| ------ | ------------------------------------- |
| skip   | Skip the loop. (same with `continue`) |
| break  | Break the loop without waiting.       |

While loop will be continue until the number of the top of the stack is `0`.

```virna
in main
    5 while
        1 - dup put
    end

    0 ret
end
```

## Types in Virna

- `number`: 4 bytes number.
- `string`: string (`std::string`).

## License

Virna is distributed under MIT license. for more information:

- https://gitlab.com/aiocat/virna/-/blob/main/LICENSE
