# 3081 Lab01 GitHub Basics

## What You Will Learn
1. Basic Linux commands, for example _mkdir_, _cd_, _mv_, and _ls_.
1. How to configure github for your cselabs account.
2. How to _clone_ (create a local copy of an existing repo), _pull_ (get updates), and _push_ (make updates).
3. How to configure the _.gitignore_ file so that _push_ ignores files not necessary to track.
4. The required directory structure and file nomenclature for course assignments.
5. How to initiate and read automated testing of course assignments.

_For additional information about Linux, see http://www-users.cs.umn.edu/~larson/repo-website-resources/website/examples/csresources/linux.html_

### Configuring GitHub

Below, a number of commands are shown that should be typed into the command line. These are preceded by a percent sign "%" which is NOT to be typed in.

Log into your cselabs account.

`% git --version` This will establish if it is installed.
```
% git config --global user.name << "your name" >>
% git config --global user.email << your email address >>
% git config --global core.editor << your editor choice here >>.
```

Note that your name appears between double quotes since it has spaces in it. Your email address doesn't, so it doesn't need to be in quotes. If you would like `emacs -nw` as your editor (emacs such that it doesn't open a new window but opens in the terminal) then you'll want double quotes around that 2 word phrase. Also note that if you want to use gedit, you probably need to use `gedit -w -s`.

`% git config --list` to see that Git has set this up correctly.

### Cloning the Read-Only 3081 Course Repository

Computer Science courses are setup for github by first establishing a GitHub organization (e.g. _umn-csci-watters-3081F17_), which contains a repository for each student, as well as a read-only course repository (e.g. _public-class-repo_). Course materials will be distributed via the read-only repository.
 < and >
> It is probably a good idea to copy any content you will be using from the class repository, into your individual workspace. This is because as we add content, it might cause merge conflicts with files that you added. Keep in mind that the way that github is used in a class is very different from how you would use it at work. You would never have 150 people at work writing the same exact code and then trying to hide it from each other. As the semester progresses, we will point out some ways in which a repository for work differs from how it is used here.

At the top level of your cselabs account or within a directory of your choice, create a 3081 directory with any name you prefer, then move to that directory. You will clone both the class and individual repo into this directory.

```
% (optional) cd <location of your choosing>
% mkdir 3081_F17
% cd 3081_F17
% git clone https://github.umn.edu/umn-csci-watters-3081F17/public-class-repo
% ls
```

**_What just happened?_** You made a new directory (i.e. folder) in your account with `mkdir`. You changed that to your working directory with `cd`. You copied the class repo locally to your machine with `clone`. You listed the contents of the working directory with `ls`, which should list the newly created directory with the name of the repository which it contains. These directories function exactly like all other linux directories. There are hidden files that track changes to the repository.

### Cloning and Configuring Your Student Course Repository

Follow the same process and clone your individual repository.

```
% git clone https://github.umn.edu/umn-csci-watters-3081F17/repo-<userID>
```

Next, move the source code for lab01 from the class repo to your individual repo. Where it has _\<userID\>_, you **replace with your UMN userID**, e.g. _watt0087_, without the "<" and ">" symbols.

```
% cd repo-<userID>
$ ls -a
```
**_What just happened?_** You made your class repo the working directory with `cd`. You displayed (i.e. listed) the contents of the working directory with `ls`, including all hidden files with `-a`. Notice the directory _.git_, which is how files are tracked. This is contained at the top level of the repository. If you want to look inside that directory type `% ls .git`.

> It is **very important** that you never modify, delete, or move this directory, AND never copy it from one repo to another, as that will really mess things up.

```
% mkdir labs
% cp -r ../public-class-repo/lab01 labs/.
% ls -a
```
**_What just happened?_** You created a new directory with `mkdir` that will contain folders with all labs for this course. You copied the entire directory (i.e. folder) _lab01_ contained in the class repo into the _labs_ directory of your individual repo, maintaining the name _lab01_ with the use of `labs/.`. Notice the `../class-repo-public`. The `..` means to navigate up one level in the directory structure. The single `.` means look inside the current directory. The list of content for this directory does not contain the _.git_ directory.

### Executing Lab Code and Pushing Results

The code provided for lab01 will create an executable by compiling the provided C++ files using a _makefile_. Running the executable will generate 2 files that will be added to your lab01 directory. A _makefile_ manages the compilation process, which will be explored further in next week's lab.

```
% cd labs/lab01
% make
% ls
```

**_What just happened?_** You made _lab01_ your working directory with `cd`. You executed the makefile (named _makefile_) with `make`, which created object files with the extension _.o_, and the executable _lab01.out_. These files are displayed with `ls`.

```
% ./lab01.out
% ls
```
**_What just happened?_** You ran the executable with `./lab01.out`, which generated 2 files _private.pvt_ and _shared.md_. In the next part of this lab, you will setup the _.gitignore_ file so that the former file is not added to the repo, but the latter is.

Before telling git what not to track, look at what it has been tracking.

```
% git status
```

You will see the directories and files that have been added to this repository.

### Configuring and Using _.gitignore_

There are a lot of files that should not be tracked in the repository. You typically don't want object and executable files included in your repo, because these are consequences of the local compilation. There are common files or libraries that should not be included, because it is wasteful to have multiple copies and to spend bandwidth moving them around. There might also be files that are for you only, such as notes about the project or todo lists. The _.gitignore_ file stores file extensions that serve as a filter for git. Any file with that extension will not be tracked.

Navigate back to the top level of your individual repository, confirmiing you are in the right place.

```
% cd ../..
% pwd
```

If you are in the right place, using your favorite text editor, create a .gitignore file, e.g. `xemacs .gitignore &`, which will open xemacs in a new window. Edit the .gitignore file to remove your executable and build folders.

Add these lines to the file:
```
# Extensions to not include in repo
*.o
*.out
*.pvt
```

Save the file.

**What just happened?** You added a comment by prefacing the first line with `#`. You indicated to not track any and all files with the use of `*` that has a specific file extension (e.g. `*.o`). If you have a one-off, you can include that specific file. You can also add a directory name, which will ignore all contents of the directory.

Look at the results:
```
% git status
```

Now you will see that the indicated files in _.gitignore_ are no longer tracked.

### Add Changes to Repo both Locally and on the Server

You need to _stage_ all changes to the repository, which prepares those items to be permanently part of the repository. When you _commit_ those changes, they are saved to your local repository, which lives in your cselabs account (or your personal computer if that is what you are working on). When you _push_ those changes, they will be copied to the repo on the server.

```
% git add *
% git commit -m "Adding lab01 results."
% git push
```

**What just happened?** All of the tracked changes were stages with `git add *`. You could have only staged certain files by replacing _*_ with the filename. Note that `add` does not mean you are adding a new file or a new directory, it means you are adding a change (any change). Those staged changes were committed to your local repository and tagged with the message that follows `-m`, then pushed to the server.

>Always use good comments in the commit. If you need to restore a previous state of the repo that is several commits back, you will have a much easier time figuring out which commit is relevant when you use comments like _"adding robot class definition"_, as opposed to _"more class stuff"_.

>Always verify that the changes have been uploaded to the server by looking at the repo through the web interface of github.

### Reading the Feedback

Pushing to the server triggers the automated grading system. Soon your repo will contain a feedback file, letting you know if you have passed all tests of the assignment. These tests will make sure you have the right directory structure, filenames, and that everything is behaving as indicated in the requirements.

Watch your github account via the web interface to see when the feedback file is ready (hit refresh to check contents). You can look at it through the web, but it is important to pull in that file to your local repo, so as not to cause merge conflicts.

```
% git pull
% cd labs/lab01
% ls
```

> ALWAYS, ALWAYS, ALWAYS perform a _pull_ before making changes to a repository. Each time you sit down to work on a lab or project iteration, it would be an excellent habit to perform a _pull_ on both the class repo and your individual repo.

THIS LAB IS COMPLETE.

Congratulations!
