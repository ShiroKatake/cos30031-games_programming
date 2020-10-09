# Post Mortem:

## **[2.2.0]** Sun Sep 27 2020
### About branching
* At the beginning I thought about doing branches for this repo. Each task was gonna be a branch of its own, but now I think it's too much for a project that's only maintained by a single person.
* It also doesn't help that when you merge the branches together, all the commit messages related to that branch is now in master, 
and messages like "ADD: Task specs" is too generic since they don't have task name to be easily identified (what task is this task specs for?) without having to go into the commit to see it.
* I'll have to be more specific with my commit messages if I were to do this in one master branch.

## **[5.30.1]** Thu Oct 1 2020
### Also include the template cpp file that I mess around with
* Cuz they show my messing around with the files, maybe it'd be better for showing my debugging skillz

## **[8.13.1]** Fri Oct 9 2020
### Add a `BUG` tag to show where I encounter problems
* This will go well with the `FIX` tag somewhere after
* Might also give it a number tag (ie. BUG #8.1 means bug number 1 for task 8)
* This will be followed by some sort of output code attached showing where the problem exists

## **[8.14.1]** Fri Oct 9 2020
### Use number # for commits
* Just realized as I hit commit that using a number system for commit messages would make version tracking a lot easier
* Commit messages will now be something like `ADD #8.15.1` which is the same as `pushing something to task 8 for the 15th time with 1 bug revision`
* `BUG` and `FIX` tag will also follow the same convention. When there's a new bug, the 3rd digit will increase by 1

## **[8.15.1]** Fri Oct 9 2020
### Have an output image to show more details
* A picture is worth a thousand words. If I have a bug, having this image updated to show that would help a lot. As I fix the issue, updating this image will also do a lot in giving context