#21sh

21sh is a project at 42 US

Objectives:
  Reimplement a Unix shell from scratch
  Understand how to fork and wait for processes
  Manage and execute successfully from the bin
  recreate system builtins:
    env
    cd
    echo
    unsetenv
    setenv
    
Supports
   cd -
   cd
   cd ~
   echo $ANYVAR

Redirections include
>> WORKING
> WORKING
< TODO: Check if file exists
<< TODO: Actually fix the hear doc
| TODO: have echo env sent correctly

Features:
line editing
history traversal
editable history
shift arrow key skip to next word


Supports: ; "
