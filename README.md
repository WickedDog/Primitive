# Primitive
Primitive is a low-level scripting language and it is a little bit like asm, because it was easier to parse it that way

## Other
If you want to write the name of a variable and not just with a space, use ""

```asm
movstring "The Text" "Hello World!"
```

Comments

```asm
; comment
```
Further, below you will see that v1 or t1 will be written in the comments, v1 is a variable, and t1 is the value of a variable

## Actions with variables
Creating, setting a variable

```asm
movint variable 1 ; v1 t1
movints variable variable2 ; v1 v2
movfloat variable 1.0 ; v1 t1
movfloats variable variable2 ; v1 v2
movstring variable "one" ; v1 t1
movstrings variable variable2 ; v1 v2
```

Adding to a variable

```asm
addint variable 1 ; v1 t1
addints variable variable2 ; v1 v2
addfloat variable 1 ; v1 t1
addfloats variable variable2 ; v1 v2
addstring variable "one" ; v1 t1
addstring variable variable2 ; v1 v2
```

Subtract from the variable

```asm
subint variable 1 ; v1 t1
subints variable variable2 ; v1 v2
subfloat variable 1 ; v1 t1
subfloats variable variable2 ; v1 v2
```

Multiply a variable

```asm
mulint variable 1 ; v1 t1
mulints variable variable2 ; v1 v2
mulfloat variable 1 ; v1 t1
mulfloats variable variable2 ; v1 v2
```

Divide a variable

```asm
divint variable 1 ; v1 t1
divints variable variable2 ; v1 v2
divfloat variable 1 ; v1 t1
divfloats variable variable2 ; v1 v2
```

Deleting a variable

```asm
Release variable ; v1
```

## Marks (functions, cycle)
Mark declaration

```asm
mark mark_name ; v1
```

Closing the mark

```asm
end
```

Repeat mark

```asm
repeat mark_name ; v1
```

Breaking the cycle

```asm
break
```
## Logical operators
Equal

```asm
ifeint variable variable2 mark_name ; v1 v2 v3
ifefloat variable variable2 mark_name ; v1 v2 v3
ifestring variable variable2 mark_name ; v1 v2 v3
```


Bigger

```asm
ifbint variable variable2 mark_name ; v1 v2 v3
ifbfloat variable variable2 mark_name ; v1 v2 v3
```

Bigger or equal

```asm
ifebint variable variable2 mark_name ; v1 v2 v3
ifebfloat variable variable2 mark_name ; v1 v2 v3
```

Less

```asm
iflint variable variable2 mark_name ; v1 v2 v3
iflfloat variable variable2 mark_name ; v1 v2 v3
```

Less than or equal

```asm
ifelint variable variable2 mark_name ; v1 v2 v3
ifelfloat variable variable2 mark_name ; v1 v2 v3
```

Not equal

```asm
ifneint variable variable2 mark_name ; v1 v2 v3
ifnefloat variable variable2 mark_name ; v1 v2 v3
ifnestring variable variable2 mark_name ; v1 v2 v3
```

Else

```asm
else mark_name ; v1
```

## Cpp functions

```asm
callcpp function variable ; v1 v2
```

# Example

Repeating the cycle 1000 times
```asm
movint index 0
movint c 1000 

mark exit ; since logical operators can only call marks, we create a separate mark where there will be an exit from the loop
callcpp message index ; we call an external function from c++ called message and output the currency of the variable index
break
end

mark cycle ; 
addint index 1
ifeint index c exit ; if index is equal to c, then we will call the mark "exit"
end

repeat cycle ; repeat the mark "cycle"
```

# C++
## Creating the primitive class

```c++
PrimitiveFunctions primitive;
```

## Loading one line

```c++
primitive.loadLine("movint v1 0");
```

## Adding external functions

```c++
void message(std::string text) {
	std::cout << text << "\n";
}


primitive.loadFunction(message, "message");
```

## Adding a value to a variable
```c++
primitive.addVar("name", "text"); //the text will be translated to the variable type
```

## Getting the value of a variable
```c++
primitive.getVar("name");
```

## Using Scripts

```c++
primitive.useScript();
```

## Release Primitive

```c++
primitive.Release();
```
