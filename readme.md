# Properties Management

> <strong><big><green>This is a class work for C course of NEU.<green></big></strong>

## project framework(for example)
```mermaid
graph LR
A["Base Type"] --> B["Database Operate"]
A --> C["resident"]
A --> D["worker"]
A --> E["admin"]
B --> C
B --> D
B --> E
C --> F["Business"]
D --> F
E --> F
F --> H["main"]
G["UI"] --> H
``` 
#### Base Type
It should include some commonly used data structures, such as string, list, stack, deque and others.  
All of structures(except str) should get a sizeof the detail data struct, and is should return a void pointer.  
The void pointer should be change to the data on its own, then be read and operated.  
#### DateBase Operate  
This is a module for operating databases.  
We assume that the data to be stored is always of string type.  
It should support basic CRUD operations(Create, Read, Update, Delete), as well as any other operations deemed necessary.  
#### resident, worker, admin  
Abstract business of the project.
#### Business  
Specific business of the project.
#### UI  
a UI module. 


## coding standard  
The code should strive for beauty and elegance indirectly.  
#### naming variables/types/functions
Variables are generally named using one or two nouns connected by underlines.  
Types are typically expressed using one or two nouns as well as variables.  
Functions are usually composed of three words, in two forms:  
1. noun+verb+noun, like `list_getitem`  
2. verb+prep+noun, like `sort_by_username`  

_names should be simple and understandable with uniqueness, and repetition is not recommended_

#### indentation
Indentation should be done using 4 spaces instead of one tab.  
Reason: spaces have a consistent width of one character on all devices, while tabs depend on platform implementation. 

#### braces and code blocks
The left brace should direcly follow control statements or the defination of function.  
The right brace should be one the same indentationlevel as the corresponding statement.  
Indent inside the code block by adding 4 spaces.
For example:
```C
int max(int one, int two){
    if( one > two ){
        return one;
    } else {
        return two;
    }
}
```

## commit standard
The commit message should be written as the format below:
```
<type>: <description>
```
#### type
The `<type>` should be one of the following:
- feat: a new feature
- fix: a bug fix
- docs: documentation only changes
- style: changes that do not affect the meaning of the code (white-space, formatting, missing semi-colons, etc)
- refactor: a code change that neither fixes a bug nor adds a feature
- perf: a code change that improves performance
- chore: changes to the build process or auxiliary tools and libraries such as documentation generation
- revert: revert to a commit
- merge: merge branch
#### description
The `<description>` should be a short, concise description of the changes made.  
It should be written by Chinese or English, and the Chinese description is recommended.

## development standard
The development should be done in the branch `develop`, and the developing branch should be merged into `master` every day.  
The branch `master` should be the latest stable version of the project.