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
All structures(except str) should get a sizeof the detail data struct, and it should return a void pointer.  
The void pointer should be changed to the data on its own, then be read and operated.  
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

## Our work flowchart

```mermaid
graph LR
start --> login
login --> verify{username&password} 
verify -->|admin| admin
verify --> |residents| residents
verify --> |workers| workers
verify --> |fail| login

admin --> admin_main
admin_main --> work_select1{work_select}
admin_main --> password_maintain1
admin_main --> password_change1
work_select1 --> |to_residents| residents_manage
work_select1 --> |to_workers| worker_manage
work_select1 --> |to_fee| fee
work_select1 --> |to_data| data
data --> backup
data --> restore
residents_manage --> repair_request
residents_manage --> add_resident
residents_manage --> remove_resident
residents_manage --> inquire_resident
fee --> select
fee --> sort
fee --> to_singal
select --> List_of_unpaid
select --> List_of_paid_overtime
sort --> sort_by_name
sort --> sort_by_lastest_paytime
to_singal --> bil
to_singal --> Paid_overtime
to_singal --> unpaid
worker_manage --> work_assignments
worker_manage --> add_worker
worker_manage --> remove_worker
work_assignments --> repair
work_assignments --> clean
work_assignments --> remind_payment

workers --> worker_main
worker_main --> inquire_work
worker_main --> sort2
worker_main --> count_work
worker_main --> complete_work
worker_main --> password_change2
worker_main --> password_maintain2
inquire_work --> region
inquire_work --> content

residents -->  residents_main
residents_main --> fee1
residents_main --> problem_report
residents_main --> inquire
residents_main --> password_change3
residents_main --> password_maintain3
fee1 --> unpaid_bills
fee1 --> paid_overtime
fee1 --> pay
fee1 --> history1
history1 --> sort3
history1 --> select2
history1 --> count1
problem_report --> add_problem
problem_report --> view_problem
problem_report --> history2
history2 --> sort4
history2 --> select3
history2 --> count2
inquire --> workers_list
inquire --> fee_standard

bill_include_id_time_username_money
```

## User data content


```mermaid
graph LR
A[["admin"]]
A --> A1(role: admin)
A --> A2(username/password)

B[[workers]]
B ---> B1(role: workers)
B ---> B2(username/password)
B --> B3(work regions)
B --> B4(patrol route)
B --> B5(shift time)

C[[residents]]
C ---> C1(role: residents)
C ---> C2(username/password)
C --> C3(name)
C --> C4(gender)
C --> C5(address)
C --> C6(phone number)
C --> C7(fee record:link list)
C --> C8(servant)
C --> C9(region)
C --> C10(parking space)
C --> C11(problem list)
C7 --> c1(fee times)
C7 --> c2(owe fee times)
C7 --> c4(trade ID)
C7 --> c3(pointers)
```

need an analysis function to change some statues(fee or not) in database

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
The left brace should directly follow control statements or the definition of function.  
The right brace should be one of the same indentation level as the corresponding statement.  
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
- style: changes that do not affect the meaning of the code (white-space, formatting, missing semicolons, etc.)
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