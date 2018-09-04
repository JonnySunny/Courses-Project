# Google Style Guide Compliance

**REMEMBER TO SIGN IN TODAY!!!**

https://google.github.io/styleguide/cppguide.html

A style guide sets guidelines for how files, classes, functions, and variables
should be named. It also sets guidelines for white space, line lengths, and
commenting within the code. By standardizing naming conventions and layout, it
is easier to integrate code from various programmers in a cohesive way that
is readable and understandable by everyone. Going forward, all code submitted
for this course must be compliant with the Google Style Guide. As stated before,
not everyone is going to agree on every Style aesthetically, but it is important to have
a standard that everyone programs to.

As stated in the email, the code was recently modified to fix most of the issues
related to non-compliance. If you have not done so, you will want to clone the
latest version from the class repo and copy it into your personal repo,
overwriting the previous one.

To fix the errors, you will first need to identify them with cpplint. The
cpplint.py file has been provided in the repo for convenience, but you can
get it direct from the repository: https://github.com/google/styleguide. If you are working on your own machine, it
is recommended that you install pip3 if not installed, then install it with

```
pip3 install cpplint
```

On the cselabs machines, you call the file directly. Place the 'cpplint.py' file
somewhere convenient to reference. For example, you might put it in your home
directory. Then you pass it a file or collection of files. For example, if
the cpplint file is in `~` and it is being called from the `iteration1` folder,
the following command will check all `.cc` and `.h` files in src.

```
~/cpplint.py src/*.cc src/*.h
```

You should get a report of all of the errors that includes the file, line
number, and a short description of the problem. If you need guidance in what
is expected, you can consult the Style Guide:
https://google.github.io/styleguide/cppguide.html. Notice that the errors range
from the placement of braces to the use of the keyword `explicit` to commenting.

There is one issue that arises with the header guards. With the above call to
`cpplint`, the header guard needs the full path prefix of
`PROJECT_ITERATION1_SRC`, but if you use this command instead:

```
~/cpplint.py --repository=. src/*.cc src/*.h
```

the header guard should not have `PROJECT_ITERATION1` in the prefix. To change
this, open up one of the files in atom and the whole project will load. Select
the pulldown menu option "Find in Project" under "Find".

```
Find: PROJECT_ITERATION1_SRC
Replace with: SRC
```
for a quick universal change throughout the code.

As part of assessment, all files will be run through cpplint.
