# Exercices — Git Workflow Training

Five progressive exercises to master git workflows before tackling Transcendence.

Each exercise includes: **what to do**, **the commands**, and **what to observe** (the learning part).

---

## Exercise 0 — Read the Tree

**Objective:** Visualize the branch structure without making changes.

**Commands:**
```bash
git log --graph --oneline --all --decorate
```

**What to observe:**
- Where is `main`? It should be at the bottom (the oldest commit).
- Where is `develop`? It should be ahead of `main` with 3-4 commits.
- Do you see a merge commit? That's where `feature/elo-system` was merged into `develop`.
- Is there a branch point for `feature/exemple`? That's a feature in progress, not merged yet.

The tree should look roughly like this:
```
*   (develop) Merge branch 'feature/elo-system'
|\
| * (feature/elo-system) Implement Elo rating system
| * Add Score tests
|/
* (feature/exemple) WIP: rank function stub
* Initial commit (main, v0.1.0)
```

**Why?** This trains your eye to read git history as a graph, not a line. You'll need this skill constantly.

---

## Exercise 1 — Your First PR

**Objective:** Open a pull request and discover why the merge button is disabled.

**Setup:**
```bash
git checkout develop
git pull origin develop
git checkout -b feature/contributor-01
```

Replace `01` with your student number.

**Do this:**
1. Edit `CONTRIBUTORS.md`
2. Add your name to the list (maintain the list format with no blank lines)
3. Commit and push:
```bash
git add CONTRIBUTORS.md
git commit -m "Add @your-name to contributors"
git push -u origin feature/contributor-01
```

4. Go to GitHub and **open a pull request** into `develop`

**What to observe:**
- Is the Merge button greyed out? Click the details.
- You should see: **"Some checks haven't completed yet"** or **"Status check failed"** (if you broke format)
- Go to the **Actions** tab and watch the CI run
- Wait for it to turn green

**Why?** This teaches you that CI is a gate, not a suggestion. Bad code gets blocked automatically, not by a person having to review. This scales.

## Exercise 2 — Implement a Feature (With Tests)

**Objective:** Implement the missing `Score::rank()` function and write tests for it.

**The requirement:**
- Implement `Score::rank(const std::vector<Player>&)` in `src/Score.cpp`
- It should return players sorted by `rating` **descending**
- At **equal rating**, sort by `name` **ascending** (alphabetically)
- Write at least **4 tests** in `tests/test_score.cpp`, including the equal-rating case

**Example:**
```
Input: [("Bob", 1500), ("Alice", 1500), ("Charlie", 1000)]
Output: [("Alice", 1500), ("Bob", 1500), ("Charlie", 1000)]
```

Alice comes before Bob (same rating, alphabetical order).

**Steps:**
1. Branch from `develop`:
```bash
git checkout develop
git pull origin develop
git checkout -b feature/rank-function
```

2. Implement `Score::rank()` in `src/Score.cpp` (remove the `throw`)
3. Write at least 4 tests in `tests/test_score.cpp`
4. Run locally: `make test-unit` (should all pass)
5. Commit code and tests together:
```bash
git add src/Score.cpp src/Score.hpp tests/test_score.cpp
git commit -m "Implement rank() and add tests"
git push -u origin feature/rank-function
```

6. Open a PR into `develop`

**What to observe:**
- If you forget a test, the review will flag it as incomplete
- If you add tests in a separate commit after the implementation, the reviewer will ask for a rebase (tests + code in one commit)
- Once CI passes and you have 1 approval (or 0 in solo mode), you can merge

**Why?** This enforces the discipline of test-driven development and teaches you to organize commits logically. A feature + its tests = one logical unit.

