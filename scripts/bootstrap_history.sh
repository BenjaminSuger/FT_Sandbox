#!/bin/bash

set -e

echo "=== Bootstrapping git history ==="

# Initialize if not already a repo
if [ ! -d .git ]; then
    git init
    git config user.email "sandbox@example.com"
    git config user.name "Sandbox"
fi

# Ensure we're on main
git checkout -b main 2>/dev/null || git checkout main

# Stage all files and make initial commit
git add -A
git commit -m "Initial commit" --allow-empty || git commit --amend -m "Initial commit"

# Tag the initial commit
git tag -a v0.1.0 -m "v0.1.0" || git tag -f v0.1.0

# Create develop branch
git checkout -b develop || git checkout develop

# Add some commits to develop
echo "# Development branch" >> README.md
git add README.md
git commit -m "Add development notes"

echo "Added Elo system" >> README.md
git add README.md
git commit -m "Update README for Elo system"

echo "Setup completed" >> README.md
git add README.md
git commit -m "Final development milestone"

# Create and merge a feature branch (to show merge commits)
git checkout -b feature/elo-system
echo "Elo implementation details" >> README.md
git add README.md
git commit -m "Implement Elo rating system"

git checkout develop
git merge --no-ff feature/elo-system -m "Merge branch 'feature/elo-system'"

# Leave a feature branch in progress
git checkout -b feature/exemple
echo "WIP: rank function" >> README.md
git add README.md
git commit -m "WIP: rank function stub"

# Return to develop
git checkout develop

echo ""
echo "=== Git history created ==="
echo ""
git log --graph --oneline --all --decorate
echo ""
echo "Summary:"
echo "  ✓ main branch at initial commit (tagged v0.1.0)"
echo "  ✓ develop branch 3+ commits ahead"
echo "  ✓ Merge commit visible (feature/elo-system)"
echo "  ✓ Feature branch in progress (feature/exemple)"
echo ""
echo "Ready for exercises. Start with:"
echo "  git log --graph --oneline --all --decorate"
