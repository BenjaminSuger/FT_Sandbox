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

---

## Exercise 2 — Break the CI (Deliberately)

**Objective:** See what happens when a test fails, and learn to read CI logs.

**Do this:**
1. Make sure you're on your branch:
```bash
git checkout feature/contributor-01
```

2. Edit `src/Score.cpp` and change the `computeElo` function to always return `0`:
```cpp
int Score::computeElo(int playerRating, int opponentRating, bool won) {
    return 0;  // BREAK THIS INTENTIONALLY
}
```

3. Commit and push:
```bash
git add src/Score.cpp
git commit -m "WIP: break Elo for debugging"
git push
```

4. **Do NOT push to main**, just to your feature branch. Go to GitHub and refresh your PR.

**What to observe:**
- The PR now shows red ❌ on the checks
- Click on "Details" next to the failing `unit-tests` check
- Read the log: which test failed? (It will be something like `"equal rating victory"`)
- Now fix the code (restore the original implementation)
- Push again:
```bash
git checkout src/Score.cpp  # restore the file
git add src/Score.cpp
git commit -m "Fix Elo implementation"
git push
```

- Refresh the PR page — without reopening it, the checks should go green again

**Why?** This shows you:
1. CI failures are immediate feedback (not discovered at review time)
2. Fixing is easy (just commit + push, no PR reopening)
3. CI logs are readable (you found the test name by reading output)

---

## Exercise 3 — Implement a Feature (With Tests)

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

---

## Exercise 4 — Rebase and Resolve Conflicts

**Objective:** Update your branch with changes from others, and resolve conflicts.

**Setup:**
This exercise requires that someone else has already merged into `develop` (touching `CONTRIBUTORS.md`).
If you're solo, do this: switch to develop, add a different name to CONTRIBUTORS.md, commit, and push. Then go back to your feature branch.

**Do this:**
1. Make sure you're on your feature branch (from exercise 3 or 1):
```bash
git checkout feature/contributor-01
```

2. Fetch and rebase:
```bash
git fetch origin
git rebase origin/develop
```

3. You should see:
```
CONFLICT (content): Merge conflict in CONTRIBUTORS.md
```

4. Open `CONTRIBUTORS.md` and resolve the conflict:
```
- Alice
<<<<<<< HEAD
- Dave
=======
- Eve
>>>>>>> origin/develop
- Bob
```

Pick one, or keep both (remove the conflict markers). Let's keep both:
```
- Alice
- Dave
- Eve
- Bob
```

5. Stage and continue the rebase:
```bash
git add CONTRIBUTORS.md
git rebase --continue
```

6. Force-push with lease:
```bash
git push --force-with-lease
```

**What to observe:**
- Why `--force-with-lease` and not `--force`?
  - `--force-with-lease` refuses to overwrite work pushed by someone else since your last fetch
  - `--force` blindly overwrites everything (dangerous in teams)
  - On this solo repo it's the same, but the habit is critical

**Why?** This is the real-world scenario: your feature branch gets stale. Rebase keeps history linear, conflicts are resolved locally, and the PR becomes a clean fast-forward merge.

---

## Exercise 5 — Cross Review

**Objective:** Review a colleague's PR and practice giving constructive feedback.

**Setup:**
Pair up (or rotate in groups of 3+).

**Do this:**
1. Find someone else's open PR on GitHub
2. Go to **Files changed** and read their code
3. Leave at least one **substantive comment** (not just "looks good")
   - Ask a question, suggest a refactor, or spot an edge case
   - Use **Review → Request Changes** (not Approve)
4. The author responds and updates their code
5. Once satisfied, use **Approve** to unblock the merge

**What to observe:**
- How does GitHub threading work? (You can see the conversation)
- How do you leave comments on specific lines? (Hover and click the line number)
- What's the difference between "Request Changes" and "Approve"? (Changes block merge, Approve unblocks it)

**Why?** Code review is how teams learn. You see someone else's approach, they see yours, everyone gets better.

---

## Bonus — The Release

**Objective:** Cut a release from `develop` → `main`.

This is a **team exercise** — do it once as a group so nobody discovers it on soutenance day.

**Steps:**
1. Create a PR from `develop` → `main` with title: "Release v1.0.0"
2. Describe what's new
3. Get approvals
4. Merge with a **merge commit** (not squash or rebase)
5. On `main`, create a tag:
```bash
git checkout main
git pull origin main
git tag -a v1.0.0 -m "Release v1.0.0"
git push origin v1.0.0
```

6. Go to GitHub **Releases** and verify the tag appears

**What to observe:**
- The merge commit is now part of `main`'s history (you can see it in `git log`)
- The tag is a pointer to that commit (searchable in GitHub)
- Every future release follows the same pattern

**Why?** Releases are not magic. They're just an agreed-upon commit + a tag. Anyone can cut one; the process is the protection.

---

## Summary

| Exercise | Skill | Time | Notes |
|----------|-------|------|-------|
| 0 | Read history | 2 min | Just `git log` |
| 1 | Open PR, watch CI | 10 min | Discover merge button disabled |
| 2 | Fix CI failures | 5 min | Intentionally break code, fix it |
| 3 | Implement + test | 20 min | The real work (code + tests together) |
| 4 | Rebase + conflict | 10 min | The scary part, now safe |
| 5 | Review | 15 min | Team learning (needs peer) |
| Bonus | Release | 5 min | Once-per-team |

**Total time:** ~70 minutes, spread over 2–3 sessions.

After these exercises, you'll have lived every scenario except deletion/force-push disasters (intentionally avoided — once is enough per career).
