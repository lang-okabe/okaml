# Okaml

OKAbe's Markup Language (or okaml for short) is a markup language. I made purely out of spite for markup languages that are indentation based.  

Here's a example of a syntax.

```okaml
name: okaml

somelist {
	has_key: true
	this_has: astringvalue
	sub_lists { 
		sub_sublists {
		isSubSub: yes
		foo: false
		}
	}
	bar: 123
	baz: 1204
}

multi_line: '''
this
is
multi_line
'''

isBad  : false
isNull : null
```

## Installation and Usage
This repo has a basic c parser to install it.  

```bash
git clone https://github.com/lang-okabe/okaml
cd okaml
gcc -o okaml main.c okaml.c
./okaml [okaml file]
```

## Usage
To include this parser in your c projects, you can import the header file
```c
#include okml.h

okml_array* data = okml_load("/path/foo.okml");
char* value = okml_find("key");
printf("%s", value);
```

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

[GPLv2](https://choosealicense.com/licenses/gpl-2.0//)
