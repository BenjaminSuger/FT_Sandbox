# Setting Up the Repository

This document describes the **manual setup** required after creating the repository.
These settings are **not transported** by forks or templates — each person must recreate them.

## 1. Make the Repository Public

Go to **Settings → Visibility** and set the repo to **Public**.

**Why?** GitHub Actions are unlimited on public repos. On private repos, even with a paid plan, there can be restrictions on concurrent jobs.

## 2. Enable "Template repository"

Go to **Settings → General** and check **Template repository**.

**Why?** This allows others to use "Use this template" instead of forking, giving them a clean history.

## 3. Set Default Branch to `develop`

Go to **Settings → General → Default branch** and select `develop`.

**Why?** New PRs and local clones will default to develop, not main (which should only be releases).

## 4. Protect `develop` Branch

Go to **Settings → Branches → Add rule**.

**Branch name pattern:** `develop`

- [x] Require a pull request before merging
  - [x] Require at least 1 approval
- [x] Require status checks to pass before merging
  - Select: `unit-tests`, `format`
- [x] Require conversation resolution before merging
- [ ] Require linear history (optional, but recommended)
- [ ] Dismiss stale pull request approvals

### Using the GitHub CLI

```bash
gh repo edit --enable-branch-protection develop \
  --require-status-check unit-tests \
  --require-status-check format \
  --require-code-review
```

## 5. Protect `main` Branch

Go to **Settings → Branches → Add rule**.

**Branch name pattern:** `main`

- [x] Require a pull request before merging
  - [x] Require at least 2 approvals
- [x] Require status checks to pass before merging
  - Select: `unit-tests`, `format`, `integration-tests`, `docker-build`
- [x] Require conversation resolution before merging
- [x] Dismiss stale pull request approvals
- [x] Require code review from code owners (if CODEOWNERS is populated)
- [x] Require a passing deployment review
- [x] Require signed commits (optional, school requirement)
- [ ] Restrict who can push to matching branches

### Using the GitHub CLI

```bash
gh repo edit --enable-branch-protection main \
  --require-status-check unit-tests \
  --require-status-check format \
  --require-status-check integration-tests \
  --require-status-check docker-build \
  --require-code-review \
  --require-code-review-from-code-owners \
  --dismiss-stale-reviews
```

## 6. Solo Mode

If you're working alone on your own repo, **you cannot approve your own PR**.

**Solution:** Set required approvals to **0**, but **keep status checks mandatory**.

```bash
gh repo edit --enable-branch-protection develop \
  --require-status-check unit-tests \
  --require-status-check format
```

You lose the review step, but you keep the branch protection, CI blocking, rebase, and conflict resolution — the essential learning outcomes.

## 7. Verify Protection Rules

```bash
gh repo view --json branchProtectionRules
```

You should see rules for both `develop` and `main` with the required checks.

## Summary Checklist

- [ ] Repository is **public**
- [ ] **Template repository** is enabled
- [ ] Default branch is **`develop`**
- [ ] Branch protection on **`develop`**: 1 approval, `unit-tests` + `format` checks
- [ ] Branch protection on **`main`**: 2 approvals, all 4 checks
- [ ] Status checks are **required** (not optional)
- [ ] Conversations must be **resolved** before merging
