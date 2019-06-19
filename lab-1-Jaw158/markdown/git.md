# git workflow

## git

git is a method of sharing files between a large number of people/groups of 
people. It works by starting with a few base files on a master branch. These 
files are what currently exists and is known to work. Other people then 
download (clone) these files to their local computer using:

    git clone "file"

The people making changes to these files will then create a new branch to 
work on the files. A branch allows people to experiment with the files without 
affecting the original working files. A branch can be created with:

    git branch "branch name"

and accessed using:

    git checkout "branch name"

As the people work on the files they will need to periodically save their 
files. This is done with:

    git commit -m "message"

The "-m" above allows for a message to be created describing what was saved. 
The command:

    git push

is also used. This moves saved changes onto a person's github, saving the 
changes online so they can be accessed anywhere. After creating their 
modifications, and ensuring they work, the people will reintegrate their branch 
with the master branch, effectively adding their changes to the orignal files. 
A branch is reintegrated using a pull request. this announces that the changes 
have been made and the person would like to integrate them with the original 
files.

## documentation

Documentation is the process of describing what changes you make to files and 
why. Good documentation is important so you can check back on the changes made 
and understand why it was done. In this way you have a history of what was 
done so if these older files need to be accessed or changed the people working 
on them don't have to spend time figuring out what was done in the first place.

