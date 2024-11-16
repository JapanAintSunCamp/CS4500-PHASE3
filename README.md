# PHASE 3 CS 4500
---
## Description
This program collects log data stored in .CSV logs in the local directory and created reports and graphs from the data
The reports created are detailed below:

- Report 1: A table listing each name (in the form Firstname Lastname) and the total number of minutes entered into their time log.
- Report 2: A table showing how many minutes total were spent by all team members on each of the activity codes.
- Report 3: A table showing how many minutes were spent by each team member on each of the activity codes.
- Report 4: A table showing total team minutes for each day of the week over all days covered in all the logs.
- Report 5: This report is not a table, but a list, sorted by date and time, earliest dates and times first, latest dates and times last.
- Graph A: This graph displays the same information as given in Report 1 above. But instead of displaying the information as a table, Graph A displays it as a bar chart.
- Graph B: This is graph displays the same information as given in Report 3 above but given as a heatmap
- Graph C: This graph shows data that was not in any of the reports above.

---
## Git Process
### 1. Clone this repository to your local machine, the default repo branch should be "dev"
```bash
git clone <repository-url>
cd <repository-name>
```

### 2. Create and switch to a new feature branch to implement your improvement or feature
Make sure you always run this command from the "dev" branch
```bash
# always create a new branch from the dev branch
# NOTE: the "-b" flag will create a new branch, only include it if the branch you are swapping to does not exist
git checkout -b <feature-branch-name>

# if you are currently not on the dev branch run the following command to move to dev
git checkout dev
```

### 3. Work on your feature add your changes to "commits" that will be added to version control
Files that are not added to a branch by a "commit" will not be added to version control

These files or changes will also persist when you change to another branch, potentially bringing unwanted changes into other branches

To "stage" you files for a commit use these commands
```bash
# Check the current status of your files, this will show files have been added, deleted, and modified
git status

# Adds all currently unstaged files to the commit stage. These will be added as part of your next commit
git add .

# Adds only the indicated file to the commit stage.
git add <file name>

# Commits all currently staged files to the current branch
git commit -m 'commit message'

# Pushes all commited changes on the current branch to that branch on the remote repository
# This will also create the branch on the remote repository if it does not exist
git push origin <feature-branch-name>
```

### 4. Create a pull request to merge your feature branch back into the dev branch
After your feature is complete, follow these steps to add your changes back into the dev branch
```bash
# ensure all your changed files are saved and committed to your feature branch
git status
git add .
git commit -m 'commit message'

# NOTE: when writing a commit message, try to be concise and descriptive. This will help in the future when reviewing commits to locate bugs or specific changes
# some tips for writing better commit messages can be found here: https://www.freecodecamp.org/news/how-to-write-better-git-commit-messages/

# ensure your local version of the dev branch is up-to-date
git checkout dev
git pull

# swap back to your feature branch
git checkout <feature-branch-name>

# merge the dev branch into your feature branch
git merge dev

# handle any git merge conflicts that might occur
# Verify that your code still works as intended with the newly updated code

# push your feature branch to github
git push origin <feature-branch-name>
```

 - Once you have pushed your branch to github, create a pull request for your branch. Ensure that the base branch is alwasy set to "dev" and the compare branch is your feature branch
 - Once the merge request has been created, verify that github detects no merge conflicts or issues
 - If github does not detect any merge conflicts or issues, merge your changs
    - If github DOES detect any merge conflicts or issues, address those issues locally and they push up those changes until no issues are detected

## How to run this code
### TODO
