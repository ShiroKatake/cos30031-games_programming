# 2020 Games Programming

## Who Am I?

* Name: Khang Gia Trinh
* ID: 102118468
* Email: 102118468@student.swin.edu.au

## Purpose

* This document contains rules and conventions for writing commit messages

## Committing rules
* Where possible, changes should be made in several small commits as it makes it
easy to find the steps in achieving those changes

## Commit Messages
### Use Tags

* ADD: Used for adding something new to the project (ie. New files, new code, etc.)
* FIX: Used for fixing bugs, broken features, tutor's suggestions, etc.
* UPDATE: Used for making changes on an existing file

### Writing conventions
The messages must be:
* A summary of 50 chars or less
* Written in imperative mood (ie. Add instead of Added)
* Has no period `.` at the end
* Be as specific as possible

### Examples:
```
5ba3db6 ADD: Ammo reload feature
```
```
e142fd1 FIX: Player vs Bullet collision detection
```
```
22b25e0 UPDATE: Increase Player HP from 80 to 90
```

## Release Notes
* Title must have version number and date

### Version numbering
Example version: x.y.z
* x: Major release (Task number)
* y: Minor release (Updates in that task)
* z: Fixes (Fixes related to that task)

### Listing changes
**At least 1** of these categories must be in each version listed:
  * What's New: A list of all major additions
  * Changes: A list of all major updates
  * Fixes: A list of all bug fixes (major and minor)

## Resources
* Markdown wiki: https://bitbucket.org/tutorials/markdowndemo/src/master/README.md
* How to write a Git Commit Message: https://chris.beams.io/posts/git-commit/
* How to read version number https://stackoverflow.com/questions/2791121/what-every-digit-means-in-software-version-1-7-1-0-for-example
