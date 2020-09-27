# Post Mortem:

## **[2.2.0]** Sun Sep 27 2020
### About branching
* At the beginning I thought about doing branches for this repo. Each task was gonna be a branch of its own, but now I think it's too much for a project that's only maintained by a single person.
* It also doesn't help that when you merge the branches together, all the commit messages related to that branch is now in master, 
and messages like "ADD: Task specs" is too generic since they don't have task name to be easily identified (what task is this task specs for?) without having to go into the commit to see it.
* I'll have to be more specific with my commit messages if I were to do this in one master branch.