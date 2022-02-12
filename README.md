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
- [**Shell**](https://gitlab.com/aiocat/virna/-/blob/main/example/vish/vish.vi)

## Usage

Clone the repository and compile program:

```sh
g++ virna.cpp -o virna
```

Add the executable file to the PATH. and:

- **Windows**:
  ```sh
  vir .\test\main g++
  ```
- **\*nix**:
  ```sh
  vir ./test/main g++
  ```

Second argument can be changed. Ex: if you want to use clang:

```sh
vir ./test/main clang++
```

## Docker
- `cd virna`
- `docker build -t "virna:Dockerfile" .`
- `docker run --rm -i -t virna:Dockerfile`

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

Writing numbers as hexadecimal also valid:

```virna
in main
    # Same program with hexadecimal numbers #

    0x64 0x1e +
    0 ret
end
```

### Chars

Characters are actually are not characters. They are converted to the number, so it's more like a syntax-sugar.

```virna
in main
    'b' '+' 'a' putc putc putc
    '\n' putc
    0 ret
end
```

`\n`, `\r`, `\t` and `\'` are supported.

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

### Arithmetic Operations

| Syntax | Description                                                                      |
| ------ | -------------------------------------------------------------------------------- |
| +      | Sums up two elements on the top of the stack.                                    |
| -      | Substracts up two elements on the top of the stack.                              |
| \*     | Multiples up two elements on the top of the stack.                               |
| %      | Mods up two elements on the top of the stack.                                    |
| dimo   | Divides up two elements on the top of the stack and returns both result and mod. |

### Bitwise Operations

| Syntax | Description  |
| ------ | ------------ |
| >>     | Right shift. |
| <<     | Left shift.  |
| \|     | Bitwise OR.  |
| &      | Bitwise AND. |
| ^      | Bitwise XOR. |
| ~      | Bitwise NOT. |

### Stack Manipulation

| Syntax  | Description                                                                                                                    |
| ------- | ------------------------------------------------------------------------------------------------------------------------------ |
| dup     | Duplicate a number on the top of the stack.                                                                                    |
| dups    | Duplicate a string on the top of the stack.                                                                                    |
| swap    | Swaps two number on the top of the stack.                                                                                      |
| swaps   | Swaps two string on the top of the stack.                                                                                      |
| pop     | Pops a number on the top of the stack.                                                                                         |
| pops    | Pops a string on the top of the stack.                                                                                         |
| trns    | Pushes the string on top of the stack to the number stack. (C Style)                                                           |
| lens    | Calculates length of the string on the top of the stack and pushes to the number stack.                                        |
| revs    | Reverses the string on the top of the stack.                                                                                   |
| neg     | Converts the number on the top of the stack to the negative number.                                                            |
| put     | Print the number on the top of the stack and pop it.                                                                           |
| puts    | Print the string on the top of the stack and pop it.                                                                           |
| putc    | Print the number as character on the top of the stack and pop it.                                                              |
| get     | Gets number from CLI and pushes to the stack                                                                                   |
| gets    | Gets string from CLI and pushes to the stack                                                                                   |
| getch   | Gets a character from CLI and pushes to the stack. (this function works same with `int getch(void)`, not waits for enter key.) |
| ret     | Returns the number on the top of the stack.                                                                                    |
| appendc | Gets the number on the top of the stack and pushes number as a character to string on the top of the stack.                    |
| ++      | Concats the two string on the top of the stack.                                                                                |
| size    | Gets number stack size and pushes to the top of the number stack.                                                              |
| sizes   | Gets string stack size and pushes to the top of the number stack.                                                              |
| emp     | Checks if number stack is empty and pushes the result to the number stack. (`1` if it is, `0` if it isn't)                     |
| emps    | Checks if string stack is empty and pushes the result to the number stack. (`1` if it is, `0` if it isn't)                     |

### Comparison

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
| fetch  | Fetches the variable and pushes to the top of the number stack.    |

Example:

```virna
in main
    let test # Create variable with 0 #
    2 3 # Push two values on the top of the stack #
    set test # Test is now 3. and the stack is [2] #

    fetch test # Push test's value on the top of the stack #
    # Stack is now [2, 3] #
    # Variable is 3 #
    0 ret
end
```

### String Variables

| Syntax | Description                                                        |
| ------ | ------------------------------------------------------------------ |
| lets   | Create a new variable with default value. ("")                     |
| sets   | Change the variable value with string on top of the stack and pop. |
| fetchs | Fetches the variable and pushes to the top of the string stack.    |

Example:

```virna
in main
    lets test # Create variable with "" #
    "Hello" # Push string on the top of the stack #
    sets test # Test is now ,"Hello". and the stack is [] #

    fetchs test # Push test's value on the top of the stack #
    # Stack is now "Hello" #
    # Variable is still "Hello" #
    0 ret
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

This program writes `25` to the console output.

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

### CImport

`cimport` is a keyword that allows to including c/c++ library to the virna easily.

```virna
cimport "stdio.h"

in main
    10

    let temp
    set temp

    `printf("%d\n", temp+10);`
    0 ret
end
```

### System

`readf` and `writef` returns `1` if success, `0` if it isn't.

`shell` returns the program exit number. (`0` if success)

| Syntax | Description                                                                                                                             |
| ------ | --------------------------------------------------------------------------------------------------------------------------------------- |
| readf  | Reads the file on top of the string stack and pushes the body to the string stack and pushes the result on the top of the number stack. |
| writef | Writes to the file on top of the string stack and pushes the result on the top of the number stack.                                     |
| shell  | Executes the command on top of the string stack and pushes the result on the top of the number stack.                                   |
| sleep  | Waits for x second (x = the number on the top of the stack)                                                                             |
| rand   | Generates pseudo-random number with current time.                                                                                       |
| write  | Wrapper for write syscall.                                                                                                              |

**Example** `readf`:

```virna
in main
    "test.txt" readf

    if
        puts
    end

    0 ret
end
```

**Example** `writef`:

```virna
in main
    "content" "test.txt" writef

    if
        "Success" puts
    end

    0 ret
end
```

**Example** `shell`:

```virna
in main
    "mkdir test" shell

    0 = if
        "Success" puts
    end

    0 ret
end
```

**Example** `write`:

```virna
in main
    1 "standart output\n" write
    2 "an stderr ex\n" write
    0 ret
end
```

**Example** `rand`:

```virna
in main
    100 10 rand # Random between [10..100] #
    put
    0 ret
end
```

#### Syscall

You can use `syscall` block that invokes the system call whose assembly language interface has the specified number with the specified arguments. Example:

```virna
in main
    # Syscall (Linux) #
    syscall
        # Syscall (write in this case) #
        0x1

        # Args... #
        1
        "hello world\n"
        12
    syscall

    0 ret
end
```

Or, more automated version

```virna
in main
    "Hello, World!\n" dups lens
    lets buf
    sets buf

    let bug_length
    set bug_length

    # Syscall (Linux) #
    syscall
        # Syscall (write in this case) #
        0x1

        # Args... #
        1
        fetchs buf
        fetch bug_length
    syscall

    0 ret
end
```

This program writes `hello world` to the console output. Syscall block is only supports `number`, `string` and `variables` and you can't use any virna command inside `syscall` block.

### Control Flow

#### If-Else

If block will be executed if the number of the top of the stack is `1`. Else, it executes the else block if block exists.

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

#### Try-Catch-Err

`catch` also handles standart errors in C++.

```virna
in main
    try
        "What is your age: " puts get

        18 < if
            err
        end

        "You can drink!" puts
    catch
        "You can't drink." puts
    end
end
```

#### While Loop

| Syntax | Description                           |
| ------ | ------------------------------------- |
| skip   | Skip the loop. (same with `continue`) |
| break  | Break the loop without waiting.       |

While loop continues until the number of the top of the stack is `0`.

```virna
in main
    5 while
        1 - dup put
    end

    0 ret
end
```

#### Repeat Loop

`repeat` keyword fetches the number on the top of the stack and repeats the code.

```virna
in main
    5 repeat
        65 putc
    end
end
```

this program prints `A` 5 times.

#### Forever Loop

I don't think i need to describe this. Continues until forever...

```virna
in main
    "Pushin' " puts
    forever
        80 putc
    end
end
```

### Meta Programming

Virna allows to access tokens in program.

- [Token Enum](https://gitlab.com/aiocat/virna/-/blob/main/lexer.cpp#L5)

```virna
in main
    quote
        10 put
    quote

    2 repeat
        put # Token Key #
        " => " puts
        puts # Token Value #
        10 putc # New Line #
    end
end
```

### Labels

Virna has labels to make your job easier.

| Syntax | Description         |
| ------ | ------------------- |
| label  | Create a new label. |
| jump   | Jump to the label.  |

```virna
# Program starts here: #
in main
    2

    # New label #
    label test

    "Hello World\n" puts
    1 -

    dup 0 = if
        0 ret
    else
        # Jump to label #
        jump test
    end
end
```

### Inline-C++

You can use C++ (without limitation) in virna source code.

```virna
import "../std/math.vi"

`int c_add(int a, int b) {
    return a + b;
}`

# Program starts here: #
in main
    5 10
    let test1
    let test2

    set test1
    set test2

    `std::cout << c_add(test1, test2) << "\n";`
    5 factorial
    put

    0 ret
end
```

### Types in Virna

- `number`: 4 bytes number.
- `string`: string (`std::string`).

## License

Virna is distributed under MIT license. for more information:

- https://gitlab.com/aiocat/virna/-/blob/main/LICENSE
